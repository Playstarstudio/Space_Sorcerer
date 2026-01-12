// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Golem.h"
#include "GolemPartRegion.h"
#include "Part.generated.h"



UCLASS()
class SPACE_SORCERER_API APart : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APart();

	UGolemPartRegion region = UGolemPartRegion::PR_None;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//NOTE: Set when cannon is added
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PartData")
	AGolem* associatedGolem;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PartData")
	float Cooldown;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PartData")
	float MinRange;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PartData")
	float MaxRange;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PartData")
	bool isRanged;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PartData")
	UGolemPartRegion regionAcceptablePlace;

};
