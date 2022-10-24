// Fill out your copyright notice in the Description page of Project Settings.


#include "Pacman/Public/Collectable.h"

ACollectable::ACollectable()
{
	// disable the tick call
	PrimaryActorTick.bCanEverTick = false;

	// enable collision
	SetActorEnableCollision(true);

	// initialize the collission sphere component
	BaseCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BaseCollisionComponent"));

	// initialize the mesh for the collectable and attach to the root
	CollectableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollectableMesh"));
	CollectableMesh->AttachToComponent(BaseCollisionComponent, FAttachmentTransformRules::KeepWorldTransform, BaseCollisionComponent->GetAttachSocketName());

	// find a reference to the sphere mesh and set it
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (Sphere.Succeeded())
	{
		CollectableMesh->SetStaticMesh(Sphere.Object);
		//set the default parameters of the collectable
		CollectableMesh->SetWorldScale3D(FVector3d(0.3, 0.3, 0.3));
		BaseCollisionComponent->SetSphereRadius(16);
	}
}
