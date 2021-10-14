// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TheBackrooms/NPC/PrayerAttack.h"
#include "NPCBaseCharacter.generated.h"

UCLASS()
class THEBACKROOMS_API ANPCBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPCBaseCharacter();

	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AWayPoint* NextWayPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool CanAttackPlayer;
	
	UFUNCTION()
		void Die();

	
	
private:
	UFUNCTION(BlueprintGetter)
		bool IsPanicking() const;
	UPROPERTY(BlueprintGetter = IsDead)
		bool m_bIsDead;

	UPROPERTY(BlueprintGetter = IsDying)
		bool m_bIsDying;
	UPROPERTY()
		float m_DeathAnimationTime;

	UPROPERTY(BlueprintGetter = IsPanicking)
		bool m_bIsPanicking;

	UFUNCTION(BlueprintGetter)
		bool IsDying() const;
	UFUNCTION(BlueprintGetter)
		bool IsDead() const;
	UPROPERTY()
		float m_DeathTimer;
};
