// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_Spawner.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "TheBackrooms/NPC/NPCBaseCharacter.h"
#include "TheBackrooms/NPC/WayPoint.h"
#include "TheBackrooms/Player/PlayerMonster.h"

// Sets default values
ANPC_Spawner::ANPC_Spawner()
	: m_SpawnTime(5.f)
	, m_SpawnTimer(0.f)
	, m_BaseNPCChance(90.f)
	, m_PriestNPCChance(10.f)
	, m_MaxNrOfNPCs(10)
	, m_PlayerSpawnRange(1000.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPC_Spawner::BeginPlay()
{
	Super::BeginPlay();

	const auto world{ GetWorld() };
	if (world)
	{
		UGameplayStatics::GetAllActorsOfClass(world, AWayPoint::StaticClass(), m_pWayPoints);
	}
}

// Called every frame
void ANPC_Spawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	m_SpawnTimer += DeltaTime;

	
	GEngine->AddOnScreenDebugMessage(12, 15.f, FColor::Green, L"time since spawn: " + FString::SanitizeFloat(m_SpawnTimer), true);
	if (m_SpawnTimer >= m_SpawnTime) 
	{
		APlayerMonster* player{};
		const auto world{ GetWorld() };
		if (world)
		{
			player = static_cast<APlayerMonster*>(world->GetFirstPlayerController()->GetPawn());
		}
		
		const FRandomStream spawnPointSelector{};
		int index = FMath::RandHelper(m_pWayPoints.Num());
		GEngine->AddOnScreenDebugMessage(14, 15.f, FColor::Red, L"Spawn at index: " + FString::SanitizeFloat(index), true);

		if (player) 
		{

			while(m_pWayPoints[index]->GetDistanceTo(player) <= m_PlayerSpawnRange)
			{
				//GEngine->AddOnScreenDebugMessage(25, 1.f, FColor::Green, L"Index: " + FString::SanitizeFloat(index) + L" was invalid, generating new one", true);
				index = FMath::RandHelper(m_pWayPoints.Num());
			}
			//GEngine->AddOnScreenDebugMessage(26, 15.f, FColor::Green, L"Index: " + FString::SanitizeFloat(index) + L" was valid", true);
			
			const auto spawnPoint = m_pWayPoints[index]->GetTransform();


			const float typeVal{ FMath::RandHelper(1000.f) / 10.f };
			if(typeVal <= m_PriestNPCChance)
			{
				SpawnNPC(NPCTypes::Priest, spawnPoint);
				//GEngine->AddOnScreenDebugMessage(13, 1.f, FColor::Green, TEXT("spawn Priest succeeded!!!"), true);
			}else
			{
				SpawnNPC(NPCTypes::Base, spawnPoint);
				//GEngine->AddOnScreenDebugMessage(13, 1.f, FColor::Green, TEXT("spawn succeeded!!!"), true);
			}
			
		}
		m_SpawnTimer = 0.f;
	}
	
	const auto world{ GetWorld() };
	if (world)
	{
		APlayerController* player{ world->GetFirstPlayerController() };
		if(player)
		{
			const BloodTiers bestTier{ static_cast<APlayerMonster*>(player->GetPawn())->m_pBloodMeter->GetHighestAchievedTier() };

			switch(bestTier)
			{
			case BloodTiers::Tier_1:
				m_BaseNPCChance = 95.f;
				m_PriestNPCChance = 5.f;

				break;
			case BloodTiers::Tier_2:
				m_BaseNPCChance = 85.f;
				m_PriestNPCChance = 15.f;

				break;
			case BloodTiers::Tier_3:
				m_BaseNPCChance = 70.f;
				m_PriestNPCChance = 30.f;

				break;
			case BloodTiers::Tier_4:
				m_BaseNPCChance = 60.f;
				m_PriestNPCChance = 40.f;

				break;
			case BloodTiers::Tier_5:
				m_BaseNPCChance = 50.f;
				m_PriestNPCChance = 50.f;

				break;
			default: 
				GEngine->AddOnScreenDebugMessage(13, 1.f, FColor::Green, TEXT("Invalid Tier"), true);
				break;
			}
		}
		
		const float playTime{ world->TimeSeconds };
		if(static_cast<int>(playTime) % 60 == 0 && playTime >= 30.f)
		{
			
			m_BaseNPCChance -= 0.05f;
			if(m_BaseNPCChance < 0.5f)
			{
				m_BaseNPCChance = 0.5f;
			}

			m_PriestNPCChance += 0.05f;
			if(m_PriestNPCChance > 0.5f)
			{
				m_PriestNPCChance = 0.5f;
			}
		}
	}

	GEngine->AddOnScreenDebugMessage(20, 15.f, FColor::Red, L"Current Base spawn: " + FString::SanitizeFloat(m_BaseNPCChance) + L"%", true);
	GEngine->AddOnScreenDebugMessage(21, 15.f, FColor::Red, L"Current Priest spawn: " + FString::SanitizeFloat(m_PriestNPCChance) + L"%", true);

}

void ANPC_Spawner::SpawnNPC_Implementation(NPCTypes, FTransform)
{
	GEngine->AddOnScreenDebugMessage(13, 1.f, FColor::Green, TEXT("Did not spawn, called wrong spawner"), true);
}
