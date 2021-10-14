// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCBaseCharacter.h"
#include "NPCAIController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values
ANPCBaseCharacter::ANPCBaseCharacter():
	  m_bIsDead(false)
	, m_bIsDying(false)
	

	, m_DeathAnimationTime(4.583f)
	, m_DeathTimer(0.f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.0f, 0.0f);

}

// Called when the game starts or when spawned
void ANPCBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ANPCBaseCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

// Called every frame
void ANPCBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AController* controller{ GetController() };
	if(controller)
	{
		ANPCAIController* NPCController = Cast<ANPCAIController>(controller);
		if(NPCController)
		{
			m_bIsPanicking = NPCController->IsAfraid();
		}
	}
	
	if (m_bIsDying)
	{
		//GEngine->AddOnScreenDebugMessage(3, 1, FColor::Red, "NPC is dying", true);
		UCapsuleComponent *hitbox = GetCapsuleComponent();
		if (hitbox)
		{
			hitbox->SetGenerateOverlapEvents(false);
			hitbox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		
		UCharacterMovementComponent* movement{ GetCharacterMovement() };

		if (movement)
		{
			movement->DisableMovement();
		}
		m_DeathTimer += DeltaTime;
		if (m_DeathTimer >= m_DeathAnimationTime)
		{
			m_bIsDead = true;
			
			m_DeathTimer -= DeltaTime;
			Destroy();
		}
	}

}

// Called to bind functionality to input
void ANPCBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool ANPCBaseCharacter::IsDying() const
{
	return m_bIsDying;
}

bool ANPCBaseCharacter::IsDead() const
{
	return m_bIsDead;
}
bool ANPCBaseCharacter::IsPanicking() const
{
	return m_bIsPanicking;
}
void ANPCBaseCharacter::Die()
{
	
	m_bIsDying = true;
	
}

