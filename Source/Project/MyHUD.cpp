#include "MyHUD.h"
#include "Engine/Canvas.h"
#include "EngineUtils.h"
#include "Fire.h"

void AMyHUD::DrawHUD()
{
    Super::DrawHUD();

    // Find Actors by tag (also works on ActorComponents, use TObjectIterator instead)
    for (TActorIterator<AActor> It(GetWorld()); It; ++It)
    {
        AActor* Actor = *It;
        if (Actor->ActorHasTag(FName(TEXT("Player"))))
        {
            auto Fire = Actor->FindComponentByClass<UFire>();
            DrawText(FString::Printf(TEXT("Your Score: %d\n"), int(Fire->totalScore)), FColor::White, Canvas->SizeX / 2.0f - 40, 30);
        }
    }
}