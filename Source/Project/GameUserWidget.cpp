#include "GameUserWidget.h"
#include "EngineUtils.h"
#include "Fire.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/Character.h"



void UGameUserWidget::ShowSingleScore(FString Name, float Score)
{
	ScoreBoard->SetRenderOpacity(1);

	USingleScore* Single = Cast<USingleScore>(CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(), 0), SingleScoreUI));
	Single->Order->SetText(FText::FromString(FString::Printf(TEXT("%02d"), Order++)));
	Single->Name->SetText(FText::FromString(Name));
	Single->Score->SetText(FText::FromString(FString::FromInt(int(Score))));

	ScoreArea->AddChild(Single);
}

void UGameUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MyCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FireComponent = MyCharacter->FindComponentByClass<UFire>();
	
	ShootButton->OnClicked.AddDynamic(this, &UGameUserWidget::Fire);
	JumpButton->OnClicked.AddDynamic(this, &UGameUserWidget::Jump);

	ScoreBoard->SetRenderOpacity(0);
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

UGameUserWidget::UGameUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}