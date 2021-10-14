// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UI/Menu/Widgets/PauseMenu/PauseMenu.h"
#include "TheBackroomsGameModeBase.generated.h"
/**
 * 
 */
UCLASS()
class THEBACKROOMS_API ATheBackroomsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATheBackroomsGameModeBase(const FObjectInitializer& ObjectIn);

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
		void PauseGame();
	UFUNCTION(BlueprintCallable)
		void ResumeGame() const;

	UFUNCTION(BlueprintCallable)
		void OpenHighScoreAdder();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<UUserWidget> m_PauseClass;

	UPROPERTY()
		UUserWidget* m_pPauseMenu;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<UUserWidget> m_NewScoreClass;

	UPROPERTY()
		UUserWidget* m_pNewScoreMenu;
};
