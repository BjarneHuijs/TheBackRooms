// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerClaw.generated.h"

UCLASS()
class THEBACKROOMS_API APlayerClaw : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerClaw();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintSetter)
		void SetTimeToLive(float ttl);
	UFUNCTION(BlueprintGetter)
		float GetTimeAlive() const;
	
	UFUNCTION(BlueprintGetter)
		bool CanAttack() const;

	UFUNCTION()
		void StartAttack();
	UFUNCTION()
		void EndAttack();

	UFUNCTION()
		void SetDebugMode(bool mode);
	
	UFUNCTION(BlueprintGetter)
		float GetTimeToLive() const;

private:

	UPROPERTY(BlueprintGetter = GetTimeAlive)
		float m_TimeAlive;

	UPROPERTY(BlueprintGetter = GetTimeToLive, BlueprintSetter = SetTimeToLive)
		float m_TimeToLive;

	UPROPERTY(BlueprintGetter = CanAttack)
		bool m_bCanAttack;


	UPROPERTY(VisibleAnywhere)
		UShapeComponent* m_pColliderBox;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* m_pVisibleComponent;

	UPROPERTY()
		bool m_bDebugMode;
};
