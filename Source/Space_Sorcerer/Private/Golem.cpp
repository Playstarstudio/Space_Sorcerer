// Fill out your copyright notice in the Description page of Project Settings.


#include "Golem.h"
#include "Cannon.h"






void AGolem::SetRegion(UGolemPartRegion region, bool enabled)
{
	SectionsEnabled.Add(region, enabled);
}

void AGolem::AddCannon(TSubclassOf<ACannon> cannon, FString Position, UGolemPartRegion region, FVector scale, FRotator rotation)
{
	FName actualName = FName(*NameMapping.Find(Position));
	FTransform socketTransform = GetMesh()->GetSocketTransform(actualName);
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = GetInstigator();
	FAttachmentTransformRules TransformRules = FAttachmentTransformRules(
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepRelative, 
		true 
	);
	ACannon* cannonObj = GetWorld()->SpawnActor<ACannon>(cannon, socketTransform, SpawnParams);
	cannonObj->AttachToComponent(GetMesh(), TransformRules, actualName);
	cannonObj->SetActorScale3D(cannonObj->GetActorScale3D() * scale);
	cannonObj->SetActorRelativeRotation(rotation);
	Cannons.Add(cannonObj);
	cannonObj->region = region;
	
}

void AGolem::DestroyGolem()
{
	for (ACannon* cannon : Cannons)
	{
		cannon->Destroy();
	}
	Destroy();
}

void AGolem::ResetTarget()
{
	targetGolem = NULL;
	distanceToTarget = -1.0;
}

void AGolem::SetTarget(AGolem* newTarget)
{
	if (newTarget == nullptr) return;
	targetGolem = newTarget;
	FVector targetVec = targetGolem->GetActorLocation();
	FVector golemVec = GetActorLocation();
	distanceToTarget = FVector::Distance(targetVec, golemVec);
}

void AGolem::UpdateDistanceToTarget()
{
	FVector targetVec = targetGolem->GetActorLocation();
	FVector golemVec = GetActorLocation();
	distanceToTarget = FVector::Distance(targetVec, golemVec);
}

void AGolem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	for (ACannon* cannon : Cannons)
	{
		if (SectionsEnabled.Contains(cannon->region) && SectionsEnabled.Find(cannon->region)) 
		{
			cannon->Fire();
		}
	}
}
