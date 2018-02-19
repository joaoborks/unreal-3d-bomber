// Created by Joao Borks [joao.borks@gmail.com] 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlastFx.generated.h"

UCLASS()
class UNREALBOMBERMAN_API ABlastFx : public AActor
{
	GENERATED_BODY()
	
public:
	ABlastFx();

	UFUNCTION(BlueprintCallable)
	void SetupBlast(FVector InitPos, FVector LastPos);
};