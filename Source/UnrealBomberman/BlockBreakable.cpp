// Created by Joao Borks [joao.borks@gmail.com] 2018

#include "BlockBreakable.h"


ABlockBreakable::ABlockBreakable()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABlockBreakable::OnBombBlastHit_Implementation()
{
	Destroy();
}