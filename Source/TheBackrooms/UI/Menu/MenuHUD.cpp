// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuHUD.h"

AMenuHUD::AMenuHUD(const FObjectInitializer& ObjectIn)
	: Super(ObjectIn)
{
}

void AMenuHUD::OnConstruction(const FTransform& Transform)
{
	const auto owner = GetWorld()->GetFirstPlayerController();
	SetOwner(owner);
}
