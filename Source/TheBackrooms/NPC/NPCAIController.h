// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WayPoint.h"
#include "NPCAIController.generated.h"

/**
 * 
 */
UCLASS()
class THEBACKROOMS_API ANPCAIController : public AAIController
{
	GENERATED_BODY()

public:
	ANPCAIController();

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* Pawn) override;

	virtual void Tick(float DeltaSeconds) override;
	virtual FRotator GetControlRotation() const override;


	UFUNCTION()
		void OnPawnDetected(const TArray<AActor*>& DetectedPawns);
	UFUNCTION()
		AWayPoint* FindNewWayPoint();

	
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
		bool allowedToMove = false;

	UPROPERTY(BlueprintGetter = IsAfraid)
		bool m_IsAfraid = false;
	UFUNCTION(BlueprintGetter)
		bool IsAfraid();
	UFUNCTION()
		bool IsPanicking();
};
