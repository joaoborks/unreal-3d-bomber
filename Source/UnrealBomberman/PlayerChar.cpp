// Created by Joao Borks [joao.borks@gmail.com] 2018

#include "PlayerChar.h"

// Sets default values
APlayerChar::APlayerChar()
{
}

FTransform& APlayerChar::GetSnappedPosition(FTransform Source) const
{
	FVector Location = Source.GetLocation();
	Location.X = GetSnappedValue(Location.X, 100.f);
	Location.Y = GetSnappedValue(Location.Y, 100.f);
	Source.SetLocation(Location);
	return Source;
}

float APlayerChar::GetSnappedValue(int Value, float Scale) const
{
	int Remains = Value % (int)Scale;
	return FMath::Abs(Remains) > Scale / 2 ? Value - Remains + (Value < 0 ? -Scale : Scale) : Value - Remains;
}