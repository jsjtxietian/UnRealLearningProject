
#include "GameUserWidget.h"
#include "EngineUtils.h"
#include "Fire.h"

UGameUserWidget::UGameUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UGameUserWidget::NativeConstruct()
{
	// Do some custom setup
	// Call the Blueprint "Event Construct" node
	Super::NativeConstruct();

	// Find Actors by tag (also works on ActorComponents, use TObjectIterator instead)
	for (TActorIterator<AActor> It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		if (Actor->ActorHasTag(FName(TEXT("Player"))))
		{
			FireComponent = Actor->FindComponentByClass<UFire>();
		}
	}

	ItemTitle->SetText(FText::FromString("Hey!"));
	ShootButton->OnClicked.AddDynamic(this, &UGameUserWidget::Fire);
	JumpButton->OnClicked.AddDynamic(this, &UGameUserWidget::Jump);
}


void UGameUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	// Make sure to call the base class's NativeTick function
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Do your custom tick stuff here
}

void UGameUserWidget::Fire()
{
	FireComponent->Fire();
}

void UGameUserWidget::Jump()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("This message will appear on the screen!"));
}