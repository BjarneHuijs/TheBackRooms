// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreditsMenu.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class THEBACKROOMS_API UCreditsMenu : public UUserWidget
{
	GENERATED_BODY()
		virtual void NativeConstruct() override;
public:
	UFUNCTION(BlueprintGetter)
		UUserWidget* GetInvoker() const;
	UFUNCTION(BlueprintSetter)
		void SetInvoker(UUserWidget* invoker);
	
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
		UButton* m_pBackButton;

	UPROPERTY(BlueprintGetter = GetInvoker, BlueprintSetter = SetInvoker)
		UUserWidget* m_pInvoker;
	
	UPROPERTY(BlueprintGetter = GetSelectedButton, BlueprintSetter = SetSelectedButton)
		int m_SelectedButton;
};
