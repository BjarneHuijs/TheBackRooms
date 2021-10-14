// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LeaderboardMenu.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FDisplayRecord
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = Basic, BlueprintReadOnly)
		FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = Basic, BlueprintReadOnly)
		int PlayerScore;

	UPROPERTY(VisibleAnywhere, Category = Basic, BlueprintReadOnly)
		int PlayerTime;
};

class UButton;
UCLASS()
class THEBACKROOMS_API ULeaderboardMenu : public UUserWidget
{
	GENERATED_BODY()
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
		void CloseLeaderBoard();

	UFUNCTION(BlueprintGetter)
		UUserWidget* GetInvoker() const;
	
	UFUNCTION(BlueprintCallable)
		void SetInvoker(UUserWidget* invoker, bool paused = false);

	UFUNCTION(BlueprintCallable)
		void LoadLeaderboard();


	UFUNCTION(BlueprintGetter)
		int GetSelectedButton() const;
	UFUNCTION(BlueprintSetter)
		void SetSelectedButton(int button);

	UFUNCTION(BlueprintCallable)
		void MoveSelectionUp();
	UFUNCTION(BlueprintCallable)
		void MoveSelectionDown();

	UFUNCTION(BlueprintCallable)
		void HandleFocusChange();

	//UFUNCTION(BlueprintNativeEvent)
	UFUNCTION(BlueprintCallable)
		void SetWidgetFocus(UButton* pButton);

	UFUNCTION(BlueprintCallable)
		void ResetButtonStyles();
	UFUNCTION(BlueprintNativeEvent)
		void ResetButtonStyle(UButton* pButton);
	UFUNCTION(BlueprintNativeEvent)
		void SetFocusedButton(UButton* pButton);
	
	UFUNCTION(BlueprintGetter)
		TArray<FDisplayRecord> GetRecords() const;

	//Returns -1 if no input, 0 if input is up direction, down direction returns 1
	UFUNCTION(BlueprintCallable)
		int GetGamepadMenuInput();

	UFUNCTION(BlueprintCallable)
		void CheckGameState();
	
	UFUNCTION(BlueprintGetter)
		bool GetPaused() const;
private:
	UPROPERTY(meta = (BindWidget))
		UButton* m_pBackButton;

	UPROPERTY(meta = (BindWidget))
		UButton* m_pStartGameButton;

	UPROPERTY(VisibleAnywhere, Category = Basic, BlueprintGetter = GetRecords)
		TArray<FDisplayRecord> m_records;

	UPROPERTY(BlueprintGetter = GetSelectedButton, BlueprintSetter = SetSelectedButton)
		int m_SelectedButton;

	UPROPERTY(BlueprintGetter = GetPaused)
		bool m_bPaused;

	UPROPERTY(BlueprintGetter = GetInvoker)
		UUserWidget* m_pInvoker;
};
