#include "CountDown.h"
#include "Fire.h"
#include "EngineUtils.h"

// Sets default values
ACountDown::ACountDown()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
    CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountdownNumber"));
    CountdownText->SetHorizontalAlignment(EHTA_Center);
    CountdownText->SetWorldSize(150.0f);
    RootComponent = CountdownText;
    CountdownTime = 3;
}

void ACountDown::UpdateTimerDisplay()
{
    CountdownText->SetText(FString::FromInt(FMath::Max(CountdownTime, 0)) + TEXT("s Left To Shoot!"));
}

void ACountDown::AdvanceTimer()
{
    --CountdownTime;
    UpdateTimerDisplay();
    if (CountdownTime < 1)
    {
        //We're done counting down, so stop running the timer.
        GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
        CountdownHasFinished();
    }
}

void ACountDown::CountdownHasFinished()
{
    //Change to a special readout
    CountdownText->SetText(TEXT("Game Over!"));

    for (TActorIterator<AActor> It(GetWorld()); It; ++It)
    {
        AActor* Actor = *It;
        if (Actor->ActorHasTag(FName(TEXT("Player"))))
        {
            auto Fire = Actor->FindComponentByClass<UFire>();
            Fire->InPlay = false;
        }
    }
}

// Called when the game starts or when spawned
void ACountDown::BeginPlay()
{
	Super::BeginPlay();
    UpdateTimerDisplay();
    GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACountDown::AdvanceTimer, 1.0f, true);
}

// Called every frame
void ACountDown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

