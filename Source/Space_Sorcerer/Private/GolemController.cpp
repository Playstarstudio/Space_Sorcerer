// Fill out your copyright notice in the Description page of Project Settings.


#include "GolemController.h"

void AGolemController::BeginPlay()
{
	Super::BeginPlay();
}


ETeamAttitude::Type AGolemController::GetTeamAttitudeTowards(const AActor& other) const
{
	const APawn* OtherPawn = Cast<APawn>(&other);
	if (OtherPawn == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("I BROKE11!"));

		return ETeamAttitude::Neutral;
	}

	auto PlayerTI = Cast<IGenericTeamAgentInterface>(&other);
	class IGenericTeamAgentInterface* BotTI = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController());

	if (BotTI == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("botTI is Null"));

		return ETeamAttitude::Neutral;
	}
	if (PlayerTI == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("playerTI is Null"));

		return ETeamAttitude::Neutral;
	}

	FGenericTeamId OtherActorTeamId = NULL;
	if (BotTI != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Getting Other Bot's ID"));

		OtherActorTeamId = BotTI->GetGenericTeamId();
	}
	else if (PlayerTI != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Getting MY ID"));

		OtherActorTeamId = PlayerTI->GetGenericTeamId();
	}

	FGenericTeamId ThisId = GetGenericTeamId();
	if (OtherActorTeamId == 255)
	{
		UE_LOG(LogTemp, Warning, TEXT("Neutral!"));
		return ETeamAttitude::Neutral;
	}
	else if (OtherActorTeamId == ThisId)
	{
		UE_LOG(LogTemp, Warning, TEXT("Friendly!"));

		return ETeamAttitude::Friendly;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Hostile!"));
		return ETeamAttitude::Hostile;
	}
}
