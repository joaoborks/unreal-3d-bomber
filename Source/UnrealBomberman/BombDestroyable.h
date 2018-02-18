// Created by Joao Borks [joao.borks@gmail.com] 2018

#pragma once

#include "CoreMinimal.h"
#include "BombDestroyable.generated.h"

UINTERFACE(BlueprintType)
class UNREALBOMBERMAN_API UBombDestroyable : public UInterface
{
	GENERATED_BODY()
};

class UNREALBOMBERMAN_API IBombDestroyable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Bomb Blast")
	// Event called by the bomb when it blows and hits an object
	void OnBombBlastHit();
};