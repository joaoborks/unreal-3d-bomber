// Created by Joao Borks [joao.borks@gmail.com] 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerChar.generated.h"

UCLASS()
class UNREALBOMBERMAN_API APlayerChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerChar();

protected:
	UFUNCTION(BlueprintCallable)
	FTransform& GetSnappedPosition(FTransform Source) const;

private:
	float GetSnappedValue(int Value, float Scale) const;
};
