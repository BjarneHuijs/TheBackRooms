// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "PrayerAttack.generated.h"

UCLASS()
class THEBACKROOMS_API APrayerAttack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APrayerAttack();

protected:
	// Called when the game starts or when spawned
	
	virtual void BeginPlay() override;

public:	
	
	// Called every frame
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void StartAttack();
	UFUNCTION()
		void EndAttack();
	UFUNCTION()
		void Reset();
	UFUNCTION()
		bool HasAttacked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DamageAmount = -10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Cooldowntime = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Castingtime = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool m_CanAttack = false;
private:
	UPROPERTY()
	bool m_HasAttacked = false;

	UPROPERTY()
	float m_CurrentCooldownTime;
	UPROPERTY()
	float m_CurrentCastingTime;

	UPROPERTY(VisibleAnywhere)
		UShapeComponent* m_pColliderBox;
};
