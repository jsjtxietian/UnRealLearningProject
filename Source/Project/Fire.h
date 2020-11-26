// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Fire.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECT_API UFire : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFire();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Fire();

	// Gun muzzle's offset from the camera location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;
	// Gun muzzle's offset from the camera location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UAnimMontage* GunMontage;

	UStaticMeshComponent* GunMesh;
	bool InPlay = true;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void FireAnimation();

};
