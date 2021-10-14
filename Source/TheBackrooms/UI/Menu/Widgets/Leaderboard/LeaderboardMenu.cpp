// Fill out your copyright notice in the Description page of Project Settings.


#include "LeaderboardMenu.h"


#include "Components/Button.h"
#include "TheBackrooms/Leaderboard/LeaderBoard.h"
#include "Kismet/GameplayStatics.h"
#include "Slate/SceneViewport.h"
#include "TheBackrooms/Player/PlayerMonster.h"

void ULeaderboardMenu::NativeConstruct()
{
	Super::NativeConstruct();

	m_SelectedButton = 0;
	//m_bPaused = false;
	//m_pBackButton->OnClicked.AddDynamic(this, &UOptionsMenu::CloseOptions);
	//LoadLeaderboard();
}

void ULeaderboardMenu::CloseLeaderBoard()
{
	/*auto parent{ GetParent() };


	RemoveFromViewport();
	RemoveFromParent();
	parent->SetVisibility(ESlateVisibility::Visible);
	parent->SetIsEnabled(true);*/
}

UUserWidget* ULeaderboardMenu::GetInvoker() const
{
	return m_pInvoker;
}

void ULeaderboardMenu::SetInvoker(UUserWidget* invoker, bool paused)
{
	m_pInvoker = invoker;
	m_bPaused = paused;
}

void ULeaderboardMenu::LoadLeaderboard()
{
	const FString slotName = TEXT("Leaderboard");
	const uint32 userIndex = 0;
	
	//Retrieve and cast the USaveGame object to UMySaveGame.
	USaveGame* saveGame{ UGameplayStatics::LoadGameFromSlot(slotName, userIndex) };
	ULeaderBoard* loadedGame = Cast<ULeaderBoard>(saveGame);
	if(loadedGame)
	{
	    // The operation was successful, so LoadedGame now contains the data we saved earlier.
	    //UE_LOG(LogTemp, Warning, TEXT("LOADED: %s %s %s"), LoadedGame->GetHighestRecord().PlayerName, LoadedGame->GetHighestRecord().PlayerScore, LoadedGame->GetHighestRecord().PlayerTime);
		TArray<FPlayerRecord> records{ loadedGame->GetRecords() };
		for(FPlayerRecord record : records)
		{
			//UE_LOG(LogTemp, Warning, TEXT("LOADED: %s %s %s"), LoadedGame->GetHighestRecord().PlayerName, LoadedGame->GetHighestRecord().PlayerScore, LoadedGame->GetHighestRecord().PlayerTime);
			FDisplayRecord displayRecord{ record.PlayerName, record.PlayerScore, record.PlayerTime };
			m_records.Add(displayRecord);

		}
	}
}

TArray<FDisplayRecord> ULeaderboardMenu::GetRecords() const
{
	return m_records;
}

int ULeaderboardMenu::GetSelectedButton() const
{
	return m_SelectedButton;
}

void ULeaderboardMenu::SetSelectedButton(int button)
{
	if (m_SelectedButton >= 0 && m_SelectedButton < 2)
	{
		m_SelectedButton = button;
	}
}

void ULeaderboardMenu::MoveSelectionUp()
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

void ULeaderboardMenu::MoveSelectionDown()
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

void ULeaderboardMenu::HandleFocusChange()
{
	switch (m_SelectedButton)
	{
	case 0:
		SetWidgetFocus(m_pStartGameButton);
		break;
	case 1:
		SetWidgetFocus(m_pBackButton);
		break;

	default:
		break;
	}
}

void ULeaderboardMenu::ResetButtonStyle_Implementation(UButton*)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "Leaderboard: Reached bad implementation reset");
	//pButton->WidgetStyle.Normal.);
	//pButton->SetStyle();
}

void ULeaderboardMenu::ResetButtonStyles()
{
	ResetButtonStyle(m_pStartGameButton);
	ResetButtonStyle(m_pBackButton);
}

int ULeaderboardMenu::GetGamepadMenuInput()
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

void ULeaderboardMenu::CheckGameState()
{
	if (m_bPaused)
	{
		//m_pStartGameButton->SetIsEnabled(false);
		m_pStartGameButton->SetVisibility(ESlateVisibility::Hidden);
		//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "Leaderboard: Game paused, cannot start new game when one already is in progress");
		m_SelectedButton = 0;
	}
}

bool ULeaderboardMenu::GetPaused() const
{
	return m_bPaused;
}

void ULeaderboardMenu::SetFocusedButton_Implementation(UButton* pButton)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "Leaderboard: Reached bad implementation setfocus");
}

//void UMainMenu::SetWidgetFocus_Implementation(UButton* pButton)
void ULeaderboardMenu::SetWidgetFocus(UButton* pButton)
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
