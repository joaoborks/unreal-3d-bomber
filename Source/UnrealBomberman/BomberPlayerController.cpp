// Created by Joao Borks [joao.borks@gmail.com] 2018

#include "BomberPlayerController.h"
#include "Runtime/Engine/Classes/Engine/LocalPlayer.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "PlayerChar.h"

void ABomberPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (!InputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Input Component is invalid"));
		return;
	}
	int32 Id = GetLocalPlayer()->GetControllerId();
	if (Id == 0)
	{
		InputComponent->BindAxis("Horizontal_P1", this, &ABomberPlayerController::MoveHorizontal);
		InputComponent->BindAxis("Vertical_P1", this, &ABomberPlayerController::MoveVertical);
		InputComponent->BindAction("Bomb_P1", EInputEvent::IE_Pressed, this, &ABomberPlayerController::SpawnBombInput);
		InputComponent->BindAction("RemoteDetonate_P1", EInputEvent::IE_Pressed, this, &ABomberPlayerController::RemoteDetonateInput);
	}
	else if (Id == 1)
	{
		InputComponent->BindAxis("Horizontal_P2", this, &ABomberPlayerController::MoveHorizontal);
		InputComponent->BindAxis("Vertical_P2", this, &ABomberPlayerController::MoveVertical);
		InputComponent->BindAction("Bomb_P2", EInputEvent::IE_Pressed, this, &ABomberPlayerController::SpawnBombInput);
		InputComponent->BindAction("RemoteDetonate_P2", EInputEvent::IE_Pressed, this, &ABomberPlayerController::RemoteDetonateInput);
	}
}

void ABomberPlayerController::MoveHorizontal(float AxisValue)
{
	APawn* Pawn = GetPawn();
	if (Pawn)
		Pawn->AddMovementInput(Pawn->GetActorRightVector() * AxisValue);
}

void ABomberPlayerController::MoveVertical(float AxisValue)
{
	APawn* Pawn = GetPawn();
	if (Pawn)
		Pawn->AddMovementInput(Pawn->GetActorForwardVector() * AxisValue);
}

void ABomberPlayerController::SpawnBombInput()
{
	APawn* Pawn = GetPawn();
	if (Pawn)
	{
		APlayerChar* Player = Cast<APlayerChar>(Pawn);
		if (Player)
			Player->SpawnBomb();
	}
}

void ABomberPlayerController::RemoteDetonateInput()
{
	APawn* Pawn = GetPawn();
	if (Pawn)
	{
		APlayerChar* Player = Cast<APlayerChar>(Pawn);
		if (Player)
		{
			if (!Player->HasRemote)
				return;
			for (int i = 0; i < Player->PlacedBombs.Num(); i++)
			{
				if (Player->PlacedBombs[i])
				{
					Player->PlacedBombs[i]->Detonate();
					i--;
				}
			}
		}
	}
}