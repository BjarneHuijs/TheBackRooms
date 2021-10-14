// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScoreSystem.generated.h"


enum class BloodTiers : uint8;
class APlayerMonster;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEBACKROOMS_API UScoreSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UScoreSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintGetter)
		int GetCurrentScore() const;
	UFUNCTION(BlueprintGetter)
		int GetFinalScore() const;
	UFUNCTION(BlueprintGetter)
		int GetNrOfKills() const;
	UFUNCTION(BlueprintGetter)
		int GetNrOfPriestKills() const;
	UFUNCTION(BlueprintGetter)
		float GetTotalTimeAlive() const;

	UFUNCTION()
		void NPCWasKilled(float NPCValue);
	
private:
	UPROPERTY(BlueprintGetter = GetNrOfKills)
		int m_NrOfKills;
	UPROPERTY(EditAnywhere)
		int m_KillScoreValue;
	UPROPERTY(BlueprintGetter = GetNrOfPriestKills)
		int m_NrOfPriestKills;
	UPROPERTY(EditAnywhere)
		int m_PriestKillScoreValue;
	UPROPERTY(BlueprintGetter = GetTotalTimeAlive)
		float m_TotalTimeAlive;
	
	UPROPERTY()
		float m_TimeHeldHighestTier;
	UPROPERTY()
		BloodTiers m_HighestTier;

	UPROPERTY(BlueprintGetter = GetCurrentScore)
		int m_CurrentScore;
	UPROPERTY(BlueprintGetter = GetFinalScore)
		int m_FinalScore;

	UPROPERTY()
		TArray<float> m_BloodMultiplierValues;

	UFUNCTION()
		void CalculateFinalScore();
};
