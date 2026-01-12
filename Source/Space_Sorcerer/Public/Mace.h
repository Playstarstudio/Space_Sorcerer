// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Part.h"
#include "GameFramework/Actor.h"
#include "Mace.generated.h"

class APart;


UCLASS()
class SPACE_SORCERER_API AMace : public APart
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMace();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PartData")
	float DamangeOnImpact;
};
