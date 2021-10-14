// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilityWidget.generated.h"

class UProgressBar;
class APlayerMonster;
UCLASS()
class THEBACKROOMS_API UAbilityWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
public:

	UFUNCTION(BlueprintCallable)
		float GetDashCooldownPercentage() const;
	UFUNCTION(BlueprintCallable)
		float GetAttackCooldownPercentage() const;
	UFUNCTION(BlueprintCallable)
		bool GetCanPhaseThroughWalls() const;

	UFUNCTION(BlueprintGetter)
		bool WasLastInputController() const;

	UFUNCTION(BlueprintCallable)
		void CheckLastInputType();
private:
	UPROPERTY(meta = (BindWidget))
		UProgressBar* m_pDashCooldown;
	UPROPERTY(meta = (BindWidget))
		UProgressBar* m_pAttackCooldown;

	UPROPERTY()
		APlayerMonster* m_pPlayer;

	UPROPERTY(BlueprintGetter = WasLastInputController)
		bool m_bLastInputwasController;
};
