// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class THEBACKROOMS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
public:
	UFUNCTION(BlueprintCallable)
		void StartGame();

	UFUNCTION(BlueprintCallable)
		void OpenOptions();

	UFUNCTION(BlueprintCallable)
		void OpenLeaderBoard();

	UFUNCTION(BlueprintCallable)
		void ExitGame();

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

	//Returns -1 if no input, 0 if input is up direction, down direction returns 1
	UFUNCTION(BlueprintCallable)
		int GetGamepadMenuInput();
private:
	UPROPERTY(meta = (BindWidget))
		UButton* m_pStartButton;

	UPROPERTY(meta = (BindWidget))
		UButton* m_pOptionsButton;

	UPROPERTY(meta = (BindWidget))
		UButton* m_pLeaderboardButton;
	
	UPROPERTY(meta = (BindWidget))
		UButton* m_pCreditsButton;

	UPROPERTY(meta = (BindWidget))
		UButton* m_pExitButton;

	UPROPERTY(BlueprintGetter = GetSelectedButton, BlueprintSetter = SetSelectedButton)
		int m_SelectedButton;

};
