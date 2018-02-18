// Created by Joao Borks [joao.borks@gmail.com] 2018

#include "Bomb.h"

// Sets default values
ABomb::ABomb()
{

}

void ABomb::BeginPlay()
{
	Super::BeginPlay();
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

}