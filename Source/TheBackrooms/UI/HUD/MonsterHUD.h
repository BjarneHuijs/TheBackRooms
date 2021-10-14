// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MonsterHUD.generated.h"


class UScoreSystemWidget;
class UAbilityWidget;
class UBloodMeterWidget;
UCLASS()
class THEBACKROOMS_API AMonsterHUD : public AHUD
{
	GENERATED_BODY()

	AMonsterHUD(const FObjectInitializer& ObjectIn);

	virtual void OnConstruction(const FTransform& Transform) override;
	//virtual void BeginPlay() override;
public:
	UPROPERTY(BlueprintReadWrite)
		UBloodMeterWidget* m_pBloodMeterWidget;
	
	UPROPERTY(BlueprintReadWrite)
		UAbilityWidget* m_pAbilityWidget;
	
	UPROPERTY(BlueprintReadWrite)
		UScoreSystemWidget* m_pScoreSystemWidget;
};
