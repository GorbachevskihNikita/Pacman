// Fill out your copyright notice in the Description page of Project Settings.


#include "PacmanCharacter.h"

#include "Collectable.h"
#include "EngineUtils.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APacmanCharacter::APacmanCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetActorEnableCollision(true);

}

void APacmanCharacter::OnCollision(UPrimitiveComponent* PrimitiveComponent, AActor* Actor,
	UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult)
{
	if (GameMode->GetCurrentState() == EGameState::EPlaying)
	{
		if (Actor->IsA(ACollectable::StaticClass()))
		{
			Actor->Destroy();
		}
	}

	if (CollectablesToEat == 0)
	{
		GameMode->SetCurrentState(EGameState::EWin);
	}
}

/*void APacmanCharacter::OnCollision(AActor* Actor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	
}*/

// Called when the game starts or when spawned
void APacmanCharacter::BeginPlay()
{
	Super::BeginPlay();
	StartPoint = GetActorLocation();
	Lives = 3;
	GameMode = Cast<APacmanGameModeBase>(UGameplayStatics::GetGameMode(this));
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APacmanCharacter::OnCollision);
	for (TActorIterator<ACollectable> CollectableItr(GetWorld()); CollectableItr; ++CollectableItr)
	{
		CollectablesToEat++;
	}
}

// Called every frame
void APacmanCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APacmanCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveX", this, &APacmanCharacter::MoveXAxis);
	InputComponent->BindAxis("MoveY", this, &APacmanCharacter::MoveYAxis);
	InputComponent->BindAction("NewGame", IE_Pressed, this, &APacmanCharacter::NewGame);
	InputComponent->BindAction("Pause", IE_Pressed, this, &APacmanCharacter::Pause);
	InputComponent->BindAction("RestartGame", IE_Pressed, this, &APacmanCharacter::RestartGame);
}

void APacmanCharacter::MoveXAxis(float AxisValue)
{
	CurrentVelocity.X = AxisValue;
	AddMovementInput(CurrentVelocity);
}

void APacmanCharacter::MoveYAxis(float AxisValue)
{
	CurrentVelocity.Y = AxisValue;
	AddMovementInput(CurrentVelocity);
}

void APacmanCharacter::NewGame()
{
	if (GameMode->GetCurrentState() == EGameState::EMenu)
	{
		GameMode->SetCurrentState(EGameState::EPlaying);
	}
	
}

void APacmanCharacter::Pause()
{
	if (GameMode->GetCurrentState() == EGameState::EPlaying)
	{
		GameMode->SetCurrentState(EGameState::EPause);
	}
	else if (GameMode->GetCurrentState() == EGameState::EPause)
	{
		GameMode->SetCurrentState(EGameState::EPlaying);
	}
}

void APacmanCharacter::RestartGame()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("RestartLevel"));
}

void APacmanCharacter::Kill()
{
	if (Lives == 0)
	{
		GameMode->SetCurrentState(EGameState::EGameOver);
	}
	else
	{
		SetActorLocation(StartPoint);
	}
}

