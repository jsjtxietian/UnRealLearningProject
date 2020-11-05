#include "GameUserWidget.h"
#include "EngineUtils.h"
#include "Fire.h"
#include "Kismet/GameplayStatics.h"

UGameUserWidget::UGameUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UGameUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FireComponent = myCharacter->FindComponentByClass<UFire>();
	
	ShootButton->OnClicked.AddDynamic(this, &UGameUserWidget::Fire);
	JumpButton->OnClicked.AddDynamic(this, &UGameUserWidget::Jump);
}


void UGameUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Your Score: %d\n"), int(FireComponent->totalScore))));
}

void UGameUserWidget::Fire()
{
	FireComponent->Fire();
}

void UGameUserWidget::Jump()
{
	myCharacter->Jump();
}