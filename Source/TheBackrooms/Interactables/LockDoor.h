// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LockDoor.generated.h"

UCLASS()
class THEBACKROOMS_API ALockDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALockDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void CloseDoor();
	UFUNCTION()
	void OpenDoor();
	UFUNCTION(BlueprintGetter)
	bool IsClosed();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* m_pDoorMesh;

	UFUNCTION(BlueprintGetter)
		float GetTimeClosed() const;
	UFUNCTION(BlueprintSetter)
		void SetTimeClosed(float closeTime);

	UFUNCTION(BlueprintGetter)
		float GetLockRadius() const;
	UFUNCTION(BlueprintSetter)
		void SetLockRadius(float radius);
private:
	UPROPERTY(EditAnywhere, BlueprintGetter = GetTimeClosed, BlueprintSetter = SetTimeClosed, Category = Doors)
		float m_TimeClosed = 5.f;
	UPROPERTY(EditAnywhere, BlueprintGetter = GetLockRadius, BlueprintSetter = SetLockRadius, Category = Doors)
		float m_RadiusToLock = 1000.f;
	
	UPROPERTY(BlueprintGetter = IsClosed)
	bool m_IsClosed;
	UPROPERTY()
	float m_CurrentTimeClosed ;
};
