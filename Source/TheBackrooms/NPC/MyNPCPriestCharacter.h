// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPCBaseCharacter.h"

#include "MyNPCPriestCharacter.generated.h"

/**
 * 
 */
UCLASS()
class THEBACKROOMS_API AMyNPCPriestCharacter : public ANPCBaseCharacter
{
	GENERATED_BODY()
	
public:
	AMyNPCPriestCharacter();

	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		APrayerAttack* m_pPrayer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintGetter)
		bool IsPriestPanicking();
	UFUNCTION(BlueprintGetter)
		bool IsPraying();

private:
	

	UPROPERTY(BlueprintGetter = IsPriestPanicking)
		bool m_IsPanicking;

	

	UPROPERTY(BlueprintGetter = IsPraying)
		bool m_bIsPraying;

};
