// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "SingleScore.generated.h"

/**
 *
 */
UCLASS()
class PROJECT_API USingleScore : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* Order;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* Name;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* Score;

};
