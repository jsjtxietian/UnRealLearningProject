// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun47.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Projectile.h"

// Sets default values
AGun47::AGun47()
	:AGun(TEXT("/Game/Weapon/Weapons/Meshes/Ka47/SK_KA47"))
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGun47::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun47::Fire()
{
	FireAnimation();

	// Attempt to fire a projectile.
	// Get the camera transform.
	FVector CameraLocation;
	FRotator CameraRotation;
	Player->GetActorEyesViewPoint(CameraLocation, CameraRotation);
	CameraRotation = Player->GetActorRotation();

	// Transform MuzzleOffset from camera space to world space.
	FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
	FRotator MuzzleRotation = CameraRotation;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Player;
	// Skew the aim to be slightly upwards.
	MuzzleRotation.Pitch += 10.0f;
	UWorld* World = GetWorld();
	if (World)
	{
		AProjectile* Projectile = World->SpawnActor<AProjectile>(MuzzleLocation, MuzzleRotation, SpawnParams);
		if (Projectile)
		{
			// Set the projectile's initial trajectory.
			FVector LaunchDirection = MuzzleRotation.Vector();
			Projectile->FireInDirection(LaunchDirection);
		}
	}
}


// Called every frame
void AGun47::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

