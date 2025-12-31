// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity.h"
#include "GenericTeamAgentInterface.h"
#include "Golem.generated.h"


/**
 * 
 */
UCLASS()
class SPACE_SORCERER_API AGolem : public AEntity, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	int32 PerceptionID = 0;


	virtual FGenericTeamId GetGenericTeamId() const override { return PerceptionTeamId; }

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FGenericTeamId PerceptionTeamId;

private:

};