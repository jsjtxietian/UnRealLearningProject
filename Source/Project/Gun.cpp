// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Fire.h"

// Sets default values
AGun::AGun(const TCHAR* AssetLocation)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> GunAsset(AssetLocation);
	if (GunAsset.Succeeded())
	{
		GunMesh->SetSkeletalMesh(GunAsset.Object);
		GunMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		GunMesh->BodyInstance.SetCollisionProfileName(TEXT("BlockAll"));
		GunMesh->OnComponentHit.AddDynamic(this, &AGun::OnHit);
	}
}


void AGun::FireAnimation()
{
	if (USkeletalMeshComponent* Mesh = Player->FindComponentByClass<USkeletalMeshComponent>())
	{
		if (UAnimInstance* AnimInst = Mesh->GetAnimInstance())
		{
			AnimInst->Montage_Play(GunMontage);
			/*UBoolProperty* AniBool = FindField<UBoolProperty>(AnimInst->GetClass(), TEXT("IsFire"));
			if (AniBool != NULL)
			{
				AniBool->SetPropertyValue_InContainer(AnimInst, IsOn);
			}*/
		}
	}
}


void AGun::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	auto name = OtherActor->GetName();

	if (name.Contains("Player"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, name);
		this->AttachToComponent(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GunSocket"));
		Player->FindComponentByClass<UFire>()->PlayerGun = this;
		GunMesh->SetNotifyRigidBodyCollision(false);
		GunMesh->BodyInstance.SetCollisionProfileName(TEXT("NoCollision"));
		GunMesh->OnComponentCollisionSettingsChanged();
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

