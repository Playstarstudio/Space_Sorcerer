// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Part.h"
#include "GolemPartRegion.h"
#include "Cannon.generated.h"

class APart;

/**
 *
 */
UCLASS()
class SPACE_SORCERER_API ACannon : public APart
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACannon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PartData")
	float Cooldown;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PartData")
	float MinRange;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PartData")
	float MaxRange;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "InitateFire")
	void Fire();
};
