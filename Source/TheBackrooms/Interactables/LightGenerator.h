// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"

#include "LightGenerator.generated.h"


UCLASS()
class THEBACKROOMS_API ALightGenerator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALightGenerator();
	~ALightGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void SetGeneratorState();
	UFUNCTION()
		void FindLightsInScene() const;
	UFUNCTION()
		void ResetLightsInScene() const;
	UFUNCTION()
		void ResetLightsEnd() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Collision)
		class USphereComponent* m_HitDetectionSphere;

	UFUNCTION(BlueprintGetter)
		float GetRepairTime() const;
	UFUNCTION(BlueprintSetter)
		void SetRepairTime(float repairTime);
	
	UFUNCTION(BlueprintGetter)
		bool IsBroken() const;
	UFUNCTION()
		bool IsGeneratorBroken();
private:
	UPROPERTY()
	float m_LightIntensity = 35.f;
	UPROPERTY()
	float m_TimeSinceBroken = 0.f;

	UPROPERTY(BlueprintGetter = IsBroken)
		bool m_IsBroken = false;
	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetRepairTime, BlueprintSetter = SetRepairTime, Category = Collision)
		float m_TimeToRepair = 15.f;
};
