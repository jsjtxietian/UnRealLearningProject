// Fill out your copyright notice in the Description page of Project Settings.


#include "GunSMG.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Projectile.h"

// Sets default values
AGunSMG::AGunSMG()
{
	PrimaryActorTick.bCanEverTick = true;

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunSMGMesh"));
	RootComponent = GunMesh;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> GunAsset(TEXT("/Game/Weapon/Weapons/Meshes/SMG11/SK_SMG11_Nostock_Y"));
	if (GunAsset.Succeeded())
	{
		GunMesh->SetSkeletalMesh(GunAsset.Object);
		GunMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		GunMesh->BodyInstance.SetCollisionProfileName(TEXT("BlockAll"));
		GunMesh->OnComponentHit.AddDynamic(this, &AGun::OnHit);
	}
}

// Called when the game starts or when spawned
void AGunSMG::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGunSMG::Fire()
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
void AGunSMG::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

