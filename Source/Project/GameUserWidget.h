// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fire.h"
#include "SingleScore.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/EditableText.h"
#include "Components/VerticalBox.h"
#include "GameFramework/Character.h"
#include "GameUserWidget.generated.h"

struct FSingle;

UCLASS()
class PROJECT_API UGameUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UGameUserWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* ShootButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* JumpButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* ScoreText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UEditableText* NameInput;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UVerticalBox* ScoreArea;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UCanvasPanel* ScoreBoard;

	UPROPERTY(EditAnywhere)
		TSubclassOf<USingleScore> SingleScoreUI;

	UFUNCTION()
		void ShowSingleScore(FString Name ,float Score);

private:
	// Optionally override the Blueprint "Event Construct" event
	virtual void NativeConstruct() override;

	// Optionally override the tick event
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
		void Fire();

	UFUNCTION()
		void Jump();

	ACharacter* MyCharacter;
	UFire* FireComponent;

	int Order = 0;
};
