// Copyright Epic Games, Inc. All Rights Reserved.

#include "Space_SorcererCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Space_Sorcerer.h"
#include "Bullet.h"
#include "Cannon.h"
#include "ModulePosition.h"

ASpace_SorcererCharacter::ASpace_SorcererCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	// Create the first person mesh that will be viewed only by this character's owner
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));

	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

	// Create the Camera Component	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCameraComponent->SetupAttachment(FirstPersonMesh, FName("head"));
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f), FRotator(0.0f, 90.0f, -90.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
	FirstPersonCameraComponent->FirstPersonScale = 0.6f;

	// configure the character comps
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	GetCapsuleComponent()->SetCapsuleSize(34.0f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;
}

void ASpace_SorcererCharacter::AddCannon(TSubclassOf<ACannon> cannon, FString Position)
{
	for (AModulePosition* pos : CannonTransforms)
	{
		if(pos->ID.Equals(Position)) 
		{
			UWorld* const World = GetWorld();
			if (World)
			{
				//Spawn in bullet
				FVector SpawnLocation = pos->GetActorLocation();
				FRotator SpawnRotation = pos->GetActorRotation();

				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = pos;
				SpawnParams.Instigator = GetInstigator();
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
				FName ComponentName = MakeUniqueObjectName(this, UChildActorComponent::StaticClass(), *FString::Printf(TEXT("ChildActorComp")));
				
				UChildActorComponent* ChildActorComponent = NewObject<UChildActorComponent>(pos, TEXT("ComponentName"));
				ChildActorComponent->RegisterComponent();
				ChildActorComponent->AttachToComponent(pos->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

				ChildActorComponent->SetChildActorClass(cannon);

				AActor* ChildActor = ChildActorComponent->GetChildActor();
				ChildActor->SetActorTransform(pos->GetActorTransform());
				ACannon* childCannon = static_cast<ACannon*>(ChildActor);
				Cannons.Add(childCannon);
			}
		}
	}
}

void ASpace_SorcererCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ASpace_SorcererCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ASpace_SorcererCharacter::DoJumpEnd);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASpace_SorcererCharacter::MoveInput);

		// Looking/Aiming
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASpace_SorcererCharacter::LookInput);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ASpace_SorcererCharacter::LookInput);
		EnhancedInputComponent->BindAction(MouseShootAction, ETriggerEvent::Triggered, this, &ASpace_SorcererCharacter::ShootInput);
	}
	else
	{
		UE_LOG(LogSpace_Sorcerer, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void ASpace_SorcererCharacter::ShootInput(const FInputActionValue& value) 
{
	int a = 1;
	a = a + a;
	for (ACannon* cannon : Cannons) 
	{
		cannon->Fire();
	}
	return;
	
}

void ASpace_SorcererCharacter::MoveInput(const FInputActionValue& Value)
{
	// get the Vector2D move axis
	FVector2D MovementVector = Value.Get<FVector2D>();

	// pass the axis values to the move input
	DoMove(MovementVector.X, MovementVector.Y);

}

void ASpace_SorcererCharacter::LookInput(const FInputActionValue& Value)
{
	// get the Vector2D look axis
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// pass the axis values to the aim input
	DoAim(LookAxisVector.X, LookAxisVector.Y);

}

void ASpace_SorcererCharacter::DoAim(float Yaw, float Pitch)
{
	if (GetController())
	{
		// pass the rotation inputs
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ASpace_SorcererCharacter::DoMove(float Right, float Forward)
{
	if (GetController())
	{
		// pass the move inputs
		AddMovementInput(GetActorRightVector(), Right);
		AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void ASpace_SorcererCharacter::DoJumpStart()
{
}

void ASpace_SorcererCharacter::BeginPlay()
{
	Super::BeginPlay();
	TArray<UChildActorComponent*> childActors;
	GetComponents<UChildActorComponent>(childActors);

	for (UChildActorComponent* childActor : childActors)
	{
		AActor* SpawnedActor = childActor->GetChildActor();
		if (SpawnedActor && SpawnedActor->IsA(AModulePosition::StaticClass()))
		{
			CannonTransforms.Add(Cast<AModulePosition>(SpawnedActor));
		}
	}
	AddCannon(cannonTemplate, "Above");
	AddCannon(cannonTemplate, "Left");


}

void ASpace_SorcererCharacter::DoJumpEnd()
{
}