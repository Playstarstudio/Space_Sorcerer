// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity.h"
#include "Perception/AISightTargetInterface.h"
#include "GenericTeamAgentInterface.h"
#include "GolemPartRegion.h"
#include "Golem.generated.h"

class ACannon;
class APart;


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

	virtual FGenericTeamId GetGenericTeamId() const override { return PerceptionTeamId; }


	UFUNCTION(BlueprintCallable, Category = "Parts")
	void SetRegion(UGolemPartRegion region, bool enabled);

	UFUNCTION(BlueprintCallable, Category = "Parts")
	void AddCannon(TSubclassOf<APart> part, FString Position, UGolemPartRegion region, FVector scale, FRotator rotation);

	UFUNCTION(BlueprintCallable, Category = "Parts")
	void RemoveCannon(UGolemPartRegion region);

	UFUNCTION(BlueprintCallable, Category = "Parts")
	virtual void DestroyGolem();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float distanceToTarget = -1;


	//NOTE: COULD BE NULL WHEN NO TARGET IS AVAILABLE
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	AGolem* targetGolem;




	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//Resets the target Golem and its distance;

	UFUNCTION(BlueprintCallable, Category = "AI")
	void ResetTarget();

	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetTarget(AGolem* newTarget);


	//Updates the distance to target, what did you think this did?
	UFUNCTION(BlueprintCallable, Category = "AI")
	virtual void UpdateDistanceToTarget();
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parts")
	TArray<APart*> Parts;

	//Mapping from normal name(left, right, up, down) to socket name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoneMappings")
	TMap<FString, FString> NameMapping;



	//Mapping from normal name(left, right, up, down) to socket name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoneMappings")
	TMap<UGolemPartRegion, bool> SectionsEnabled;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FGenericTeamId PerceptionTeamId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TArray<FName> ViewTargets;
	/*
	UFUNCTION(BlueprintCallable)
	void NextViewTarget();
	int32 Index = 0;
	*/

private:

};