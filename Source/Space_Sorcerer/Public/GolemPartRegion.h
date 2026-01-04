// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "GolemPartRegion.generated.h"

UENUM(BlueprintType)
enum class UGolemPartRegion : uint8
{
    PR_None         UMETA(DisplayName = "None"),
    PR_Left         UMETA(DisplayName = "Left side"),
    PR_Right        UMETA(DisplayName = "Right side"),
    PR_MAX         UMETA(Hidden)
};
