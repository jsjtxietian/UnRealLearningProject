#include "Fire.h"
#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "Gun47.h"

// Sets default values for this component's properties
UFire::UFire()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UFire::BeginPlay()
{
	Super::BeginPlay();

	auto Input = this->GetOwner()->FindComponentByClass<UInputComponent>();
	Input->BindAction("Fire", IE_Pressed, this, &UFire::Fire);

}

void UFire::Fire()
{
	if (!InPlay || PlayerGun == nullptr)
		return;

	PlayerGun->Fire();
}

// Called every frame
void UFire::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

