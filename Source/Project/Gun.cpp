// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "Fire.h"


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
		auto PlayerGun = Player->FindComponentByClass<UFire>()->PlayerGun;

		if (PlayerGun != nullptr)
		{
			PlayerGun->Destroy();
		}

		Player->FindComponentByClass<UFire>()->PlayerGun = this;
		this->AttachToComponent(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GunSocket"));
		
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

