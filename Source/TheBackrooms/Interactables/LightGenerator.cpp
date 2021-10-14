// Fill out your copyright notice in the Description page of Project Settings.


#include "LightGenerator.h"
#include "Components/RectLightComponent.h"
#include "Components/LightComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
// Sets default values
ALightGenerator::ALightGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_HitDetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Hit detection sphere"));
	m_HitDetectionSphere->InitSphereRadius(200.f);
	m_HitDetectionSphere->SetupAttachment(RootComponent);
}

ALightGenerator::~ALightGenerator()
{
	ResetLightsEnd();
}

// Called when the game starts or when spawned
void ALightGenerator::BeginPlay()
{
	Super::BeginPlay();

	
	for (TObjectIterator<ULightComponent>ActorItr; ActorItr; ++ActorItr)
	{
		if (ActorItr->GetWorld())
		{
			//m_LightIntensity = ActorItr->Intensity;
		}

	}
}



// Called every frame
void ALightGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (m_IsBroken)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, L"Is BROKEN");
		m_TimeSinceBroken += DeltaTime;
		//FString TheFloatStr = FString::SanitizeFloat(m_TimeSinceBroken);
		//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, *TheFloatStr);
		if (m_TimeSinceBroken >= m_TimeToRepair)
		{
			m_IsBroken = false;
			m_TimeSinceBroken = 0.f;
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, L" Generator is Repaired");
			ResetLightsInScene();
		}
	}

}

void ALightGenerator::SetGeneratorState()
{
	if (!m_IsBroken)
	{
		m_IsBroken = true;
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, L" Generator is broken");
		FindLightsInScene();

	}
	
}

void ALightGenerator::FindLightsInScene() const
{
	
	for (TObjectIterator<ULightComponent>ActorItr; ActorItr ; ++ActorItr)
	{
		if (ActorItr->GetWorld())
		{
			FVector DistanceToGenerator;
			float distance = DistanceToGenerator.Distance(ActorItr->GetLightPosition(), this->GetActorLocation());
			if (distance <= 1500.f)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, L" Light found");
				ActorItr->SetIntensity(10.f);
			}
			
			
		}
		
	}
}

void ALightGenerator::ResetLightsInScene() const
{
	for (TObjectIterator<ULightComponent>ActorItr; ActorItr; ++ActorItr)
	{
		if (ActorItr->GetWorld())
		{
			FVector DistanceToGenerator;
			float distance = DistanceToGenerator.Distance(ActorItr->GetLightPosition(), this->GetActorLocation());
			if (distance <= 1500.f)
			{
				ActorItr->SetIntensity(m_LightIntensity);
			}
		}

	}
}

void ALightGenerator::ResetLightsEnd() const
{
	for (TObjectIterator<ULightComponent>ActorItr; ActorItr; ++ActorItr)
	{
		if (ActorItr->GetWorld())
		{
			ActorItr->SetIntensity(m_LightIntensity);
		}

	}
}

float ALightGenerator::GetRepairTime() const
{
	return m_TimeToRepair;
}

void ALightGenerator::SetRepairTime(float repairTime)
{
	if(repairTime > 0.f)
	{
		m_TimeToRepair = repairTime;
	}
}

bool ALightGenerator::IsBroken() const
{
	return m_IsBroken;
}

bool ALightGenerator::IsGeneratorBroken()
{
	return m_IsBroken;
}