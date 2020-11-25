#include "Fire.h"
#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "Gun47.h"

// Sets default values for this component's properties
UFire::UFire()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	
}


// Called when the game starts
void UFire::BeginPlay()
{
	Super::BeginPlay();

	auto Input = this->GetOwner()->FindComponentByClass<UInputComponent>();
	Input->BindAction("Fire", IE_Pressed, this, &UFire::Fire);

	AGun47* Gun = GetWorld()->SpawnActor<AGun47>();
	Gun->AttachToComponent(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GunSocket"));

	GetOwner()->Tags.AddUnique(TEXT("Player"));
}

void UFire::Fire()
{
	if (!InPlay)
		return;

	// Attempt to fire a projectile.
	// Get the camera transform.
	FVector CameraLocation;
	FRotator CameraRotation;
	this->GetOwner()->GetActorEyesViewPoint(CameraLocation, CameraRotation);

	// Transform MuzzleOffset from camera space to world space.
	FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
	FRotator MuzzleRotation = CameraRotation;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this->GetOwner();
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
void UFire::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

