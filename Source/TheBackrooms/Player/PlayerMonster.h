// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "BloodMeter/BloodMeter.h"
#include "GameFramework/Character.h"
#include "PlayerMonster.generated.h"

class UScoreSystem;
class APlayerClaw;
//class UBloodMeter;
class USpringArmComponent;
class UCameraComponent;
UCLASS()
class THEBACKROOMS_API APlayerMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		bool GetCanPhaseThroughWall() const;
#pragma region Object Components
	//UPROPERTY(EditAnywhere) // Default cube for testing purposes
	//	UStaticMeshComponent* m_VisibleComponent;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		UCameraComponent* m_pCamera;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		USpringArmComponent* m_pArm;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite) // attachment socket for attack hitbox
		USceneComponent* m_pAttachment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) // attachment socket position (temp)
		FVector m_AttachmentPosition;

	UPROPERTY(BlueprintReadWrite)
		APlayerClaw* m_pClaw;
#pragma endregion
	
	UPROPERTY(EditAnywhere)
		UBloodMeter* m_pBloodMeter;
	UPROPERTY(EditAnywhere)
		UScoreSystem* m_pScoreSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector m_MeshScale;
	
	UFUNCTION()
		float GetClawAttackTime() const;
	UFUNCTION()
		float GetAttackTimeToLive() const;
	UFUNCTION(BlueprintCallable)
		float GetBloodMeterPercentFill() const;
	UFUNCTION(BlueprintCallable)
		BloodTiers GetBloodMeterCurrentTier() const;
	UFUNCTION()
		void AddBlood(float bloodValue) const;

	UFUNCTION(BlueprintGetter)
		bool IsDying() const;

	UFUNCTION(BlueprintGetter)
		bool IsDead() const;

	UFUNCTION(BlueprintCallable)
		void CheckGamePadInUse(FKey key);
	
	UFUNCTION(BlueprintGetter)
		bool GetUsingController() const;

	UFUNCTION(BlueprintGetter)
		float GetDashCooldownTime() const;

	UFUNCTION(BlueprintGetter)
		float GetDashCooldownTimer() const;
	UFUNCTION(BlueprintSetter)
		void SetDashCooldownTimer(float newValue);

	UFUNCTION(BlueprintGetter)
		float GetDashDistance() const;

	UFUNCTION(BlueprintGetter)
		bool IsSprinting() const;
	UFUNCTION(BlueprintGetter)
		bool CanSprint() const;
	UFUNCTION(BlueprintSetter)
		void SetCanSprint(bool canSprint);

	UFUNCTION(BlueprintGetter)
		float GetMaxAttackTime() const;

	UFUNCTION(BlueprintGetter)
		bool IsAttacking() const;
	UFUNCTION(BlueprintSetter)
		void SetIsAttacking(bool attacking);

private:
#pragma region Sprint Variables
	UPROPERTY(EditAnywhere, BlueprintGetter = GetDashCooldownTime, Category = "Dash")
		float m_DashCooldownTime;
	UPROPERTY(EditAnywhere, BlueprintGetter = GetDashCooldownTimer, BlueprintSetter = SetDashCooldownTimer, Category = "Dash")
		float m_DashCooldownTimer;

	UPROPERTY(EditAnywhere, BlueprintGetter = GetDashDistance, Category = "Dash")
		float m_DashDistance;

	UPROPERTY(BlueprintGetter = IsSprinting, Category = "Dash")
		bool m_bIsSprinting;
	UPROPERTY(BlueprintGetter = CanSprint, BlueprintSetter = SetCanSprint, Category = "Dash")
		bool m_bCanSprint;
#pragma endregion


	UPROPERTY(EditAnywhere, BlueprintGetter = GetMaxAttackTime)
		float m_AttackTime;

	UPROPERTY(BlueprintGetter = IsAttacking, BlueprintSetter = SetIsAttacking)
		bool m_bIsAttacking;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float m_MovementSpeed;

	UPROPERTY()
		bool m_bCanPhaseThroughWall;
	
	UPROPERTY(BlueprintGetter = IsDead)
		bool m_bIsDead;

	UPROPERTY(BlueprintGetter = IsDying)
		bool m_bIsDying;

	UPROPERTY(EditAnywhere)
		bool m_bDebugMode;

	UPROPERTY()
		float m_DeathAnimationTime;

	UPROPERTY()
		float m_DeathTimer;

	UPROPERTY(BlueprintGetter = GetUsingController)
		bool m_bUsingController;
	
	UFUNCTION()
		void CheckAbilityUnlocks();

	UFUNCTION()
		void MoveAlongXAxis(float axisValue);
	UFUNCTION()
		void MoveAlongYAxis(float axisValue);
	UFUNCTION()
		void Dash();
	UFUNCTION()
		void Attack();
	UFUNCTION()
		void Die();
	UFUNCTION()
		void Pause();
	UFUNCTION()
		void LockDoors();

};