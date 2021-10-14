// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NewRecordWidget.generated.h"

class ULeaderBoard;
/**
 * 
 */
class UButton;
class UTextBlock;
class UEditableTextBox;
UCLASS()
class THEBACKROOMS_API UNewRecordWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
		void SaveScore();

	UFUNCTION(BlueprintCallable)
		void DontSaveScore();

	UFUNCTION()
		void SetNewRecordValues(ULeaderBoard* board, int score, int time);

	UFUNCTION(BlueprintGetter)
		int GetTimeAlive() const;
	UFUNCTION(BlueprintGetter)
		int GetCurrentScore() const;

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
		void SetInputFocus(UEditableTextBox* pTextBox);
	UFUNCTION(BlueprintNativeEvent)
		void SetFocusedInputBox(UEditableTextBox* pTextBox);
	UFUNCTION(BlueprintNativeEvent)
		void ResetInputStyle(UEditableTextBox* pTextBox);
	
	UFUNCTION(BlueprintCallable)
		void ResetButtonStyles();
	UFUNCTION(BlueprintNativeEvent)
		void ResetButtonStyle(UButton* pButton);
	UFUNCTION(BlueprintNativeEvent)
		void SetFocusedButton(UButton* pButton);

	UFUNCTION(BlueprintCallable)
		void ResetWidgetStyles();
	
	//Returns -1 if no input, 0 if input is up direction, down direction returns 1
	UFUNCTION(BlueprintCallable)
		int GetGamepadMenuInput();
private:
	UPROPERTY(meta = (BindWidget))
		UEditableTextBox* m_pNameInputField;

	UPROPERTY(meta = (BindWidget))
		UButton* m_pSaveScoreButton;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* m_pTimeAlive;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* m_pScore;

	UPROPERTY(meta = (BindWidget))
		UButton* m_pDontSaveScoreButton;

	UPROPERTY(meta = (BindWidget))
		UButton* m_pRestartButton;


	UPROPERTY(BlueprintGetter = GetSelectedButton, BlueprintSetter = SetSelectedButton)
		int m_SelectedButton;

	UPROPERTY(BlueprintGetter = GetCurrentScore)
		int m_AttainedScore;
	UPROPERTY(BlueprintGetter = GetTimeAlive)
		int m_TimeSurvived;

	UPROPERTY()
		ULeaderBoard* m_pLeaderBoard;
};
