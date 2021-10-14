// Fill out your copyright notice in the Description page of Project Settings.


#include "PhaseableWall.h"


#include "Components/BoxComponent.h"
#include "TheBackrooms/Player/PlayerMonster.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
APhaseableWall::APhaseableWall()
	: m_bActive(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto box = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider box"));
	box->SetBoxExtent({ 150.f, 50.f, 150.f });
	box->SetGenerateOverlapEvents(true);
	box->SetHiddenInGame(false);

	m_pColliderBox = box;
	SetRootComponent(m_pColliderBox);

	
	m_pWallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_pWallMesh"));
	m_pWallMesh->SetupAttachment(m_pColliderBox);
	
	static UStaticMesh* CubeVisualAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object;

	if (CubeVisualAsset)
	{
		m_pWallMesh->SetStaticMesh(CubeVisualAsset);
		m_pWallMesh->SetRelativeLocation(FVector{ 0.f, 0.f, 0.f });
		m_pWallMesh->SetWorldScale3D(FVector{ 3.f, .5f, 3.f });
		m_pWallMesh->SetMaterial(0, m_pInActiveMaterial);
	}

	m_pExit_1 = CreateDefaultSubobject<USceneComponent>(TEXT("m_pExit_1"));
	m_ExitPos_1 = FVector(0.f, 150.f, -52.f);
	m_pExit_1->SetRelativeLocation(m_ExitPos_1);
	m_pExit_1->SetupAttachment(m_pWallMesh);
	
	m_pExit_2 = CreateDefaultSubobject<USceneComponent>(TEXT("m_pExit_2"));
	m_ExitPos_2 = FVector(0.f, -150.f, -52.f);
	m_pExit_2->SetRelativeLocation(m_ExitPos_2);
	m_pExit_2->SetupAttachment(m_pWallMesh);

	//m_pWallMesh->OnComponentBeginOverlap.AddDynamic(this, &APhaseableWall::OnBeginOverlap);
	OnActorBeginOverlap.AddDynamic(this, &APhaseableWall::OnBeginOverlap);
}

//void APhaseableWall::OnBeginOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor,
	//UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
void APhaseableWall::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const APlayerMonster* player{ Cast<APlayerMonster>(OtherActor) };
	if (player)
	{
		//if(!m_bActive && player->GetBloodMeterCurrentTier() >= BloodTiers::Tier_1)
		if (player->GetCanPhaseThroughWall())
		{
			const float distanceToExit_1{ (m_pExit_1->GetComponentLocation() - OtherActor->GetActorLocation()).Size() };
			const float distanceToExit_2{ (m_pExit_2->GetComponentLocation() - OtherActor->GetActorLocation()).Size() };
			FVector newPos{};
			if (distanceToExit_1 > distanceToExit_2)
			{
				//GEngine->AddOnScreenDebugMessage(33, 1.f, FColor::Green, TEXT("closest to exit 2"), true);
				newPos = m_pExit_1->GetComponentLocation();
				newPos.Z = OtherActor->GetActorLocation().Z;
				OtherActor->SetActorLocation(newPos, false, nullptr, ETeleportType::ResetPhysics);
			}
			else if (distanceToExit_2 > distanceToExit_1)
			{
				//GEngine->AddOnScreenDebugMessage(34, 1.f, FColor::Green, TEXT("closest to exit 1"), true);
				newPos = m_pExit_2->GetComponentLocation();
				newPos.Z = OtherActor->GetActorLocation().Z;
				OtherActor->SetActorLocation(newPos, false, nullptr, ETeleportType::ResetPhysics);
			}
		}
	}
}

// Called when the game starts or when spawned
void APhaseableWall::BeginPlay()
{
	Super::BeginPlay();

	m_pExit_1->SetRelativeLocation(m_ExitPos_1);
	m_pExit_2->SetRelativeLocation(m_ExitPos_2);
}

// Called every frame
void APhaseableWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const bool oldActiveValue{ m_bActive };
	
	const UWorld* world{ GetWorld() };
	if(world)
	{
		const APlayerController* controller{ world->GetFirstPlayerController() };
		if(controller)
		{
			const APlayerMonster* player{ Cast<APlayerMonster>(controller->GetPawn()) };
			if(player)
			{
				//if(!m_bActive && player->GetBloodMeterCurrentTier() >= BloodTiers::Tier_1)
				if(!player->GetCanPhaseThroughWall() && !m_bActive)
				{
					Toggle(true);
				}else if(player->GetCanPhaseThroughWall() && m_bActive)
				{
					Toggle(false);
				}
			}
		}
	}

	if (oldActiveValue != m_bActive)
	{
		SwapMaterial(m_bActive);
	}
}

bool APhaseableWall::GetActive() const
{
	return m_bActive;
}

void APhaseableWall::Toggle(bool state)
{
	m_bActive = state;
}

void APhaseableWall::SwapMaterial_Implementation(bool active)
{
	if (m_bActive)
	{
		m_pWallMesh->SetMaterial(0, m_pActiveMaterial);
		//m_pWallMesh->GetStaticMesh()->SetMaterial(0, m_pActiveMaterial);
	}
	else
	{
		m_pWallMesh->SetMaterial(0, m_pInActiveMaterial);
		//m_pWallMesh->GetStaticMesh()->SetMaterial(0, m_pInActiveMaterial);
	}
}

