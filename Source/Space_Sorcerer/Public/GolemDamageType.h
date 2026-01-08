// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class GolemDamageType : uint8
{
    DT_Instant         UMETA(DisplayName = "Instant"),
    DT_DOT         UMETA(DisplayName = "Damage Over Time"),
};
