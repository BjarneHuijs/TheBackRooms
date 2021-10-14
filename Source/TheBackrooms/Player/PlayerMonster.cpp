// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMonster.h"



#include "ScoreSystem.h"
#include "TheBackrooms/Interactables/LockDoor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "../TheBackroomsGameModeBase.h"
#include "Attack/PlayerClaw.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APlayerMonster::APlayerMonster()
	: m_MeshScale(1.f, 1.f, 1.f)
	, m_DashCooldownTime{ 5.f }
	, m_DashCooldownTimer{ 5.f }
	, m_DashDistance{ 2000.f }
	, m_bIsSprinting( false )
	, m_bCanSprint( true )

    , m_AttackTime(3.5f)
    , m_bIsAttacking( false )

    , m_MovementSpeed{ 500.f }
    , m_bCanPhaseThroughWall( false )

    , m_bIsDead( false )
    , m_bIsDying( false )
	//, m_bDebugMode( false )

	, m_DeathAnimationTime(2.f)
	, m_DeathTimer(0.f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

    AutoPossessPlayer = EAutoReceiveInput::Player0;

    auto collider = Cast<UCapsuleComponent>(GetRootComponent());
	if(collider)
	{
        collider->SetCapsuleRadius(collider->GetUnscaledCapsuleRadius() * 1.5f);
	}
	
    // Create a camera and a visible object
    m_pCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("m_pCamera"));
    m_pArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("m_pArm"));

	// Attach our camera and visible object to our root component. Offset and rotate the camera.
    m_pCamera->SetupAttachment(m_pArm);
    m_pArm->SetupAttachment(RootComponent);
    m_pArm->bInheritYaw = false;
    m_pArm->bInheritPitch = false;
    m_pArm->bDoCollisionTest = false;
    m_pArm->SetRelativeRotation(FRotator(-50.f, 0.f, 0.f));
    m_pArm->TargetArmLength = 850.f;

    m_pAttachment = CreateDefaultSubobject<USceneComponent>(TEXT("m_pAttachment"));
    m_pAttachment->SetupAttachment(RootComponent);
    m_AttachmentPosition = FVector(75.f, 0.f, 0.f);
    m_pAttachment->SetRelativeLocation(m_AttachmentPosition);

	
    m_pBloodMeter = CreateDefaultSubobject<UBloodMeter>(TEXT("m_pBloodMeter"));
	m_pScoreSystem = CreateDefaultSubobject<UScoreSystem>(TEXT("m_pScoreSystem"));
    m_pClaw = CreateDefaultSubobject<APlayerClaw>(TEXT("m_pClaw"));

}

// Called when the game starts or when spawned
void APlayerMonster::BeginPlay()
{
	Super::BeginPlay();

    m_pClaw = GetWorld()->SpawnActor<APlayerClaw>(m_pAttachment->GetRelativeLocation(), m_pAttachment->GetRelativeRotation());
    const auto mesh{ GetMesh() };
    if (mesh) 
    {
        m_pClaw->AttachToComponent(mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "AttackSocket");
    }
	
    m_pClaw->SetOwner(this);
    m_pClaw->SetTimeToLive(m_AttackTime);

    m_pClaw->SetDebugMode(m_bDebugMode);

}

void APlayerMonster::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
	
    UCharacterMovementComponent* movement{ GetCharacterMovement() };
    if (movement)
    {
        bUseControllerRotationYaw = false;
        movement->bOrientRotationToMovement = true;
        movement->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
        movement->MaxWalkSpeed = m_MovementSpeed;
    }
}

// Called every frame
void APlayerMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
	
    m_pClaw->Tick(DeltaTime);

    if (!m_bIsDying)
    {

        if (m_pBloodMeter->IsMeterEmpty())
        {
            Die();
        }

#pragma region Dash
        UCharacterMovementComponent* movement{ GetCharacterMovement() };
        if (movement)
        {
            if (movement->Velocity.Size() <= m_MovementSpeed)
            {
                // if not dashing disable bool, on overlap will check for npc -> if npc Kill NPC
                m_bIsSprinting = false;
            }
        }

        if (!m_bCanSprint)
        {
            m_DashCooldownTimer += DeltaTime;

            if (m_DashCooldownTimer >= m_DashCooldownTime)
            {
                m_bCanSprint = true;
                GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "Can sprint again");

            }
        }
#pragma endregion

        CheckAbilityUnlocks();
    }
    else
    {
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
        }
    }

}

// Called to bind functionality to input
void APlayerMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    //InputComponent->BindAction("AnyKey", IE_Pressed, this, &APlayerMonster::CheckGamePadInUse);
    InputComponent->BindAction(TEXT("Any Key"), IE_Pressed, this, &APlayerMonster::CheckGamePadInUse).bExecuteWhenPaused = true;
	
	// Sprinting toggle
    InputComponent->BindAction("Dash", IE_Pressed, this, &APlayerMonster::Dash);

    // Respond every frame to the values of our two movement axes, "MoveX" and "MoveY". UE4 uses X-axis as forward axis
    InputComponent->BindAxis("Movement_X", this, &APlayerMonster::MoveAlongXAxis);
    InputComponent->BindAxis("Movement_Y", this, &APlayerMonster::MoveAlongYAxis);

    // Attack toggle
    InputComponent->BindAction("Attack", IE_Pressed, this, &APlayerMonster::Attack);

	// Pause Game	(sets binding and enables use during pause)
    InputComponent->BindAction("Pause", IE_Pressed, this, &APlayerMonster::Pause).bExecuteWhenPaused = true;
    
    InputComponent->BindAction("Lock", IE_Pressed, this, &APlayerMonster::LockDoors);
    
}

bool APlayerMonster::GetCanPhaseThroughWall() const
{
    return m_bCanPhaseThroughWall;
}

void APlayerMonster::MoveAlongXAxis(float axisValue)
{
    AController* controller{ GetController() };
    UCharacterMovementComponent* movement{ GetCharacterMovement() };
    if (controller && (axisValue != 0.0f))
    {
        // find out which way is forward
        FRotator Rotation = Controller->GetControlRotation();
        // Limit pitch when walking or falling
        if (movement->IsMovingOnGround() || movement->IsFalling())
        {
            Rotation.Pitch = 0.0f;
        }
        // add movement in that direction
        const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
        AddMovementInput(Direction, axisValue);
    }
}

void APlayerMonster::MoveAlongYAxis(float axisValue)
{
    AController* controller{ GetController() };
    UCharacterMovementComponent* movement{ GetCharacterMovement() };
    if (controller && (axisValue != 0.0f))
    {
        // find out which way is forward
        FRotator Rotation = Controller->GetControlRotation();
        // Limit pitch when walking or falling
        if (movement->IsMovingOnGround() || movement->IsFalling())
        {
            Rotation.Pitch = 0.0f;
        }
        // add movement in that direction
        const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
        AddMovementInput(Direction, axisValue);
    }
}

void APlayerMonster::Dash()
{
	if(m_bCanSprint)
	{
        const UCharacterMovementComponent* movementComponent = GetCharacterMovement();
        if (movementComponent)
        {
            auto forward = movementComponent->Velocity.GetSafeNormal();
            forward *= m_DashDistance;
            LaunchCharacter(forward, true, true);
        }

        //GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, "Dash");
        m_pBloodMeter->AddBlood(-5.f);
		
        m_bCanSprint = false;
        m_bIsSprinting = true;
		m_DashCooldownTimer = 0.f;
	}
}

void APlayerMonster::Attack()
{

    if (m_pClaw->CanAttack()) 
    {
        m_pClaw->StartAttack();
        m_bIsAttacking = true;

    }
	
}

void APlayerMonster::Die()
{
    GEngine->AddOnScreenDebugMessage(3, 1, FColor::Red, "Dead", true);
    m_bIsDying = true;

}

float APlayerMonster::GetClawAttackTime() const
{
    return m_pClaw->GetTimeAlive();
}

float APlayerMonster::GetAttackTimeToLive() const
{
    return m_AttackTime;
}

float APlayerMonster::GetBloodMeterPercentFill() const
{
    return (m_pBloodMeter->GetBlood() / m_pBloodMeter->GetMaxBlood());
}

BloodTiers APlayerMonster::GetBloodMeterCurrentTier() const
{
    return m_pBloodMeter->GetCurrentTier();
}

void APlayerMonster::AddBlood(float bloodValue) const
{
	if(bloodValue > 0.f)
	{
        m_pScoreSystem->NPCWasKilled(bloodValue);
	}
	
    m_pBloodMeter->AddBlood(bloodValue);
}

bool APlayerMonster::IsDying() const
{
    return m_bIsDying;
}

bool APlayerMonster::IsDead() const
{
    return m_bIsDead;
}

void APlayerMonster::CheckGamePadInUse(FKey key)
{
    if (key.IsMouseButton() || !key.IsGamepadKey())
    {
        m_bUsingController = false;
    }
    else if (key.IsGamepadKey()) 
    {
        m_bUsingController = true;
    }
	else
    {
        m_bUsingController = false;    
    }
}

bool APlayerMonster::GetUsingController() const
{
    return m_bUsingController;
}

float APlayerMonster::GetDashCooldownTime() const
{
    return m_DashCooldownTime;
}

float APlayerMonster::GetDashCooldownTimer() const
{
    return m_DashCooldownTimer;
}

void APlayerMonster::SetDashCooldownTimer(float newValue)
{
    if (newValue > 0.f) {
        m_DashCooldownTimer = newValue;
    }
}

float APlayerMonster::GetDashDistance() const
{
    return m_DashDistance;
}

bool APlayerMonster::IsSprinting() const
{
    return m_bIsSprinting;
}

bool APlayerMonster::CanSprint() const
{
    return m_bCanSprint;
}

void APlayerMonster::SetCanSprint(bool canSprint)
{
    m_bCanSprint = canSprint;
}

float APlayerMonster::GetMaxAttackTime() const
{
    return m_AttackTime;
}

bool APlayerMonster::IsAttacking() const
{
    return m_bIsAttacking;
}

void APlayerMonster::SetIsAttacking(bool attacking)
{
    m_bIsAttacking = attacking;
}

void APlayerMonster::CheckAbilityUnlocks()
{
    if (m_pBloodMeter->GetCurrentTier() >= BloodTiers::Tier_3)
    {
        m_bCanPhaseThroughWall = true;
        GEngine->AddOnScreenDebugMessage(1, 1, FColor::Green, "Enabled wall phasing", true);

    }
    else
    {
        m_bCanPhaseThroughWall = false;
        GEngine->AddOnScreenDebugMessage(1, 1, FColor::Green, "Disabled wall phasing", true);

    }
}

void APlayerMonster::Pause()
{
    const auto gameMode{ Cast<ATheBackroomsGameModeBase>(GetWorld()->GetAuthGameMode()) };
	if(gameMode)
	{
        gameMode->PauseGame();
	}
}

void APlayerMonster::LockDoors()
{
    TSubclassOf<ALockDoor> classToFind;
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALockDoor::StaticClass(), FoundActors);

    for (AActor* doors : FoundActors)
    {
        ALockDoor* Door = Cast<ALockDoor>(doors);
        if (doors->GetDistanceTo(this) <= Door->GetLockRadius())
        {
            Door->CloseDoor();
        }
    }
}

