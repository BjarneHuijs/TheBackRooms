// Fill out your copyright notice in the Description page of Project Settings.


#include "CreditsMenu.h"

#include "TheBackrooms/Player/PlayerMonster.h"
#include "Slate/SceneViewport.h"
#include "Components/Button.h"

void UCreditsMenu::NativeConstruct()
{
	Super::NativeConstruct();

	m_SelectedButton = 0;
}

UUserWidget* UCreditsMenu::GetInvoker() const
{
	return m_pInvoker;
}

void UCreditsMenu::SetInvoker(UUserWidget* invoker)
{
	m_pInvoker = invoker;
}

int UCreditsMenu::GetSelectedButton() const
{
	return m_SelectedButton;
}

void UCreditsMenu::SetSelectedButton(int button)
{
	if (m_SelectedButton >= 0 && m_SelectedButton < 2)
	{
		m_SelectedButton = button;
	}
}

void UCreditsMenu::MoveSelectionUp()
{
	m_SelectedButton--;

	if (m_SelectedButton < 0)
	{
		m_SelectedButton = 1;
	}
	else if (m_SelectedButton >= 2)
	{
		m_SelectedButton = 0;
	}
}

void UCreditsMenu::MoveSelectionDown()
{
	m_SelectedButton++;

	if (m_SelectedButton < 0)
	{
		m_SelectedButton = 1;
	}
	else if (m_SelectedButton >= 2)
	{
		m_SelectedButton = 0;
	}
}

void UCreditsMenu::HandleFocusChange()
{
	switch (m_SelectedButton)
	{
	case 0:
		SetWidgetFocus(m_pBackButton);
		break;
	case 1:
		SetWidgetFocus(nullptr);
		break;
	default:
		break;
	}
}

void UCreditsMenu::ResetButtonStyle_Implementation(UButton*)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "Reached bad implementation reset");
	//pButton->WidgetStyle.Normal.);
	//pButton->SetStyle();
}

void UCreditsMenu::ResetButtonStyles()
{
	ResetButtonStyle(m_pBackButton);
}

void UCreditsMenu::SetFocusedButton_Implementation(UButton* pButton)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "Reached bad implementation setfocus");
}

//void UMainMenu::SetWidgetFocus_Implementation(UButton* pButton)
void UCreditsMenu::SetWidgetFocus(UButton* pButton)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "Reached bad implementation");
	ResetButtonStyles();

	if(!pButton)
	{
		return;
	}
	
	UWorld* world{ GetWorld() };
	if (world)
	{
		APlayerController* playerController{ world->GetFirstPlayerController() };
		if (playerController)
		{
			APlayerMonster* player{ Cast<APlayerMonster>(playerController->GetPawn()) };
			if (player)
			{
				if (player->GetUsingController())
				{
					SetFocusedButton(pButton);
				}
				else
				{
					FSceneViewport* port = world->GetGameViewport()->GetGameViewport();
					if (port)
					{
						port->SetUserFocus(true);
					}
				}
			}
		}
	}
}

int UCreditsMenu::GetGamepadMenuInput()
{
	UWorld* world{ GetWorld() };
	if (world)
	{
		APlayerController* playerController{ world->GetFirstPlayerController() };
		if (playerController)
		{
			float xInput{};
			float yInput{};
			playerController->GetInputAnalogStickState(EControllerAnalogStick::CAS_LeftStick, xInput, yInput);

			const FKey upKey{ EKeys::Gamepad_DPad_Up };
			const FKey downKey{ EKeys::Gamepad_DPad_Down };

			if (yInput >= 0.7f || playerController->WasInputKeyJustPressed(upKey))
			{
				// up direction input
				return 0;
			}

			if (yInput <= -0.7f || playerController->WasInputKeyJustPressed(downKey))
			{
				// down direction input
				return 1;
			}
		}
	}

	return -1;
}
