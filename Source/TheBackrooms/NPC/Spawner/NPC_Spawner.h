// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPC_Spawner.generated.h"

class ANPCBaseCharacter;

UENUM(BlueprintType)
enum class NPCTypes : uint8
{
	Base UMETA(DisplayName = "Base NPC"),
	Priest UMETA(DisplayName = "Priest NPC")
};

UCLASS()
class THEBACKROOMS_API ANPC_Spawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPC_Spawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<class ANPCBaseCharacter> m_BaseNPCClass;

	UFUNCTION(BlueprintNativeEvent)
		void SpawnNPC(NPCTypes type, FTransform spawnTransform);
	
private:
	UPROPERTY(EditAnywhere)
		float m_SpawnTime;
	UPROPERTY()
		float m_SpawnTimer;

	UPROPERTY(EditAnywhere)
		float m_BaseNPCChance;
	UPROPERTY(EditAnywhere)
		float m_PriestNPCChance;

	UPROPERTY(EditAnywhere)
		int m_MaxNrOfNPCs;
	
	UPROPERTY(EditAnywhere)
		float m_PlayerSpawnRange;

	UPROPERTY()
		TArray<AActor*> m_pWayPoints;

	UPROPERTY()
		UBlueprint* m_pNPCBaseBP;
};
