#include "Fire.h"
#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "Components/InputComponent.h"

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

	GetOwner()->Tags.AddUnique(TEXT("Player"));

	totalScore = 0;
}

void UFire::Fire()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("Fire!!! Total score %f"),totalScore));

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

