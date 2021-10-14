// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionsMenu.generated.h"

class USlider;
class UButton;
class USoundClass;
/**
 * 
 */
UCLASS()
class THEBACKROOMS_API UOptionsMenu : public UUserWidget
{
	GENERATED_BODY()
	virtual void NativeConstruct() override;
	
public:
	UFUNCTION(BlueprintCallable)
		void CloseOptions();

	UFUNCTION(BlueprintGetter)
		UUserWidget* GetInvoker() const;
	UFUNCTION(BlueprintSetter)
		void SetInvoker(UUserWidget* invoker);

	// Sets the volume of a sound class Asset
	UFUNCTION(BlueprintCallable, Category = "Settings|Sound")
		static void SetSoundClassVolume(USoundClass* SoundClass, float Volume);

	// Gets volume of a sound class Asset
	UFUNCTION(BlueprintPure, Category = "Settings|Sound")
		static float GetSoundClassVolume(const USoundClass* SoundClass);

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
		void SetSliderFocus(USlider* pSlider);

	UFUNCTION(BlueprintCallable)
		void ResetWidgetStyles();
	UFUNCTION(BlueprintNativeEvent)
		void ResetButtonStyle(UButton* pButton);
	UFUNCTION(BlueprintNativeEvent)
		void SetFocusedButton(UButton* pButton);


	UFUNCTION(BlueprintNativeEvent)
		void SetFocusedSlider(USlider* pSlider);
	UFUNCTION(BlueprintNativeEvent)
		void ResetSlider(USlider* pSlider);

	//Returns -1 if no input, 0 if input is up direction, down direction returns 1
	UFUNCTION(BlueprintCallable)
		int GetGamepadMenuInput();
private:
	UPROPERTY(BlueprintGetter = GetInvoker, BlueprintSetter = SetInvoker)
		UUserWidget* m_pInvoker;

	UPROPERTY(meta = (BindWidget))
		UButton* m_pBackButton;

	UPROPERTY(meta = (BindWidget))
		USlider* m_pMasterVolumeSlider;

	UPROPERTY(meta = (BindWidget))
		USlider* m_pPlayerVolumeSlider;

	UPROPERTY(meta = (BindWidget))
		USlider* m_pNPCVolumeSlider;

	UPROPERTY(meta = (BindWidget))
		USlider* m_pAmbientVolumeSlider;

	UPROPERTY(BlueprintGetter = GetSelectedButton, BlueprintSetter = SetSelectedButton)
		int m_SelectedButton;
};
