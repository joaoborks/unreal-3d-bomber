// Created by Joao Borks [joao.borks@gmail.com] 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BombDestroyable.h"
#include "BlockBreakable.generated.h"

UCLASS()
class UNREALBOMBERMAN_API ABlockBreakable : public AActor, public IBombDestroyable
{
	GENERATED_BODY()
	
public:	
	ABlockBreakable();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Bomb Blast")
	// Event called by the bomb when it blows and hits an object
	void OnBombBlastHit();
	// Event called by the bomb when it blows and hits an object
	virtual void OnBombBlastHit_Implementation() override;
};