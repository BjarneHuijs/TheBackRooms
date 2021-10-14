// Fill out your copyright notice in the Description page of Project Settings.


#include "WayPoint.h"
#include "NPCBaseCharacter.h"
#include "MyNPCPriestCharacter.h"
#include "NPCAIController.h"
#include "PriestAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values
AWayPoint::AWayPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	SetRootComponent(Root);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	BoxComponent->SetupAttachment(GetRootComponent());

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AWayPoint::OnPlayerEnter);
}

// Called when the game starts or when spawned
void AWayPoint::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void AWayPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, NextWayPoint->GetName());
}



void AWayPoint::OnPlayerEnter(UPrimitiveComponent* OverlapComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ANPCBaseCharacter* Character = nullptr;
	AMyNPCPriestCharacter* Priest = nullptr;
	if (otherActor != nullptr)
	{
		Priest = Cast<AMyNPCPriestCharacter>(otherActor);
		if (Priest)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, "Priest entered waypoint");

			APriestAIController* controller = Cast<APriestAIController>(Priest->GetController());

			if (controller)
			{
				Priest->NextWayPoint = controller->FindNewWayPoint();
			}
		}

		Character = Cast<ANPCBaseCharacter>(otherActor);
		if (Character )
		{
			//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, "NPC entered waypoint");
			
			ANPCAIController *controller = Cast<ANPCAIController>(Character->GetController());
			
			if (controller)
			{ 
				Character->NextWayPoint = controller->FindNewWayPoint();
			}
			
			//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, NextWayPoint->GetName());
		}
	}
}



