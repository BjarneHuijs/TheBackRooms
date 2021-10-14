// Fill out your copyright notice in the Description page of Project Settings.


#include "BloodMeter.h"

// Sets default values for this component's properties
UBloodMeter::UBloodMeter()
	: m_bEmpty(false)
	, m_MaxBlood{ 100.f }
	, m_Blood{ 10.f }
	, m_CurrentTier(BloodTiers::Tier_1)
	, m_HighestAchievedTier(BloodTiers::Tier_1)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	m_DecayValues.Add(BloodTiers::Tier_1, 0.5f);
	m_DecayValues.Add(BloodTiers::Tier_2, 0.75f);
	m_DecayValues.Add(BloodTiers::Tier_3, 1.f);
	m_DecayValues.Add(BloodTiers::Tier_4, 1.5f);
	m_DecayValues.Add(BloodTiers::Tier_5, 2.f);
}


// Called when the game starts
void UBloodMeter::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBloodMeter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// multiply delta time by decay value of highest achieved blood tier
	m_Blood -= DeltaTime * m_DecayValues[m_HighestAchievedTier]; 
	if (m_Blood <= 0.f)
	{
		// dead, end game and restart
		//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "Dead", true);
		m_bEmpty = true;
	}


	// check tier updates and highest tier
	if (m_Blood <= m_MaxBlood * 0.2f)
	{
		m_CurrentTier = BloodTiers::Tier_1;
		GEngine->AddOnScreenDebugMessage(0, 1, FColor::Green, "Tier 1", true);

	}
	else if (m_Blood <= m_MaxBlood * 0.4f)
	{
		m_CurrentTier = BloodTiers::Tier_2;
		GEngine->AddOnScreenDebugMessage(0, 1, FColor::Green, "Tier 2", true);
	}
	else if (m_Blood <= m_MaxBlood * 0.6f)
	{
		m_CurrentTier = BloodTiers::Tier_3;
		GEngine->AddOnScreenDebugMessage(0, 1, FColor::Green, "Tier 3", true);
	}
	else if (m_Blood <= m_MaxBlood * 0.8f)
	{
		m_CurrentTier = BloodTiers::Tier_4;
		GEngine->AddOnScreenDebugMessage(0, 1, FColor::Green, "Tier 4", true);
	}
	else
	{
		m_CurrentTier = BloodTiers::Tier_5;
		GEngine->AddOnScreenDebugMessage(0, 1, FColor::Green, "Tier 5", true);
	}

	if (m_CurrentTier > m_HighestAchievedTier)
	{
		m_HighestAchievedTier = m_CurrentTier;
	}
}

float UBloodMeter::GetMaxBlood() const
{
	return m_MaxBlood;
}

float UBloodMeter::GetBlood() const
{
	return m_Blood;
}

TMap<BloodTiers, float> UBloodMeter::GetDecayValues() const
{
	return m_DecayValues;
}

void UBloodMeter::AddBlood(float value)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "Added " + FString::SanitizeFloat(value) + " blood points");

	m_Blood += value;
	if(m_Blood >= m_MaxBlood)
	{
		m_Blood = m_MaxBlood;
	}
}

BloodTiers UBloodMeter::GetCurrentTier() const
{
	return m_CurrentTier;
}

BloodTiers UBloodMeter::GetHighestAchievedTier() const
{
	return m_HighestAchievedTier;
}

bool UBloodMeter::IsMeterEmpty()
{
	return m_bEmpty;
}

