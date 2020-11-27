#include "Projectile.h"
#include "Fire.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = VisualMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BulletAsset(TEXT("/Game/Weapon/Weapons/Meshes/Ammunition/SM_Shell_40mm_G"));

	if (BulletAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(BulletAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

		VisualMesh->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
		VisualMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	}

	// Use this component to drive this projectile's movement.
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(VisualMesh);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("/Game/StarterContent/Particles/P_Explosion"));
	if (PS.Succeeded())
	{
		ExplosionEffect = PS.Object;
	}

	//SetActorScale3D(FVector(0.2f, 0.2f, 0.2f));
}

// Function that initializes the projectile's velocity in the shoot direction.
void AProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	auto name = OtherActor->GetName();
	auto Player = UGameplayStatics::GetPlayerCharacter(GetOwner()->GetWorld(), 0)->GetPlayerState();

	if (name.Contains("Target"))
	{
		if (name.Contains("Center"))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("Hit ~ %f"), Score1));
			Player->SetScore(Player->GetScore() + Score1);
		}
		else if (name.Contains("1"))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("Hit ~ %f"), Score2));
			Player->SetScore(Player->GetScore() + Score1);
		}
		else
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("Hit ~ %f"), Score3));
			Player->SetScore(Player->GetScore() + Score1);
		}
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
	}
	this->Destroy();
}
