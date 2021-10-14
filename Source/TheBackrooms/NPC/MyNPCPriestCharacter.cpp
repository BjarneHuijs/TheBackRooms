// Fill out your copyright notice in the Description page of Project Settings.


#include "MyNPCPriestCharacter.h"
#include "PriestAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

AMyNPCPriestCharacter::AMyNPCPriestCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.0f, 0.0f);
}

void AMyNPCPriestCharacter::BeginPlay()
{
	ANPCBaseCharacter::BeginPlay();

	m_pPrayer = GetWorld()->SpawnActor<APrayerAttack>(RootComponent->GetRelativeLocation(), RootComponent->GetRelativeRotation());

	m_pPrayer->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	
}
void AMyNPCPriestCharacter::OnConstruction(const FTransform& Transform)
{
	ANPCBaseCharacter::OnConstruction(Transform);

}
void AMyNPCPriestCharacter::Tick(float DeltaTime)
{
	ANPCBaseCharacter::Tick(DeltaTime);
	
	AController* controller = GetController();
	if (!controller)
	{
		return;
	}
	APriestAIController* PriestController = Cast<APriestAIController>(controller);

		if (PriestController)
		{
			m_IsPanicking = PriestController->IsAfraid();

			m_bIsPraying = PriestController->m_IsPraying;
		}

	
	
}

bool AMyNPCPriestCharacter::IsPriestPanicking()
{
	
	return m_IsPanicking;
}

bool AMyNPCPriestCharacter::IsPraying()
{
	return m_bIsPraying;
}

