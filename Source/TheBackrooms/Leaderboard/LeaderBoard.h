// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LeaderBoard.generated.h"

/**
 * 
 */

USTRUCT()
struct FPlayerRecord
{
	GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, Category = Basic)
        FString PlayerName;

    UPROPERTY(VisibleAnywhere, Category = Basic)
        int PlayerTime;

    UPROPERTY(VisibleAnywhere, Category = Basic)
        int PlayerScore;
};

UCLASS()
class THEBACKROOMS_API ULeaderBoard : public USaveGame
{
	GENERATED_BODY()
public:
    ULeaderBoard();


 //   UFUNCTION()
 //       void SetPlayerName(const FString& name);
 //   UFUNCTION()
 //       FString GetPlayerName();
	//
	//UFUNCTION()
 //       void SetPlayerScore(int score);
	//UFUNCTION()
 //       int GetPlayerScore();
	//
	//UFUNCTION()
 //       void SetPlayerTime(int time);
	//UFUNCTION()
 //       int GetPlayerTime();

    UFUNCTION()
        FString GetSaveSlotName() const;

	UFUNCTION()
        uint32 GetUserIndex() const;
	
    UFUNCTION()
        void SaveNewScore(const FPlayerRecord& player);

    UFUNCTION()
        bool IsNewLeaderboardScore(int score);

	UFUNCTION()
        const FPlayerRecord& GetHighestRecord() const;

    UFUNCTION()
        TArray<FPlayerRecord> GetRecords() const;

 //   UFUNCTION()
 //       void LoadRecords();

	//UFUNCTION()
 //       void Save() const;
	
private:
    UPROPERTY(VisibleAnywhere, Category = Basic)
        TArray<FPlayerRecord> m_Records;

    UPROPERTY(VisibleAnywhere, Category = Basic)
        FString m_SaveSlotName;

    UPROPERTY(VisibleAnywhere, Category = Basic)
        uint32 m_UserIndex;

};
