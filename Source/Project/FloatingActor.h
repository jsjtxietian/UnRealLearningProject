// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingActor.generated.h"

UCLASS()
class PROJECT_API AFloatingActor : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloatingActor")
		float FloatSpeed = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloatingActor")
		float Score1 = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloatingActor")
		float Score2 = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloatingActor")
		float Score3 = 10.0f;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* VisualMesh;

	// Sets default values for this actor's properties
	AFloatingActor();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
