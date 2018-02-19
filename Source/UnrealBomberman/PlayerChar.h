// Created by Joao Borks [joao.borks@gmail.com] 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Bomb.h"
#include "PlayerChar.generated.h"

UCLASS()
class UNREALBOMBERMAN_API APlayerChar : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerChar();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<ABomb*> PlacedBombs;

protected:
	UFUNCTION(BlueprintCallable)
	FTransform& GetSnappedPosition(FTransform Source) const;

private:
	float GetSnappedValue(int Value, float Scale) const;
};
