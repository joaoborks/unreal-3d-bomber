// Created by Joao Borks [joao.borks@gmail.com] 2018

#include "Bomb.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BombDestroyable.h"

// Sets default values
ABomb::ABomb()
{
}

void ABomb::BeginPlay()
{
	Super::BeginPlay();

	// Assign Box Overlap Event
	Box = Cast<UBoxComponent>(GetComponentByClass(UBoxComponent::StaticClass()));
	Box->OnComponentEndOverlap.AddDynamic(this, &ABomb::OnOverlapEnd);
}

void ABomb::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (GetOwner() == OtherActor)
		Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
}

void ABomb::Detonate()
{
	// Must destroy before traces otherwise will create infinite loop
	Destroy();
	LineTraceDirection(GetActorRightVector());
	LineTraceDirection(GetActorForwardVector());
	LineTraceDirection(- GetActorRightVector());
	LineTraceDirection(- GetActorForwardVector());
}

void ABomb::LineTraceDirection(FVector Direction)
{
	FHitResult ObstacleHit;
	TArray<FHitResult> Hits;
	FVector Origin = GetCenterLocation();
	FVector Target = Origin + Direction * BlastRange * 100.f;
	FCollisionQueryParams Params = FCollisionQueryParams();
	Params.AddIgnoredActor(this);
	GetWorld()->LineTraceMultiByChannel(Hits, Origin, Target, ECollisionChannel::ECC_Visibility, Params);
	if (Hits.Num() > 0)
	{
		if (Hits.Last().bBlockingHit)
			Target = Hits.Last().ImpactPoint;
		IBombDestroyable* Destroyable;
		for (auto& Hit : Hits)
		{
			Destroyable = Cast<IBombDestroyable>(Hit.GetActor());
			if (Destroyable)
				Destroyable->Execute_OnBombBlastHit(Hit.GetActor());
		}
	}
	UKismetSystemLibrary::DrawDebugLine(GetWorld(), Origin, Target, FLinearColor(.8f, 0.f, 0.f), 3, 20);
}

void ABomb::OnBombBlastHit_Implementation() 
{
	Detonate();
}

FVector ABomb::GetCenterLocation() const
{
	return GetActorLocation() + FVector(0.f, 0.f, 50.f);
}