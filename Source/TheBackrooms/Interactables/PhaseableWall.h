// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhaseableWall.generated.h"

class UMaterialInstance;
UCLASS()
class THEBACKROOMS_API APhaseableWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APhaseableWall();

	UFUNCTION()
		void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
		//void OnBeginOverlap(class UPrimitiveComponent* OverlapComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintGetter)
		bool GetActive() const;
	UFUNCTION(BlueprintCallable)
		void Toggle(bool state);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* m_pWallMesh;

	UPROPERTY(VisibleAnywhere)
		UShapeComponent* m_pColliderBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* m_pExit_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector m_ExitPos_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* m_pExit_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector m_ExitPos_2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UMaterialInstance* m_pActiveMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UMaterialInstance* m_pInActiveMaterial;

	UFUNCTION(BlueprintNativeEvent)
		void SwapMaterial(bool active);

private:
	UPROPERTY(BlueprintGetter=GetActive)
		bool m_bActive;

};
