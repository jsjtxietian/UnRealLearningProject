// Fill out your copyright notice in the Description page of Project Settings.


#include "GunSMG.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
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

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("/Game/StarterContent/Particles/P_Fire"));
	if (PS.Succeeded())
	{
		ExplosionEffect = PS.Object;
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
	FVector CameraLocation;
	FRotator LazerRotation;
	Player->GetActorEyesViewPoint(CameraLocation, LazerRotation);
	LazerRotation = Player->GetActorRotation();
	FVector MuzzleLocation = CameraLocation + FTransform(LazerRotation).TransformVector(MuzzleOffset);

	// You can use this to customize various properties about the trace
	FCollisionQueryParams Params;
	// Ignore the player's pawn
	Params.AddIgnoredActor(Player);
	// The hit result gets populated by the line trace
	FHitResult Hit;

	// Raycast out from the camera, only collide with pawns (they are on the ECC_Pawn collision channel)
	FVector Start = MuzzleLocation;
	FVector End = Start + (Player->GetActorRotation().Vector() * 1000.0f);

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_WorldStatic, Params);

	if (bHit)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White,AActor::GetDebugName(Hit.Actor.Get()));
		// return Cast<APawn>(Hit.Actor.Get());

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, Hit.Location);
	}

	FireAnimation();

}


// Called every frame
void AGunSMG::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

