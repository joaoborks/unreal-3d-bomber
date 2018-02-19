// Created by Joao Borks [joao.borks@gmail.com] 2018

#include "PlayerChar.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Bomb.h"

// Sets default values
APlayerChar::APlayerChar()
{
}

void APlayerChar::SpawnBomb()
{
	int Limit = BombLimit;
	if (HasRemote)
		Limit = 1;
	if (PlacedBombs.Num() >= Limit)
		return;
	if (!BombBP)
	{
		UE_LOG(LogTemp, Error, TEXT("Bomb Blueprint is not assigned"));
		return;
	}
	FActorSpawnParameters Params = FActorSpawnParameters();
	Params.Owner = this;
	FVector Location = GetSnappedPosition(GetActorTransform()).GetLocation();
	Location.Z = 0;
	ABomb* Bomb = GetWorld()->SpawnActor<ABomb>(BombBP, Location, FRotator::ZeroRotator, Params);
	PlacedBombs.Add(Bomb);
	Bomb->BlastRange = BombRange;
}

void APlayerChar::OnBombBlastHit_Implementation()
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