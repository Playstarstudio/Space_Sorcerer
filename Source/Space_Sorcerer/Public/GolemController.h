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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	int PercIdToSet;

	FGenericTeamId PerceptionTeamId;

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

public:

	UFUNCTION(BlueprintCallable, DisplayName = "SetTeamID", Category = "AI")
	void SetTeam(uint8 const& id)
	{
		PerceptionTeamId = FGenericTeamId(id);
	}

	virtual FGenericTeamId GetGenericTeamId() const override 
	{
		return PerceptionTeamId;
	}
};
