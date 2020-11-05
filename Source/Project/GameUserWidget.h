// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fire.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "GameFramework/Character.h"
#include "GameUserWidget.generated.h"

/**
 *
 */
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

	// Optionally override the Blueprint "Event Construct" event
	virtual void NativeConstruct() override;

	// Optionally override the tick event
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	void Fire();

	UFUNCTION()
	void Jump();

private:
	UFire* FireComponent;
	ACharacter* myCharacter;
};
