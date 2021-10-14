// Fill out your copyright notice in the Description page of Project Settings.


#include "BloodMeterWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Border.h"
#include "TheBackrooms/Player/PlayerMonster.h"

void UBloodMeterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//m_pBloodMeter->AddBinding()
	//pButton->OnClicked.AddDynamic(this, &UBloodMeterWidget::ButtonClicked);
	m_pPlayer = Cast<APlayerMonster>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

float UBloodMeterWidget::GetBloodBarFillPercentage() const
{
	return m_pPlayer->GetBloodMeterPercentFill();
}

FLinearColor UBloodMeterWidget::GetCurrentBloodTier1() const
{
	const auto tier{ m_pPlayer->GetBloodMeterCurrentTier() };
	if(tier == BloodTiers::Tier_1)
	{
		return m_pTier1->ContentColorAndOpacity = { 1.f, 165.f / 255.f, 0.f, 1.f };
	}
	return { 105.f / 255.f,105.f / 255.f,105.f / 255.f, 1.f };
}

FLinearColor UBloodMeterWidget::GetCurrentBloodTier2() const
{
	const auto tier{ m_pPlayer->GetBloodMeterCurrentTier() };
	if(tier == BloodTiers::Tier_2)
	{
		return m_pTier1->ContentColorAndOpacity = { 1.f, 165.f / 255.f, 0.f, 1.f };
	}
	return { 105.f / 255.f,105.f / 255.f,105.f / 255.f, 1.f };
}

FLinearColor UBloodMeterWidget::GetCurrentBloodTier3() const
{
	const auto tier{ m_pPlayer->GetBloodMeterCurrentTier() };
	if(tier == BloodTiers::Tier_3)
	{
		return m_pTier1->ContentColorAndOpacity = { 1.f, 165.f / 255.f, 0.f, 1.f };
	}
	return { 105.f / 255.f,105.f / 255.f,105.f / 255.f, 1.f };
}

FLinearColor UBloodMeterWidget::GetCurrentBloodTier4() const
{
	const auto tier{ m_pPlayer->GetBloodMeterCurrentTier() };
	if(tier == BloodTiers::Tier_4)
	{
		return m_pTier1->ContentColorAndOpacity = { 1.f, 165.f / 255.f, 0.f, 1.f };
	}
	return { 105.f / 255.f,105.f / 255.f,105.f / 255.f, 1.f };
}

FLinearColor UBloodMeterWidget::GetCurrentBloodTier5() const
{
	const auto tier{ m_pPlayer->GetBloodMeterCurrentTier() };
	if(tier == BloodTiers::Tier_5)
	{
		return m_pTier1->ContentColorAndOpacity = { 1.f, 165.f / 255.f, 0.f, 1.f };
	}
	return { 105.f / 255.f,105.f / 255.f,105.f / 255.f, 1.f };
}

