#pragma once

#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CountDown.generated.h"

UCLASS()
class PROJECT_API ACountDown : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACountDown();

	UPROPERTY(EditAnywhere)
	int32 CountdownTime;

	void CountdownHasFinished();

	UTextRenderComponent* CountdownText;
	FTimerHandle CountdownTimerHandle;

	void UpdateTimerDisplay();
	void AdvanceTimer();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};