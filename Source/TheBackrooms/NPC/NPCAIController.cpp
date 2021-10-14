// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCAIController.h"
#include "NPCBaseCharacter.h"
#include "MyNPCPriestCharacter.h"
#include "WayPoint.h"
#include "TheBackrooms/Interactables/LightGenerator.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"



ANPCAIController::ANPCAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perceprion Component")));

	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AISightAngle;
	SightConfig->SetMaxAge(AISightAge);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &ANPCAIController::OnPawnDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}



void ANPCAIController::BeginPlay()
{
	Super::BeginPlay();
	
	ANPCBaseCharacter* character = Cast<ANPCBaseCharacter>(GetPawn());
	if (character)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, "Test character cast ");
		if (character->NextWayPoint == nullptr)
		{
			character->NextWayPoint = FindNewWayPoint();
		}
		

	}
	if (GetPerceptionComponent() != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Set "));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Problem has occured "));
	}
	

}

void ANPCAIController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);
}

void ANPCAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	

	ANPCBaseCharacter* character = Cast<ANPCBaseCharacter>(GetPawn());
	UPawnMovementComponent* charMove = character->GetMovementComponent();
	
	if (IsPanicking())
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, "PANICKING");

		charMove->Deactivate();
	}
	else
	{
		charMove->Activate();
	}
	if (character)
	{
		if (character->NextWayPoint == nullptr)
		{
			character->NextWayPoint = FindNewWayPoint();
		}
		if (character->NextWayPoint != nullptr)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, "NPC Should move");
			MoveToActor(character->NextWayPoint);
			
		}
		
		
	}
	
}

FRotator ANPCAIController::GetControlRotation() const
{
	if (GetPawn() == nullptr)
	{
		return FRotator(0.0f,0.0f,0.0f);
	}
	return FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}

void ANPCAIController::OnPawnDetected(const TArray<AActor*>& DetectedPawns)
{
	
	for (AActor* actor : DetectedPawns)
	{
		if (actor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, "sees player");
			TSubclassOf<AWayPoint> classToFind;
			TArray<AActor*> FoundActors;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWayPoint::StaticClass(), FoundActors);

			for (AActor* WayPoint : FoundActors)
			{
				ANPCBaseCharacter* character = Cast<ANPCBaseCharacter>(GetPawn());

					if (character)
					{
						FVector distanceNPC;
						FVector distancePlayer;

						float distanceToNPC = distanceNPC.Distance(WayPoint->GetActorLocation(), character->GetActorLocation());
						float distanceToPlayer = distancePlayer.Distance(WayPoint->GetActorLocation(), actor->GetActorLocation());

						if (distanceToNPC < distanceToPlayer)
						{
							character->NextWayPoint = Cast<AWayPoint>(WayPoint);

							//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, "running " );
						}
					}
					

			}
		}

	}
}

AWayPoint* ANPCAIController::FindNewWayPoint()
{
	AWayPoint *nextWayPoint;
	TSubclassOf<AWayPoint> classToFind;
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWayPoint::StaticClass(), FoundActors);

	int AmountOfElements = FoundActors.Num();

	int arrayRandomIndex = rand() % AmountOfElements;
	if (previousArrayIndex != arrayRandomIndex)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, "FOUND OTHER POINT");
		nextWayPoint = Cast<AWayPoint>(FoundActors[arrayRandomIndex]);
		previousArrayIndex = arrayRandomIndex;
		return nextWayPoint;
	}


	return nullptr;
}

bool ANPCAIController::IsAfraid()
{
	return m_IsAfraid;
}

bool ANPCAIController::IsPanicking()
{
	for (TObjectIterator<ALightGenerator>generatorIterator; generatorIterator; ++generatorIterator)
	{
		if (generatorIterator->GetWorld())
		{
			FVector DistanceToGenerator;
			const float distance = DistanceToGenerator.Distance(GetCharacter()->GetActorLocation(), generatorIterator->GetActorLocation());
			if (distance <= 1500.f)
			{
				if (generatorIterator->IsBroken())
				{
					GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Purple, "NPC should feel scared");
					m_IsAfraid = true;
					return m_IsAfraid;

				}
				else
				{
					m_IsAfraid = false;
					return m_IsAfraid;
				}
				
			}
			else
			{
				
				return m_IsAfraid;
			}
			
		}
		else
		{
			return m_IsAfraid;
		}
	}
	return m_IsAfraid;
}


