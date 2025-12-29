// Fill out your copyright notice in the Description page of Project Settings.


#include "ModulePosition.h"

// Sets default values
AModulePosition::AModulePosition()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AModulePosition::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AModulePosition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

