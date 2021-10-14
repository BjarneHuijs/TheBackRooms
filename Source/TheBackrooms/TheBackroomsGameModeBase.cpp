// Copyright Epic Games, Inc. All Rights Reserved.


#include "TheBackroomsGameModeBase.h"



#include "Kismet/GameplayStatics.h"
#include "Player/PlayerMonster.h"
#include "Player/ScoreSystem.h"
#include "UI/HUD/MonsterHUD.h"
#include "TheBackrooms/Leaderboard/LeaderBoard.h"
#include "UI/Menu/Widgets/NewRecordMenu/NewRecordWidget.h"

ATheBackroomsGameModeBase::ATheBackroomsGameModeBase(const FObjectInitializer& ObjectIn)
	: Super(ObjectIn)
{
	HUDClass = AMonsterHUD::StaticClass();
}

void ATheBackroomsGameModeBase::BeginPlay()
{
	USaveGame* saveGame{ UGameplayStatics::LoadGameFromSlot("Leaderboard", 0) };
    ULeaderBoard* loadedGame = Cast<ULeaderBoard>(saveGame);
	if (!loadedGame)
	{
		ULeaderBoard* leaderboard = Cast<ULeaderBoard>(UGameplayStatics::CreateSaveGameObject(ULeaderBoard::StaticClass()));
		if (UGameplayStatics::SaveGameToSlot(leaderboard, leaderboard->GetSaveSlotName(), leaderboard->GetUserIndex()))
		{
			//Save succeeded.
			GEngine->AddOnScreenDebugMessage(50, 2, FColor::Orange, "Saved record");
		}else
		{
			GEngine->AddOnScreenDebugMessage(50, 2, FColor::Orange, "Save record failed");
		}
	}
}

void ATheBackroomsGameModeBase::PauseGame()
{
	const auto player{ GetWorld()->GetFirstPlayerController() };

	if(player)
	{
		if (player->IsPaused())
		{
			if(m_pPauseMenu)
			{
				m_pPauseMenu->RemoveFromParent();
			}
			const FInputModeGameOnly gameOnly{};
			player->SetInputMode(gameOnly);
			player->SetShowMouseCursor(false);
			ResumeGame();
			//GEngine->AddOnScreenDebugMessage(8, 1, FColor::Green, "Pause game toggled off", true);

		}else
		{
			player->SetPause(true);
			if (m_PauseClass) 
			{

				if (!m_pPauseMenu)
				{
					m_pPauseMenu = CreateWidget<UPauseMenu>(GetWorld(), m_PauseClass);
				}
				m_pPauseMenu->AddToViewport(2);
				//const FInputModeUIOnly uiOnly{};
				//player->SetInputMode(uiOnly);
				const FInputModeGameAndUI gameAndUI{};
				player->SetInputMode(gameAndUI);
				player->SetShowMouseCursor(true);
				//m_pPauseMenu->SetFocus();
				m_pPauseMenu->SetUserFocus(player);
				//GEngine->AddOnScreenDebugMessage(8, 1, FColor::Green, "Pause game toggled on", true);

			}
			//menu->AddToViewport();
		}
	}
}

void ATheBackroomsGameModeBase::ResumeGame() const
{
	const auto player{ GetWorld()->GetFirstPlayerController() };

	if (player)
	{
		/*if (player->IsPaused())
		{
			player->SetPause(false);
		}else
		{*/

		player->SetPause(false);
		
		//}
	}
}

void ATheBackroomsGameModeBase::OpenHighScoreAdder()
{
	const auto player{ GetWorld()->GetFirstPlayerController() };

	if (player)
	{
		if (m_NewScoreClass)
		{
			APlayerMonster* playerMonster{ Cast<APlayerMonster>(player->GetPawn()) };
			if(playerMonster)
			{
				USaveGame* saveGame{ UGameplayStatics::LoadGameFromSlot("Leaderboard", 0) };
				ULeaderBoard* leaderboard = Cast<ULeaderBoard>(saveGame);
				if (leaderboard)
				{
					//leaderboard.LoadRecords();
					if (leaderboard->IsNewLeaderboardScore(playerMonster->m_pScoreSystem->GetFinalScore()))
					{						
						if (!m_pNewScoreMenu)
						{
							m_pNewScoreMenu = CreateWidget<UNewRecordWidget>(GetWorld(), m_NewScoreClass);
						}
						auto score{ Cast<UNewRecordWidget>(m_pNewScoreMenu) };
						if(score)
						{
							score->SetNewRecordValues(leaderboard, playerMonster->m_pScoreSystem->GetFinalScore(), playerMonster->m_pScoreSystem->GetTotalTimeAlive());
						}

						player->SetPause(true);
						m_pNewScoreMenu->AddToViewport(3);
						//const FInputModeUIOnly uiOnly{};
						const FInputModeGameAndUI gameAndUI{};
						player->SetInputMode(gameAndUI);
						player->SetShowMouseCursor(true);
					}
					else 
					{
						UGameplayStatics::OpenLevel(GetWorld(), "LeaderboardLevel");
					}
				}
			}
		}
	}
}
