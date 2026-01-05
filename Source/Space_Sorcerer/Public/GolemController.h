// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Golem.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	int PercIdToSet;

	FGenericTeamId PerceptionTeamId;

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

public:

	UPROPERTY(BlueprintReadWrite)
	class AGolem* Agent;

	virtual FGenericTeamId GetGenericTeamId() const override 
	{
		return PerceptionTeamId;
	}

	UFUNCTION()
	void OnPerception(AActor* Actor, FAIStimulus Stimulus)
};
