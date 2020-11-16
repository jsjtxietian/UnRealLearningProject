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


	if (UNameScore* LoadedGame = Cast<UNameScore>(UGameplayStatics::LoadGameFromSlot(SlotName, 0)))
	{
		// The operation was successful, so LoadedGame now contains the data we saved earlier.
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Load Success"));

		//if (UNameScore* SaveGameInstance = Cast<UNameScore>(UGameplayStatics::CreateSaveGameObject(UNameScore::StaticClass())))
		//{
			// Set data on the savegame object.
		FSingle Current;
		Current.PlayerName = GameUI->NameInput->Text.ToString();
		Current.PlayerScore = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetPlayerState()->GetScore();
		LoadedGame->Saves.Add(Current);

		/*SaveGameInstance->Saves.Sort([](USaveData* A, USaveData* B) {
			return A->PlayerScore > B->PlayerScore;
		});*/

		// Save the data immediately.
		if (UGameplayStatics::SaveGameToSlot(LoadedGame, SlotName, 0))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::SanitizeFloat(LoadedGame->Saves[0].PlayerScore));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::SanitizeFloat(LoadedGame->Saves.Last().PlayerScore));
		}
		//}
	}

}

// Called when the game starts or when spawned
void ACountDown::BeginPlay()
{
	Super::BeginPlay();
	UpdateTimerDisplay();
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACountDown::AdvanceTimer, 1.0f, true);

	GameUI = Cast<UGameUserWidget>(CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(), 0), GameUIType));
	GameUI->AddToViewport();
}

// Called every frame
void ACountDown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

