// Fill out your copyright notice in the Description page of Project Settings.


#include "Golem.h"
#include "Cannon.h"
#include "Part.h"





bool AGolem::CanPlaceInRegion(TSubclassOf<APart> part, UGolemPartRegion region)
{
	UGolemPartRegion partRegion = part.GetDefaultObject()->regionAcceptablePlace;
	if (partRegion == UGolemPartRegion::PR_Both_Hands && (region == UGolemPartRegion::PR_Left || region == UGolemPartRegion::PR_Right)) 
	{
		return true;
	}
	return partRegion == region;
}

void AGolem::SetRegion(UGolemPartRegion region, bool enabled)
{
	SectionsEnabled.Add(region, enabled);
}

APart* AGolem::AddCannon(TSubclassOf<APart> part, UGolemPartRegion region, FVector scale, FRotator rotation)
{
	if (!CanPlaceInRegion(part, region))
	{
		return nullptr;
	}
	FString Position = "None";
	if (region == UGolemPartRegion::PR_Left) 
	{
		Position = "Left";
	}
	else if (region == UGolemPartRegion::PR_Right) 
	{
		Position = "Right";
	}
	else if (region == UGolemPartRegion::PR_Head)
	{
		Position = "Head";
	}
	else if (region == UGolemPartRegion::PR_Both_Hands) 
	{
		region = UGolemPartRegion::PR_Right;
		Position = "Right";
		this->AddCannon(part, UGolemPartRegion::PR_Left, scale, rotation);
	}
	if (PartAtLocation(region) != NULL) 
	{
		for (int cannonIndex = Parts.Num() - 1; cannonIndex >= 0; cannonIndex--)
		{
			APart* instantiatedPart = Parts[cannonIndex];
			if (instantiatedPart->region == region)
			{
				instantiatedPart->Destroy();
				Parts.Remove(instantiatedPart);
			}
		}
	}
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
	APart* partObj = GetWorld()->SpawnActor<APart>(part, socketTransform, SpawnParams);
	partObj->AttachToComponent(GetMesh(), TransformRules, actualName);
	partObj->SetActorScale3D(partObj->GetActorScale3D() * scale);
	partObj->SetActorRelativeRotation(rotation);
	partObj->associatedGolem = this;
	Parts.Add(partObj);
	partObj->region = region;
	return partObj;
}

void AGolem::RemoveCannon(UGolemPartRegion region)
{
	for (int cannonIndex = Parts.Num() - 1; cannonIndex >= 0; cannonIndex--)
	{
		APart* cannon = Parts[cannonIndex];
		if (region == cannon->region)
		{
			cannon->Destroy();
			Parts.Remove(cannon);
		}
	}
}



void AGolem::DestroyGolem()
{
	for (APart* cannon : Parts)
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

APart* AGolem::PartAtLocation(UGolemPartRegion region)
{
	for (APart* part : Parts) 
	{
		if (part && part->region == region) 
		{
			return part;
		}
	}

	return nullptr;
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
	for (APart* cannon : Parts)
	{
		if (SectionsEnabled.Contains(cannon->region) && SectionsEnabled.Find(cannon->region) && cannon->IsA(ACannon::StaticClass())) 
		{
			((ACannon*)cannon)->Fire();
		}
	}
}
