#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveScore.generated.h"

UCLASS()
class USaveData : public UObject {
	GENERATED_BODY()

public:
	USaveData() {}

	FString PlayerName;
	float PlayerScore;
};


/**
 *
 */
UCLASS()
class PROJECT_API USaveScore : public USaveGame
{
	GENERATED_BODY()

public:
	USaveScore();

	UPROPERTY(VisibleAnywhere, Category = Basic)
	TArray<USaveData*> Saves;
};
