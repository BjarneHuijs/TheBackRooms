// Fill out your copyright notice in the Description page of Project Settings.
#include "NewRecordWidget.h"


#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "TheBackrooms/Leaderboard/LeaderBoard.h"
#include "TheBackrooms/Player/PlayerMonster.h"
#include "Slate/SceneViewport.h"

void UNewRecordWidget::NativeConstruct()
{
	Super::NativeConstruct();
	m_SelectedButton = 0;

	//m_pBackButton->OnClicked.AddDynamic(this, &UOptionsMenu::CloseOptions);
}

void UNewRecordWidget::SaveScore()
{
    //USaveGame* saveGame{ UGameplayStatics::CreateSaveGameObject(ULeaderBoard::StaticClass()) };
    //ULeaderBoard* leaderBoard = Cast<ULeaderBoard>(saveGame);
    if(m_pLeaderBoard)
    {
        // Set data on the savegame object.
        //leaderboard->SetPlayerName(TEXT("PlayerOne"));
        const FPlayerRecord newRecord{ m_pNameInputField->GetText().ToString(), m_TimeSurvived, m_AttainedScore };
        m_pLeaderBoard->SaveNewScore(newRecord);
    	
        // Save the data immediately.
        if (UGameplayStatics::SaveGameToSlot(m_pLeaderBoard, m_pLeaderBoard->GetSaveSlotName(), m_pLeaderBoard->GetUserIndex()))
        {
            // Save succeeded.
			GEngine->AddOnScreenDebugMessage(50, 1, FColor::Orange, "Saved record");
            UGameplayStatics::OpenLevel(GetWorld(), "LeaderboardLevel");
        }else
        {
            GEngine->AddOnScreenDebugMessage(50, 1, FColor::Orange, "Save record failed");
        }
    }
}

void UNewRecordWidget::DontSaveScore()
{
	UGameplayStatics::OpenLevel(GetWorld(), "LeaderboardLevel");
}

void UNewRecordWidget::SetNewRecordValues(ULeaderBoard* board, int score, int time)
{
    m_AttainedScore = score;
    m_TimeSurvived = time;
    m_pLeaderBoard = board;
}

int UNewRecordWidget::GetTimeAlive() const
{
    return m_TimeSurvived;
}

int UNewRecordWidget::GetCurrentScore() const
{
    return m_AttainedScore;
}

int UNewRecordWidget::GetSelectedButton() const
{
	return m_SelectedButton;
}

void UNewRecordWidget::SetSelectedButton(int button)
{
	if (m_SelectedButton >= 0 && m_SelectedButton < 4)
	{
		m_SelectedButton = button;
	}
}

void UNewRecordWidget::MoveSelectionUp()
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

void UNewRecordWidget::MoveSelectionDown()
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

void UNewRecordWidget::HandleFocusChange()
{
	switch (m_SelectedButton)
	{
	case 0:
		SetInputFocus(m_pNameInputField);
		break;
	case 1:
		SetWidgetFocus(m_pSaveScoreButton);
		break;
	case 2:
		SetWidgetFocus(m_pDontSaveScoreButton);
		break;
	case 3:
		SetWidgetFocus(m_pRestartButton);
		break;

	default:
		break;
	}
}

void UNewRecordWidget::ResetButtonStyle_Implementation(UButton*)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "NewRecord: Reached bad implementation reset button");
	//pButton->WidgetStyle.Normal.);
	//pButton->SetStyle();
}

void UNewRecordWidget::ResetInputStyle_Implementation(UEditableTextBox*)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "NewRecord: Reached bad implementation resetstyle input");
}

void UNewRecordWidget::SetFocusedButton_Implementation(UButton*)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "NewRecord: Reached bad implementation button setfocus");
}

void UNewRecordWidget::SetFocusedInputBox_Implementation(UEditableTextBox*)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "NewRecord: Reached bad implementation input setfocus");
}

void UNewRecordWidget::ResetButtonStyles()
{
	ResetButtonStyle(m_pSaveScoreButton);
	ResetButtonStyle(m_pDontSaveScoreButton);
	ResetButtonStyle(m_pRestartButton);
}

void UNewRecordWidget::ResetWidgetStyles()
{

	ResetInputStyle(m_pNameInputField);
	ResetButtonStyles();
	
}

int UNewRecordWidget::GetGamepadMenuInput()
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

			if (yInput >= 0.7f)
			{
				// up direction input
				return 0;
			}

			if (playerController->WasInputKeyJustPressed(upKey))
			{
				// up direction input D-Pad
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

void UNewRecordWidget::SetWidgetFocus(UButton* pButton)
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

void UNewRecordWidget::SetInputFocus(UEditableTextBox* pTextBox)
{
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
					SetFocusedInputBox(pTextBox);
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
