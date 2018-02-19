// Created by Joao Borks [joao.borks@gmail.com] 2018

#include "BlastFx.h"

ABlastFx::ABlastFx()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABlastFx::SetupBlast(FVector InitPos, FVector LastPos) 
{
	SetActorLocation(FMath::Lerp(InitPos, LastPos, .5f));
	float Stretch = FVector::Distance(InitPos, LastPos) / 100.f;
	FVector TargetScale = GetActorScale3D();
	if (InitPos.Y == LastPos.Y)
		TargetScale.X = Stretch;
	else
		TargetScale.Y = Stretch;
	SetActorScale3D(TargetScale);
}