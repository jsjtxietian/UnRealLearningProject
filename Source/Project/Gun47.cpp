// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun47.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"

// Sets default values
AGun47::AGun47()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> GunAsset(TEXT("/Game/Weapon/Weapons/Meshes/Ka47/SK_KA47"));
	if (GunAsset.Succeeded())
	{
		GunMesh->SetSkeletalMesh(GunAsset.Object);
		GunMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
}

// Called when the game starts or when spawned
void AGun47::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun47::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

