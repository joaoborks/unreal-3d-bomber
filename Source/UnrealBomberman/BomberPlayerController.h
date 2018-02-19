// Created by Joao Borks [joao.borks@gmail.com] 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BomberPlayerController.generated.h"

UCLASS()
class UNREALBOMBERMAN_API ABomberPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ABomberPlayerController();

protected:
	virtual void Reset() override;
	virtual void SetupInputComponent() override;
	
	void MoveHorizontal(float AxisValue);
	void MoveVertical(float AxisValue);
	void SpawnBombInput();
	void RemoteDetonateInput();
};
