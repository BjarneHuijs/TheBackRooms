// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterHUD.h"

#include "Widgets/BloodMeter/BloodMeterWidget.h"
#include "Widgets/Ability/AbilityWidget.h"

AMonsterHUD::AMonsterHUD(const FObjectInitializer& ObjectIn)
	: Super(ObjectIn)
{
	//bloodMeterWidget->AddToViewport();
}

void AMonsterHUD::OnConstruction(const FTransform& Transform)
{
	const auto owner = GetWorld()->GetFirstPlayerController();
	SetOwner(owner);

	//m_pBloodMeterWidget = CreateWidget<UBloodMeterWidget>(owner, UBloodMeterWidget::StaticClass());
	//if (m_pBloodMeterWidget)
	//{
	//	m_pBloodMeterWidget->AddToViewport();
	//}

	//m_pAbilityWidget = CreateWidget<UAbilityWidget>(owner, UAbilityWidget::StaticClass());
	//if (m_pAbilityWidget)
	//{
	//	m_pAbilityWidget->AddToViewport();
	//}
}

//void AMonsterHUD::BeginPlay()
//{
//	const auto owner = GetOwner();
//	
//
//}
