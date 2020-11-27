// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Character.h"
#include "Gun.generated.h"

UCLASS()
class PROJECT_API AGun : public AActor
{
	GENERATED_BODY()

public:
	AGun() { PrimaryActorTick.bCanEverTick = true; };

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) ;

	
	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* GunMesh;

	UFUNCTION()
		virtual void Fire() {};

	UFUNCTION()
		virtual void FireAnimation();

	//50 40 -60
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

	// Gun muzzle's offset from the camera location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UAnimMontage* GunMontage;

	ACharacter* Player;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
