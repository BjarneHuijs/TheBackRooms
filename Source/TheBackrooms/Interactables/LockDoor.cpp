// Fill out your copyright notice in the Description page of Project Settings.


#include "LockDoor.h"

// Sets default values
ALockDoor::ALockDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALockDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALockDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_IsClosed)
	{
		m_CurrentTimeClosed += DeltaTime;
	}
	if (m_CurrentTimeClosed >= m_TimeClosed)
	{
		OpenDoor();
	}
}

void ALockDoor::CloseDoor()
{
	
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, "Closing Door");
	m_IsClosed = true;
}

void ALockDoor::OpenDoor()
{
	
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, "Opening Door");
	m_IsClosed = false;
	m_CurrentTimeClosed = 0.f;
}

bool ALockDoor::IsClosed()
{
	return m_IsClosed;
}

float ALockDoor::GetTimeClosed() const
{
	return m_TimeClosed;
}

void ALockDoor::SetTimeClosed(float closeTime)
{
	if(closeTime > 0.f)
	{
		m_TimeClosed = closeTime;
	}
}

float ALockDoor::GetLockRadius() const
{
	return m_RadiusToLock;
}

void ALockDoor::SetLockRadius(float radius)
{
	if(radius > 0.f)
	{
		m_RadiusToLock = radius;
	}
}

