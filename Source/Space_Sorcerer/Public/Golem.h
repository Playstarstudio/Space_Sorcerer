// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity.h"
#include "Golem.generated.h"

/**
 * 
 */
UCLASS()
class SPACE_SORCERER_API AGolem : public AEntity
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int hp;
protected:

private:

};