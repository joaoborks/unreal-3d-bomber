// Created by Joao Borks [joao.borks@gmail.com] 2018

#include "Powerup.h"

APowerup::APowerup()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APowerup::OnBombBlastHit_Implementation()
{
	Destroy();
}