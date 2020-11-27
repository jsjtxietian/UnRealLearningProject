// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "GunSMG.generated.h"

/**
 *
 */
UCLASS()
class PROJECT_API AGunSMG : public AGun
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGunSMG();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* ExplosionEffect;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Fire() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
