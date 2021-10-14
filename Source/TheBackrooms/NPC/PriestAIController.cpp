// Fill out your copyright notice in the Description page of Project Settings.


#include "PriestAIController.h"
#include "NPCBaseCharacter.h"
#include "MyNPCPriestCharacter.h"
#include "WayPoint.h"
#include "TheBackrooms/Interactables/LightGenerator.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


APriestAIController::APriestAIController()
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

	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &APriestAIController::OnPawnDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);

}

void APriestAIController::BeginPlay()
{
	Super::BeginPlay();
	AMyNPCPriestCharacter* PriestCharacter = Cast<AMyNPCPriestCharacter>(GetPawn());
	if (PriestCharacter)
	{
		if (PriestCharacter->NextWayPoint == nullptr)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, "Priest new waypoint begin ");
			PriestCharacter->NextWayPoint = FindNewWayPoint();
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

void APriestAIController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);
}

void APriestAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (m_IsPraying)
	{
		m_PrayerAttackTime += DeltaSeconds;
	}
	

	
	AMyNPCPriestCharacter* PriestCharacter = Cast<AMyNPCPriestCharacter>(GetPawn());
	// get priest movement component
	UPawnMovementComponent* charMove = PriestCharacter->GetMovementComponent();
	if (IsPanicking())
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, "PANICKING");
		charMove->Deactivate();
		
	}
	else
	{
		charMove->Activate();
	}
	if (PriestCharacter)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, "Priest cast succesfull tick ");
		if (PriestCharacter->NextWayPoint == nullptr)
		{
			PriestCharacter->NextWayPoint = FindNewWayPoint();
		}
		else if (PriestCharacter->NextWayPoint != nullptr)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, "Priest movetoactor ");
			MoveToActor(PriestCharacter->NextWayPoint);
		}
		
		if (IsPlayerInSight())
		{
			AActor* actor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
			
			if (!m_IsPraying)
			{
				if (IsPlayerInRange() && IsPlayerInSight())
				{
					charMove->Deactivate();
					m_IsPraying = true;
					PriestCharacter->m_pPrayer->StartAttack();
				}
				else
				{
					if (m_PrayerAttackTime >= 1.f)
					{
						MoveToActor(actor);
						m_PrayerAttackTime = 0.f;
						PriestCharacter->m_pPrayer->Reset();
					}
					
				}
			}
			
			/*if (!m_IsPraying)
			{
				if (IsPlayerInRange())
				{
					charMove->Deactivate();
					m_IsPraying = true;
					PriestCharacter->m_pPrayer->StartAttack();
				}
				else
				{
					if (IsPlayerInSight())
					{
						charMove->Activate();
						MoveToActor(actor);
						m_IsPraying = false;

						if (m_PrayerAttackTime <= 1.f)
						{
							GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, "test");
							m_IsPraying = false;
							
							PriestCharacter->m_pPrayer->Reset();
							
						}
						

					}
					else if (!IsPlayerInSight())
					{
						m_IsPraying = false;
						
						PriestCharacter->NextWayPoint = FindNewWayPoint();
						
					}
				}

			}*/
			if (PriestCharacter->m_pPrayer->HasAttacked())
			{
					
				charMove->Activate();
				m_IsPraying = false;
				PriestCharacter->NextWayPoint = FindNewWayPoint();
				m_PrayerAttackTime = 0.f;
				PriestCharacter->m_pPrayer->Reset();
			}

		}
			
		
		
	}
	
	if (m_PrayerAttackTime >= m_AttackTime)
	{
		m_PrayerAttackTime = 0.f;
	}

	
}

FRotator APriestAIController::GetControlRotation() const
{
	if (GetPawn() == nullptr)
	{
		return FRotator(0.0f, 0.0f, 0.0f);
	}
	return FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}

void APriestAIController::OnPawnDetected(const TArray<AActor*>& DetectedPawns)
{

	for (AActor* actor : DetectedPawns)
	{
		if (actor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
		{
			
			
			HasSeenPlayer = true;
				
			
			
		}
	}
}

AWayPoint* APriestAIController::FindNewWayPoint()
{
	AWayPoint* nextWayPoint;
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
bool APriestAIController::IsPlayerInRange()
{
	AMyNPCPriestCharacter* PriestCharacter = Cast<AMyNPCPriestCharacter>(GetPawn());
	if (PriestCharacter)
	{
		// get player character 
		AActor* actor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		// get priest movement component
		UPawnMovementComponent* charMove = PriestCharacter->GetMovementComponent();


		if (PriestCharacter->GetDistanceTo(actor) >= 200.f)
		{

			return false;
			
			

		}
		if (PriestCharacter->GetDistanceTo(actor) <= 200.f)
		{
			return true;
			

		}

		
	}

	return false;
}
bool APriestAIController::IsPlayerInSight()
{
	FActorPerceptionBlueprintInfo Info;
	AActor* actor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	GetAIPerceptionComponent()->GetActorsPerception(actor, Info);
	AMyNPCPriestCharacter* PriestCharacter = Cast<AMyNPCPriestCharacter>(GetPawn());
	if (PriestCharacter)
	{
		if (Info.LastSensedStimuli.Num() > 0)
		{
			const FAIStimulus Stimulus = Info.LastSensedStimuli[0];

			if (Stimulus.WasSuccessfullySensed())
			{
				//Player in sight
			
				//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, "sees player");
				return true;
			}
			else
			{
				
				//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, " player out of sight");
				HasSeenPlayer = false;
				
				return false;
			}
		}
	}

	return false;
}
bool APriestAIController::IsPraying()
{
	return m_IsPraying;
}
bool APriestAIController::IsPanicking()
{
	for (TObjectIterator<ALightGenerator>ActorItr; ActorItr; ++ActorItr)
	{
		if (ActorItr->GetWorld())
		{

			FVector DistanceToGenerator;
			float distance = DistanceToGenerator.Distance(GetCharacter()->GetActorLocation(), ActorItr->GetActorLocation());
			if (distance <= 1500.f)
			{
				if (ActorItr->IsBroken())
				{
					GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Purple, "Priest should feel scared");
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
bool APriestAIController::IsAfraid()
{
	
	return m_IsAfraid;
}