// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityWidget.h"

#include "TheBackrooms/Player/PlayerMonster.h"

void UAbilityWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_pPlayer = Cast<APlayerMonster>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

float UAbilityWidget::GetDashCooldownPercentage() const
{
	return (m_pPlayer->GetDashCooldownTimer() / m_pPlayer->GetDashCooldownTime());
}

float UAbilityWidget::GetAttackCooldownPercentage() const
{
	return (m_pPlayer->GetClawAttackTime() / m_pPlayer->GetAttackTimeToLive());
}

bool UAbilityWidget::GetCanPhaseThroughWalls() const
{
	return m_pPlayer->GetCanPhaseThroughWall();
}

bool UAbilityWidget::WasLastInputController() const
{
	return m_bLastInputwasController;
}

void UAbilityWidget::CheckLastInputType()
{
	UWorld* world{ GetWorld() };
	if (world)
	{
		APlayerController* playerController{ world->GetFirstPlayerController() };
		if (playerController)
		{
			TArray<FKey> keys{};
			EKeys::GetAllKeys(keys);
			for (const FKey key : keys)
			{
				if (playerController->IsInputKeyDown(key))
				{
					if (key.IsGamepadKey())
					{
						m_bLastInputwasController = true;
						return;
					}

					m_bLastInputwasController = false;
					return;
				}
			}
		}
	}
}
