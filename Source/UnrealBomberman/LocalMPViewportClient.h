// Created by Joao Borks [joao.borks@gmail.com] 2018

#pragma once

#include "Engine.h"
#include "Engine/GameViewportClient.h"
#include "LocalMPViewportClient.generated.h"

UCLASS()
class UNREALBOMBERMAN_API ULocalMPViewportClient : public UGameViewportClient
{
	GENERATED_BODY()
	
protected:
	virtual bool InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed = 1.f, bool bGamepad = false) override;
};