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
		return ETeamAttitude::Neutral;
	}

	auto PlayerTI = Cast<IGenericTeamAgentInterface>(&other);
	class IGenericTeamAgentInterface* BotTI = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController());

	if (BotTI == nullptr && PlayerTI == nullptr)
	{
		return ETeamAttitude::Neutral;
	}

	FGenericTeamId OtherActorTeamId = NULL;
	if (BotTI != nullptr)
	{
		OtherActorTeamId = BotTI->GetGenericTeamId();
	}
	else if (PlayerTI != nullptr)
	{
		OtherActorTeamId = PlayerTI->GetGenericTeamId();
	}

	FGenericTeamId ThisId = GetGenericTeamId();
	if (OtherActorTeamId == 255)
	{
		return ETeamAttitude::Neutral;
	}
	else if (OtherActorTeamId == ThisId)
	{
		return ETeamAttitude::Friendly;
	}
	else
	{
		return ETeamAttitude::Hostile;
	}
}
