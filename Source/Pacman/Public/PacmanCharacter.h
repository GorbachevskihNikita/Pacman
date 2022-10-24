// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Pacman/PacmanGameModeBase.h"
#include "PacmanCharacter.generated.h"

UCLASS()
class PACMAN_API APacmanCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APacmanCharacter();

protected:
	UFUNCTION()
	void OnCollision(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult);
	UFUNCTION()
	
	//void OnCollision(AActor* Actor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveXAxis(float AxisValue);
	void MoveYAxis(float AxisValue);

	void NewGame();
	void Pause();
	void RestartGame();
	void Kill();
	
	FVector CurrentVelocity;

	APacmanGameModeBase* GameMode;

	uint8 CollectablesToEat;
	uint8 Lives;

	FVector StartPoint;
};
