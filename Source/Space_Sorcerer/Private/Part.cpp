// Fill out your copyright notice in the Description page of Project Settings.


#include "Part.h"

// Sets default values
APart::APart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APart::BeginPlay()
{
	Super::BeginPlay();
	CurrentCooldown = Cooldown;
}

// Called every frame
void APart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentCooldown -= DeltaTime;
	FMath::Clamp(CurrentCooldown, -1, FLT_MAX);
}

