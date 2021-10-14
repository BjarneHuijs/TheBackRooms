// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreSystem.h"

#include "PlayerMonster.h"

// Sets default values for this component's properties
UScoreSystem::UScoreSystem()
	: m_NrOfKills(0)
	, m_KillScoreValue(25)
	, m_NrOfPriestKills(0)
	, m_PriestKillScoreValue(50)
	, m_TotalTimeAlive(0.f)
	, m_CurrentScore(0)
	, m_BloodMultiplierValues({1.f, 1.1f, 1.5f, 2.f, 3.f})
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UScoreSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UScoreSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	const auto player = Cast<APlayerMonster>(GetOwner());
	if(player)
	{
		if(!player->IsDying())
		{
			m_TotalTimeAlive += DeltaTime;

			const BloodTiers currentPlayerTier{ player->GetBloodMeterCurrentTier() };
			if(m_HighestTier == currentPlayerTier)
			{
				m_TimeHeldHighestTier += DeltaTime;
			}
			else if(currentPlayerTier > m_HighestTier)
			{
				m_HighestTier = currentPlayerTier;
			}
		}
		else
		{
			CalculateFinalScore();
		}
	}

	m_CurrentScore = static_cast<int>(m_TotalTimeAlive);
	const int killScore{ (m_NrOfKills * m_KillScoreValue) + (m_NrOfPriestKills * m_PriestKillScoreValue) };
	m_CurrentScore += ( killScore * m_BloodMultiplierValues[static_cast<int>(m_HighestTier)] );
	m_CurrentScore += (m_TimeHeldHighestTier * m_BloodMultiplierValues[static_cast<int>(m_HighestTier)]);
}

int UScoreSystem::GetCurrentScore() const
{
	return m_CurrentScore;
}

int UScoreSystem::GetFinalScore() const
{
	return m_FinalScore;
}

int UScoreSystem::GetNrOfKills() const
{
	return m_NrOfKills;
}

int UScoreSystem::GetNrOfPriestKills() const
{
	return m_NrOfPriestKills;
}

float UScoreSystem::GetTotalTimeAlive() const
{
	return m_TotalTimeAlive;
}

void UScoreSystem::NPCWasKilled(float NPCValue)
{
	if (NPCValue >= 15.f)
	{
		m_NrOfPriestKills++;
	}
	else
	{
		m_NrOfKills++;
	}
}

void UScoreSystem::CalculateFinalScore()
{
	m_FinalScore = m_CurrentScore * m_BloodMultiplierValues[static_cast<int>(m_HighestTier)];
}


