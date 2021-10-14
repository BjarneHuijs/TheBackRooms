// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BloodMeterWidget.generated.h"


class APlayerMonster;
class UProgressBar;
class UBorder;
UCLASS()
class THEBACKROOMS_API UBloodMeterWidget : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
		float GetBloodBarFillPercentage() const;

	UFUNCTION(BlueprintCallable)
		FLinearColor GetCurrentBloodTier1() const;
	UFUNCTION(BlueprintCallable)
		FLinearColor GetCurrentBloodTier2() const;
	UFUNCTION(BlueprintCallable)
		FLinearColor GetCurrentBloodTier3() const;
	UFUNCTION(BlueprintCallable)
		FLinearColor GetCurrentBloodTier4() const;
	UFUNCTION(BlueprintCallable)
		FLinearColor GetCurrentBloodTier5() const;

private:
	UPROPERTY(meta = (BindWidget))
		UProgressBar* m_pBloodMeter;

	UPROPERTY(meta = (BindWidget))
		UBorder* m_pTier1;
	UPROPERTY(meta = (BindWidget))
		UBorder* m_pTier2;
	UPROPERTY(meta = (BindWidget))
		UBorder* m_pTier3;
	UPROPERTY(meta = (BindWidget))
		UBorder* m_pTier4;
	UPROPERTY(meta = (BindWidget))
		UBorder* m_pTier5;

	UPROPERTY()
		APlayerMonster* m_pPlayer;
};
