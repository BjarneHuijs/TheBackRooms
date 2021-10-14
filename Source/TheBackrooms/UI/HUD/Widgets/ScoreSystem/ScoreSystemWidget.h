#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreSystemWidget.generated.h"

/**
 * 
 */
class APlayerMonster;
class UTextBlock;
UCLASS()
class THEBACKROOMS_API UScoreSystemWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
public:

	UFUNCTION(BlueprintCallable)
		int GetPlayerTimeAlive() const;
	UFUNCTION(BlueprintCallable)
		int GetTotalNrOfKills() const;
	UFUNCTION(BlueprintCallable)
		int GetCurrentScore() const;

private:
	UPROPERTY(meta = (BindWidget))
		UTextBlock* m_pTimeAlive;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* m_pNrOfKills;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* m_pCurrentScore;

	UPROPERTY()
		APlayerMonster* m_pPlayer;
	
};
