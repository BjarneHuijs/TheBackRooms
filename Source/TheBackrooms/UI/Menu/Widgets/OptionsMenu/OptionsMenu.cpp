// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionsMenu.h"


#include "Components/Button.h"
#include "Components/PanelWidget.h"
#include "Sound/SoundClass.h"
#include "TheBackrooms/Player/PlayerMonster.h"
#include "Slate/SceneViewport.h"

void UOptionsMenu::NativeConstruct()
{
	Super::NativeConstruct();

	m_SelectedButton = 0;
	/*m_MasterVolume = 1.f;
	m_AmbientVolume = 1.f;
	m_PlayerVolume = 1.f;
	m_NPCVolume = 1.f;*/
	//m_pBackButton->OnClicked.AddDynamic(this, &UOptionsMenu::CloseOptions);
}

void UOptionsMenu::CloseOptions()
{
	/*auto parent{ GetParent() };
	
	
	RemoveFromViewport();
	RemoveFromParent();
	parent->SetVisibility(ESlateVisibility::Visible);
	parent->SetIsEnabled(true);*/
}

UUserWidget* UOptionsMenu::GetInvoker() const
{
	return m_pInvoker;
}

void UOptionsMenu::SetInvoker(UUserWidget* invoker)
{
	m_pInvoker = invoker;
}

void UOptionsMenu::SetSoundClassVolume(USoundClass* soundClass, float Volume) {
	if (soundClass) {
		soundClass->Properties.Volume = Volume;
	}
}

float UOptionsMenu::GetSoundClassVolume(const USoundClass* soundClass) {
	return soundClass->Properties.Volume;
}

int UOptionsMenu::GetSelectedButton() const
{
	return m_SelectedButton;
}

void UOptionsMenu::SetSelectedButton(int button)
{
	if (m_SelectedButton >= 0 && m_SelectedButton < 5)
	{
		m_SelectedButton = button;
	}
}

void UOptionsMenu::MoveSelectionUp()
{
	m_SelectedButton--;

	if (m_SelectedButton < 0)
	{
		m_SelectedButton = 4;
	}
	else if (m_SelectedButton >= 5)
	{
		m_SelectedButton = 0;
	}
}

void UOptionsMenu::MoveSelectionDown()
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

void UOptionsMenu::HandleFocusChange()
{
	switch (m_SelectedButton)
	{
	case 0:
		SetSliderFocus(m_pMasterVolumeSlider);
		//SetWidgetFocus(m_pStartButton);
		break;
	case 1:
		SetSliderFocus(m_pAmbientVolumeSlider);
		//SetWidgetFocus(m_pOptionsButton);
		break;
	case 2:
		SetSliderFocus(m_pPlayerVolumeSlider);
		//SetWidgetFocus(m_pLeaderboardButton);
		break;
	case 3:
		SetSliderFocus(m_pNPCVolumeSlider);
		//SetWidgetFocus(m_pBackButton);
		break;
	case 4:
		SetWidgetFocus(m_pBackButton);
		break;

	default:
		break;
	}
}

void UOptionsMenu::ResetButtonStyle_Implementation(UButton*)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "Reached bad implementation reset");
	//pButton->WidgetStyle.Normal.);
	//pButton->SetStyle();
}

void UOptionsMenu::ResetWidgetStyles()
{
	ResetSlider(m_pMasterVolumeSlider);
	ResetSlider(m_pAmbientVolumeSlider);
	ResetSlider(m_pPlayerVolumeSlider);
	ResetSlider(m_pNPCVolumeSlider);
	ResetButtonStyle(m_pBackButton);
}

void UOptionsMenu::SetFocusedButton_Implementation(UButton* pButton)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "Reached bad implementation setfocus");
}

//void UMainMenu::SetWidgetFocus_Implementation(UButton* pButton)
void UOptionsMenu::SetWidgetFocus(UButton* pButton)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "Reached bad implementation");
	ResetWidgetStyles();

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

void UOptionsMenu::SetSliderFocus(USlider* pSlider)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "Reached bad implementation");
	ResetWidgetStyles();

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
					SetFocusedSlider(pSlider);
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


void UOptionsMenu::SetFocusedSlider_Implementation(USlider* pSlider)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "Reached bad implementation setfocus slider");

}


void UOptionsMenu::ResetSlider_Implementation(USlider* pSlider)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "Reached bad implementation reset slider");
}

int UOptionsMenu::GetGamepadMenuInput()
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
