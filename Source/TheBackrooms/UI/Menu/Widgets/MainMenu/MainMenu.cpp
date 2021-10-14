// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"



#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "../OptionsMenu/OptionsMenu.h"
#include "Slate/SceneViewport.h"
#include "TheBackrooms/Player/PlayerMonster.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	m_SelectedButton = 0;
	//m_pStartButton->OnClicked.AddDynamic(this, &UMainMenu::StartGame);
	//m_pOptionsButton->OnClicked.AddDynamic(this, &UMainMenu::OpenOptions);
	//m_pLeaderboardButton->OnClicked.AddDynamic(this, &UMainMenu::OpenLeaderBoard);
	//m_pExitButton->OnClicked.AddDynamic(this, &UMainMenu::ExitGame);
	
}

void UMainMenu::StartGame()
{
	//UGameplayStatics::OpenLevel(GetWorld(), "ShowcaseLevel");
	//GetWorld()->SetGameMode(FURL{"../../../"})
}

void UMainMenu::OpenOptions()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "Open Options");
	
	//this->SetIsEnabled(false);
	//this->SetVisibility(ESlateVisibility::Hidden);
	//auto options{ CreateWidget(this, UOptionsMenu::StaticClass(), "OptionsMenu") };
	//options->AddToViewport();
}

void UMainMenu::OpenLeaderBoard()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "Open LeaderBoard");
}

void UMainMenu::ExitGame()
{
	//const auto world{ GetWorld() };
	//UKismetSystemLibrary::QuitGame(world, world->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

int UMainMenu::GetSelectedButton() const
{
	return m_SelectedButton;
}

void UMainMenu::SetSelectedButton(int button)
{
	if (m_SelectedButton >= 0 && m_SelectedButton < 5)
	{
		m_SelectedButton = button;
	}
}

void UMainMenu::MoveSelectionUp()
{
	m_SelectedButton--;

	if(m_SelectedButton < 0)
	{
		m_SelectedButton = 4;
	}
	else if(m_SelectedButton >= 5)
	{
		m_SelectedButton = 0;
	}
}

void UMainMenu::MoveSelectionDown()
{
	m_SelectedButton++;

	if (m_SelectedButton < 0)
	{
		m_SelectedButton = 4;
	}
	else if (m_SelectedButton >= 5)
	{
		m_SelectedButton = 0;
	}
}

void UMainMenu::HandleFocusChange()
{
	switch (m_SelectedButton)
	{
	case 0:
		SetWidgetFocus(m_pStartButton);
		break;
	case 1:
		SetWidgetFocus(m_pOptionsButton);
		break;
	case 2:
		SetWidgetFocus(m_pLeaderboardButton);
		break;
	case 3:
		SetWidgetFocus(m_pCreditsButton);
		break;
	case 4:
		SetWidgetFocus(m_pExitButton);
		break;
		
	default:
		break;
	}
}

void UMainMenu::ResetButtonStyle_Implementation(UButton*)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "Reached bad implementation reset");
	//pButton->WidgetStyle.Normal.);
	//pButton->SetStyle();
}

void UMainMenu::ResetButtonStyles()
{
	ResetButtonStyle(m_pStartButton);
	ResetButtonStyle(m_pOptionsButton);
	ResetButtonStyle(m_pLeaderboardButton);
	ResetButtonStyle(m_pCreditsButton);
	ResetButtonStyle(m_pExitButton);
}

void UMainMenu::SetFocusedButton_Implementation(UButton* pButton)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "Reached bad implementation setfocus");
}

//void UMainMenu::SetWidgetFocus_Implementation(UButton* pButton)
void UMainMenu::SetWidgetFocus(UButton* pButton)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "Reached bad implementation");
	ResetButtonStyles();

	UWorld* world{ GetWorld() };
	if(world)
	{
		APlayerController* playerController{ world->GetFirstPlayerController() };
		if(playerController)
		{
			APlayerMonster* player{ Cast<APlayerMonster>(playerController->GetPawn()) };
			if(player)
			{
				if(player->GetUsingController())
				{
					SetFocusedButton(pButton);
				}else
				{
					FSceneViewport* port = world->GetGameViewport()->GetGameViewport();
					if(port)
					{
						port->SetUserFocus(true);
					}
				}
			}
		}
	}
}

int UMainMenu::GetGamepadMenuInput()
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
