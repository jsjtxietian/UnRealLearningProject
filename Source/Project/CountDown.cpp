#include "CountDown.h"
#include "Fire.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "NameScore.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

struct FSingle;

// Sets default values
ACountDown::ACountDown()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountdownNumber"));
	CountdownText->SetHorizontalAlignment(EHTA_Center);
	CountdownText->SetWorldSize(150.0f);
	RootComponent = CountdownText;
	CountdownTime = 10;
}


// Called when the game starts or when spawned
void ACountDown::BeginPlay()
{
	Super::BeginPlay();
	UpdateTimerDisplay();
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACountDown::AdvanceTimer, 1.0f, true);

	GameUI = Cast<UGameUserWidget>(CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(), 0), GameUIType));
	GameUI->SingleScoreUI = SingleScoreUI;
	GameUI->AddToViewport();
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

	auto FireComponent = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->FindComponentByClass<UFire>();
	FireComponent->InPlay = false;

	const FString SlotName = FString::FromInt(0);

	FSingle Current;
	Current.PlayerName = GameUI->NameInput->GetText().ToString();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, Current.PlayerName);

	Current.PlayerScore = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetPlayerState()->GetScore();

	if (UNameScore* LoadedGame = Cast<UNameScore>(UGameplayStatics::LoadGameFromSlot(SlotName, 0)))
	{
		LoadedGame->Saves.Add(Current);
		LoadedGame->Saves.Sort([](FSingle A, FSingle B) {
			return A.PlayerScore >= B.PlayerScore;
		});

		// Save the data immediately.
		if (UGameplayStatics::SaveGameToSlot(LoadedGame, SlotName, 0))
		{
			int Count = 0;
			for(auto save : LoadedGame->Saves)
			{
				GameUI->ShowSingleScore(save.PlayerName, save.PlayerScore);
				if(++Count > 10)
					break;
			}
		}
	}
	else
	{
		if (UNameScore* SaveGameInstance = Cast<UNameScore>(UGameplayStatics::CreateSaveGameObject(UNameScore::StaticClass())))
		{
			SaveGameInstance->Saves.Add(Current);
			UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0);
		}
	}

}

// Called every frame
void ACountDown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

