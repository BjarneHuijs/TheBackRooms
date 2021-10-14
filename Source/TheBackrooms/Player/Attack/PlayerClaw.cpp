// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerClaw.h"

#include "Components/BoxComponent.h"
#include "TheBackrooms/NPC/NPCBaseCharacter.h"
#include "TheBackrooms/NPC/MyNPCPriestCharacter.h"
#include "TheBackrooms/Player/PlayerMonster.h"
#include "TheBackrooms/Interactables/LightGenerator.h"

// Sets default values
APlayerClaw::APlayerClaw()
	: m_TimeAlive(5.f)
	, m_TimeToLive(5.f)
	, m_bCanAttack(true)

	, m_pColliderBox(nullptr)
	, m_bDebugMode(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	auto box = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider box"));
	box->SetBoxExtent({ 90.f, 10.f, 32.f });
	box->SetGenerateOverlapEvents(true);

	m_pColliderBox = box;
	RootComponent = m_pColliderBox;

	m_pVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_VisibleComponent"));
	UStaticMesh* cubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object;

	if (cubeMesh)
	{
		m_pVisibleComponent->SetStaticMesh(cubeMesh);
		m_pVisibleComponent->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		m_pVisibleComponent->SetWorldScale3D(FVector{ 1.f, 1.f, 0.2f });
		m_pVisibleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		m_pVisibleComponent->SetGenerateOverlapEvents(false);
		m_pVisibleComponent->SetupAttachment(RootComponent);
	}
	m_pColliderBox->OnComponentBeginOverlap.AddDynamic(this, &APlayerClaw::OnBeginOverlap);
}

// Called when the game starts or when spawned
void APlayerClaw::BeginPlay()
{
	Super::BeginPlay();
	//m_pColliderBox->SetGenerateOverlapEvents(false);
}

// Called every frame
void APlayerClaw::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// seperate scope for debug mode, will toggle attack visuals on/off
	{
		m_pColliderBox->SetHiddenInGame(!m_bDebugMode);
		m_pColliderBox->SetVisibility(m_bDebugMode);
		m_pVisibleComponent->SetVisibility(m_bDebugMode, true);
	}

	if (!m_bCanAttack)
	{
		m_TimeAlive += DeltaTime;
		//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Orange, L"Time: " + FString::SanitizeFloat(m_TimeAlive));

		if (m_TimeAlive >= m_TimeToLive)
		{
			EndAttack();
		}
	}
}

void APlayerClaw::OnBeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp,
	int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	ANPCBaseCharacter* pBaseNPC = Cast<ANPCBaseCharacter>(otherActor);
	const auto player = Cast<APlayerMonster>(GetOwner());
	if (player && player->IsAttacking()) 
	{
		if (pBaseNPC)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, L"Hit enemy Base NPC");

			pBaseNPC->Die();

			player->AddBlood(10.f);

		}

		AMyNPCPriestCharacter* pPriestNPC = Cast<AMyNPCPriestCharacter>(otherActor);
		if (pPriestNPC)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, L"Hit enemy Priest NPC");
			pPriestNPC->Die();

			//const auto player = Cast<APlayerMonster>(GetOwner());
			player->AddBlood(15.f);
		}

		ALightGenerator* GeneratorActor = Cast<ALightGenerator>(otherActor);
		if (GeneratorActor)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, L"Hit Generator");
			GeneratorActor->SetGeneratorState();
		}
	}
}

void APlayerClaw::SetTimeToLive(float ttl)
{
	if (ttl > 0.f && ttl <= 10.f)
	{
		m_TimeToLive = ttl;
	}
}

float APlayerClaw::GetTimeAlive() const
{
	return m_TimeAlive;
}

bool APlayerClaw::CanAttack() const
{
	return m_bCanAttack;
}

void APlayerClaw::StartAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "Attack started");
	m_bCanAttack = false;
	m_TimeAlive = 0.f;

	m_pColliderBox->SetGenerateOverlapEvents(true);
}

void APlayerClaw::EndAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "Attack ended");
	m_bCanAttack = true;

	m_pColliderBox->SetGenerateOverlapEvents(false);

	const auto player = Cast<APlayerMonster>(GetOwner());
	player->SetIsAttacking(false);
}

void APlayerClaw::SetDebugMode(bool mode)
{
	m_bDebugMode = mode;
}

float APlayerClaw::GetTimeToLive() const 
{
	return m_TimeToLive;
}