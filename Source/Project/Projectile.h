#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystem.h"
#include "Projectile.generated.h"

UCLASS()
class PROJECT_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sphere collision component.
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* VisualMesh;

	// Projectile movement component.
	UPROPERTY(VisibleAnywhere, Category = Movement)
		UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
		float Score1 = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
		float Score2 = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
		float Score3 = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
		UParticleSystem* ExplosionEffect;

	// Function that initializes the projectile's velocity in the shoot direction.
	void FireInDirection(const FVector& ShootDirection);

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};
