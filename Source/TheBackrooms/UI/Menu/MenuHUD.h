// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MenuHUD.generated.h"

class UMainMenu;
UCLASS()
class THEBACKROOMS_API AMenuHUD : public AHUD
{
	GENERATED_BODY()
	AMenuHUD(const FObjectInitializer& ObjectIn);

	virtual void OnConstruction(const FTransform& Transform) override;
	
public:
	UPROPERTY(BlueprintReadWrite)
		UMainMenu* M_PMainMenu;
};
