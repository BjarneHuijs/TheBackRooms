// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreSystemWidget.h"

#include "TheBackrooms/Player/PlayerMonster.h"
#include "TheBackrooms/Player/ScoreSystem.h"

void UScoreSystemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_pPlayer = Cast<APlayerMonster>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

int UScoreSystemWidget::GetPlayerTimeAlive() const
{
	//return 0.0f;
	return static_cast<int>(m_pPlayer->m_pScoreSystem->GetTotalTimeAlive());
}

int UScoreSystemWidget::GetTotalNrOfKills() const
{
	//return 0.0f;
	return m_pPlayer->m_pScoreSystem->GetNrOfKills() + m_pPlayer->m_pScoreSystem->GetNrOfPriestKills();
}

int UScoreSystemWidget::GetCurrentScore() const
{
	//return 0.0f;
	return m_pPlayer->m_pScoreSystem->GetCurrentScore();
}
