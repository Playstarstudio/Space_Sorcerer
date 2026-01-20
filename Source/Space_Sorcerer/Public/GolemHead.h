// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Part.h"
#include "GolemHead.generated.h"

/**
 * 
 */
UCLASS()
class SPACE_SORCERER_API AGolemHead : public APart
{
	GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PartData")
    bool PreferRanged;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PartData")
    float RangeDamageMod;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PartData")
    float MeleeDamageMod;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PartData")
    float HpMod;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PartData")
    float DefenseMod;
};
