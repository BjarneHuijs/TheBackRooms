// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BloodMeter.generated.h"

UENUM(BlueprintType)
enum class BloodTiers : uint8
{
	Tier_1 UMETA(DisplayName = "Tier 1"),
	Tier_2 UMETA(DisplayName = "Tier 2"),
	Tier_3 UMETA(DisplayName = "Tier 3"),
	Tier_4 UMETA(DisplayName = "Tier 4"),
	Tier_5 UMETA(DisplayName = "Tier 5")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEBACKROOMS_API UBloodMeter : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBloodMeter();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintGetter)
		float GetMaxBlood() const;
	UFUNCTION(BlueprintGetter)
		float GetBlood() const;

	UFUNCTION(BlueprintGetter)
		TMap<BloodTiers, float> GetDecayValues() const;

	UFUNCTION()
		void AddBlood(float value);

	UFUNCTION(BlueprintGetter)
		BloodTiers GetCurrentTier() const;
	UFUNCTION(BlueprintGetter)
		BloodTiers GetHighestAchievedTier() const;
	UFUNCTION()
		bool IsMeterEmpty();
private:
	UPROPERTY()
		bool m_bEmpty;

	UPROPERTY(EditAnywhere, BlueprintGetter = GetMaxBlood)
		float m_MaxBlood;
	UPROPERTY(EditAnywhere, BlueprintGetter = GetBlood)
		float m_Blood;
	
	UPROPERTY(BlueprintGetter = GetCurrentTier)
		BloodTiers m_CurrentTier;

	UPROPERTY(BlueprintGetter = GetHighestAchievedTier)
		BloodTiers m_HighestAchievedTier;

	UPROPERTY(EditAnywhere, BlueprintGetter = GetDecayValues)
		TMap<BloodTiers, float> m_DecayValues;
};
