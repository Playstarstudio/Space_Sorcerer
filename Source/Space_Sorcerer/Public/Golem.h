// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity.h"
#include "GenericTeamAgentInterface.h"
#include "GolemPartRegion.h"
#include "Golem.generated.h"

class ACannon;

/**
 * 
 */
UCLASS()
class SPACE_SORCERER_API AGolem : public AEntity, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int WeaponRangeMax_R;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int WeaponRangeMax_L;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int WeaponRangeMin_R;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int WeaponRangeMin_L;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	bool MeleeWeapon_R;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	bool MeleeWeapon_L;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	bool Fire_R;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	bool Fire_L;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	int32 PerceptionID = 0;



	UFUNCTION(BlueprintCallable, Category = "Partss")
	void SetRegion(UGolemPartRegion region, bool enabled);

	UFUNCTION(BlueprintCallable, Category = "Parts")
	void AddCannon(TSubclassOf<ACannon> cannon, FString Position, UGolemPartRegion region, FVector scale, FRotator rotation);


	virtual FGenericTeamId GetGenericTeamId() const override { return PerceptionTeamId; }

protected:


	TArray<ACannon*> Cannons;

	//Mapping from normal name(left, right, up, down) to socket name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoneMappings")
	TMap<FString, FString> NameMapping;



	//Mapping from normal name(left, right, up, down) to socket name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoneMappings")
	TMap<UGolemPartRegion, bool> SectionsEnabled;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FGenericTeamId PerceptionTeamId;
private:

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};