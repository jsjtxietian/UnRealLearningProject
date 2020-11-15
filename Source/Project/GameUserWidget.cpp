#include "GameUserWidget.h"
#include "EngineUtils.h"
#include "Fire.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/Character.h"

UGameUserWidget::UGameUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UGameUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MyCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FireComponent = MyCharacter->FindComponentByClass<UFire>();
	
	ShootButton->OnClicked.AddDynamic(this, &UGameUserWidget::Fire);
	JumpButton->OnClicked.AddDynamic(this, &UGameUserWidget::Jump);
}


void UGameUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Your Score: %d\n"), int(MyCharacter->GetPlayerState()->GetScore()))));
}

void UGameUserWidget::Fire()
{
	FireComponent->Fire();
}

void UGameUserWidget::Jump()
{
	MyCharacter->Jump();
}