// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WayPoint.h"
#include "PriestAIController.generated.h"

/**
 * 
 */
UCLASS()
class THEBACKROOMS_API APriestAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	APriestAIController();

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* Pawn) override;

	virtual void Tick(float DeltaSeconds) override;
	virtual FRotator GetControlRotation() const override;


	UFUNCTION()
		void OnPawnDetected(const TArray<AActor*>& DetectedPawns);
	UFUNCTION()
		AWayPoint* FindNewWayPoint();
	UFUNCTION()
		bool IsPlayerInRange();
	UFUNCTION()
		bool IsPlayerInSight();
	UFUNCTION(BlueprintGetter)
		bool IsPraying();
	UFUNCTION()
		bool IsPanicking();
	UFUNCTION(BlueprintGetter)
		bool IsAfraid();
	
	

	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = AI)
		float AISightRadius = 500.f;
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = AI)
		float AISightAge = 5.0f;
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = AI)
		float AILoseSightRadius = AISightRadius + 50.f;
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = AI)
		float AISightAngle = 65.f;
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = AI)
		class UAISenseConfig_Sight* SightConfig;

	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = WayPoint)
		int previousArrayIndex = 0;

	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = WayPoint)
		bool HasSeenPlayer = false;
	UPROPERTY()
		bool m_IsPlayerInRange;
	UPROPERTY()
		float m_PrayerAttackTime;
	UPROPERTY()
		float m_AttackTime = 1.f;

	UPROPERTY(BlueprintGetter = IsPraying)
		bool m_IsPraying;
	UPROPERTY(BlueprintGetter = IsAfraid)
		bool m_IsAfraid = false;
};
