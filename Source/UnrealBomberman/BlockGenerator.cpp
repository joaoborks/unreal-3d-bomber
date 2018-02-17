// Created by Joao Borks [joao.borks@gmail.com] 2018

#include "BlockGenerator.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "Color.h"

ABlockGenerator::ABlockGenerator()
{
	PrimaryActorTick.bCanEverTick = WITH_EDITOR;
}

void ABlockGenerator::BeginPlay()
{
	Super::BeginPlay();
}

void ABlockGenerator::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (ShowDebugPoints)
	{
		DrawDebugPoint(InitSpawnPoint, InvalidColor);
		DrawDebugPoint(FinalSpawnPoint, InvalidColor);
		for (auto& Container : SpawnPoints)
			for (auto& Point : Container.PositionRow)
				DrawDebugPoint(Point, ValidColor);				
		for (auto& IgnorePoint : IgnoredPoints)
			DrawDebugPoint(IgnorePoint, InvalidColor);
	}
}

void ABlockGenerator::PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent)
{
	CalculatePoints();
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void ABlockGenerator::DrawDebugPoint(FVector &Center, const FLinearColor &Color)
{
	UKismetSystemLibrary::DrawDebugPoint(GetWorld(), Center, 20.f, Color);
}

void ABlockGenerator::CalculatePoints()
{
	if (FVector::Distance(InitSpawnPoint, FinalSpawnPoint) == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Distance between spawnpoints is not enough to calculate points"));
		return;
	}
	if (SpawnPoints.Num() > 0)
	{
		for (auto& container : SpawnPoints)
			container.PositionRow.Empty();
		SpawnPoints.Empty();
	}
	// Temporarily predefined
	float Scale = 100.f;
	int SizeX = (FMath::Abs(InitSpawnPoint.X) + FMath::Abs(FinalSpawnPoint.X) + Scale) / Scale;
	int SizeY = (FMath::Abs(InitSpawnPoint.Y) + FMath::Abs(FinalSpawnPoint.Y) + Scale) / Scale;
	FVectorContainer* Temp = nullptr;
	FVector* TempPosition;
	for (int y = 0; y < SizeY; y++)
	{
		Temp = new FVectorContainer();
		for (int x = 0; x < SizeX; x++)
		{
			// Row/Column Restrictions
			if ((y % 2 == 0) || (x % 2 == 0))
			{
				TempPosition = new FVector(InitSpawnPoint.X - x * Scale, InitSpawnPoint.Y + y * Scale, InitSpawnPoint.Z);
				// Position Restrictions
				if (AllowedSpawnPosition(*TempPosition))
					Temp->PositionRow.Add(*TempPosition);
			}
		}
		SpawnPoints.Emplace(*Temp);
	}
}

void ABlockGenerator::SpawnBlocks()
{
	UE_LOG(LogTemp, Display, TEXT("Should spawn %d blocks"), GetValidPositionsCount());
}

bool ABlockGenerator::AllowedSpawnPosition(FVector Position)
{
	// Restrict Init and Final Points
	if (Position == InitSpawnPoint || Position == FinalSpawnPoint)
		return false;
	// Restrict Ignored Points
	if (IgnoredPoints.Contains(Position))
		return false;

	return true;
}

bool ABlockGenerator::ShouldTickIfViewportsOnly() const
{
	return WITH_EDITOR;
}

int ABlockGenerator::GetValidPositionsCount()
{
	int Temp = 0;
	for (auto& Container : SpawnPoints)
		Temp += Container.PositionRow.Num();
	return Temp;
}