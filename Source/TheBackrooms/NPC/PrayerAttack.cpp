// Fill out your copyright notice in the Description page of Project Settings.


#include "PrayerAttack.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "TheBackrooms/Player/PlayerMonster.h"


// Sets default values
APrayerAttack::APrayerAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APrayerAttack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APrayerAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_CanAttack)
	{
		m_CurrentCastingTime += DeltaTime;
	/*	FString TheFloat = FString::SanitizeFloat(m_CurrentCastingTime);
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Orange, TheFloat, false);*/
	}

	if (m_HasAttacked)
	{
		m_CurrentCooldownTime += DeltaTime;
		/*FString TheFloatStr = FString::SanitizeFloat(m_CurrentCooldownTime);
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Emerald, TheFloatStr , false);*/
	}
	if (m_CurrentCooldownTime >= Cooldowntime)
	{
		m_CanAttack = true;
		m_HasAttacked = false;
		m_CurrentCooldownTime = 0.f;
	}
}

void APrayerAttack::StartAttack()
{
	
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "Prayer STARTATTACK()");
	m_CanAttack = true;
	
	//APlayerMonster* player = Cast<APlayerMonster>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	APlayerMonster* player = Cast<APlayerMonster>(GetWorld()->GetFirstPlayerController()->GetPawn());

	
	if (player)
	{
		if (m_CurrentCastingTime >= Castingtime)
		{
			player->m_pBloodMeter->AddBlood(DamageAmount);
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "PRIEST ATTACKED ");
			m_CurrentCastingTime = 0;
			EndAttack();
		}
		
	}
	
	
	
	
}

void APrayerAttack::EndAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "Prayer Attack ended");
	m_CurrentCastingTime = 0.f;
	m_HasAttacked = true;
	m_CanAttack = false;
}

void APrayerAttack::Reset()
{
	m_CurrentCooldownTime = 0.f;
	m_CurrentCastingTime = 0.f;
	m_CanAttack = false;
	m_HasAttacked = false;
}

bool APrayerAttack::HasAttacked()
{
	return m_HasAttacked;
}

