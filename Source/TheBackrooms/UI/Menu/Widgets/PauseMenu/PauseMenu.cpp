// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"

#include "Kismet/GameplayStatics.h"
#include "Slate/SceneViewport.h"
#include "TheBackrooms/Player/PlayerMonster.h"

void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	m_SelectedButton = 0;
}

int UPauseMenu::GetSelectedButton() const
{
	return m_SelectedButton;
}

void UPauseMenu::SetSelectedButton(int button)
{
	if (m_SelectedButton >= 0 && m_SelectedButton < 4)
	{
		m_SelectedButton = button;
	}
}

void UPauseMenu::MoveSelectionUp()
{
	m_SelectedButton--;

	if (m_SelectedButton < 0)
	{
		m_SelectedButton = 3;
	}
	else if (m_SelectedButton >= 4)
	{
		m_SelectedButton = 0;
	}
}

void UPauseMenu::MoveSelectionDown()
{
	m_SelectedButton++;

	if (m_SelectedButton < 0)
	{
		m_SelectedButton = 3;
	}
	else if (m_SelectedButton >= 4)
	{
		m_SelectedButton = 0;
	}
}

void UPauseMenu::HandleFocusChange()
{
	switch (m_SelectedButton)
	{
	case 0:
		SetWidgetFocus(m_pResumeButton);
		break;
	case 1:
		SetWidgetFocus(m_pLeaderboardButton);
		break;
	case 2:
		SetWidgetFocus(m_pOptionsButton);
		break;
	case 3:
		SetWidgetFocus(m_pExitButton);
		break;

	default:
		break;
	}
}

void UPauseMenu::ResetButtonStyle_Implementation(UButton*)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "Pause: Reached bad implementation reset");
	//pButton->WidgetStyle.Normal.);
	//pButton->SetStyle();
}

void UPauseMenu::ResetButtonStyles()
{
	ResetButtonStyle(m_pResumeButton);
	ResetButtonStyle(m_pOptionsButton);
	ResetButtonStyle(m_pLeaderboardButton);
	ResetButtonStyle(m_pExitButton);
}

int UPauseMenu::GetGamepadMenuInput()
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
			
			if(yInput >= 0.7f)
			{
				// up direction input
				return 0;
			}

			if(playerController->WasInputKeyJustPressed(upKey))
			{
				// up direction input D-Pad
				return 0;
			}

			if(yInput <= -0.7f || playerController->WasInputKeyJustPressed(downKey))
			{
				// down direction input
				return 1;
			}
		}
	}

	return -1;
}

void UPauseMenu::SetFocusedButton_Implementation(UButton* pButton)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "Pause: Reached bad implementation setfocus");
}

//void UMainMenu::SetWidgetFocus_Implementation(UButton* pButton)
void UPauseMenu::SetWidgetFocus(UButton* pButton)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "Reached bad implementation");
	ResetButtonStyles();

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
