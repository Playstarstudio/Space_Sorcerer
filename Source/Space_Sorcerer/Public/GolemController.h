// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GolemController.generated.h"

/**
 * 
 */
UCLASS()
class SPACE_SORCERER_API AGolemController : public AAIController
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay();

	FGenericTeamId PerceptionTeamId;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

public:

	virtual FGenericTeamId GetGenericTeamId() const override 
	{
		return PerceptionTeamId;
	}
};
