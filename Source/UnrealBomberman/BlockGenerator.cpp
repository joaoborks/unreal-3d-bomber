// Created by Joao Borks [joao.borks@gmail.com] 2018

#include "BlockGenerator.h"
#include "BlockBreakable.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
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
	ShowDebugPoints = false;
	SpawnBlocks();
}

void ABlockGenerator::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (ShowDebugPoints)
	{
		DrawDebugPoint(InitSpawnPoint, InvalidColor);
		DrawDebugPoint(FinalSpawnPoint, InvalidColor);
		for (auto& Point : SpawnPoints)
			DrawDebugPoint(Point, ValidColor);				
		for (auto& Point : IgnoredPoints)
			DrawDebugPoint(Point, InvalidColor);
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

// Calculates the possible spawn points on the level
void ABlockGenerator::CalculatePoints()
{
	if (FVector::Distance(InitSpawnPoint, FinalSpawnPoint) == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Distance between spawnpoints is not enough to calculate points"));
		return;
	}
	if (SpawnPoints.Num() > 0)
		SpawnPoints.Empty();

	// Temporarily predefined
	float Scale = 100.f;
	int SizeX = (FMath::Abs(InitSpawnPoint.X) + FMath::Abs(FinalSpawnPoint.X) + Scale) / Scale;
	int SizeY = (FMath::Abs(InitSpawnPoint.Y) + FMath::Abs(FinalSpawnPoint.Y) + Scale) / Scale;
	FVector* TempPosition;
	for (int y = 0; y < SizeY; y++)
	{
		for (int x = 0; x < SizeX; x++)
		{
			// Row/Column Restrictions
			if ((y % 2 == 0) || (x % 2 == 0))
			{
				TempPosition = new FVector(InitSpawnPoint.X - x * Scale, InitSpawnPoint.Y + y * Scale, InitSpawnPoint.Z);
				// Position Restrictions
				if (AllowedSpawnPosition(*TempPosition))
					SpawnPoints.Emplace(*TempPosition);
			}
		}
	}
}

// Spawns the blocks at the free spaces
void ABlockGenerator::SpawnBlocks()
{
	if (!BlockBreakableBP)
	{
		UE_LOG(LogTemp, Error, TEXT("Block Blueprint was not assigned!"));
		return;
	}
	int BlocksToSpawn = GetValidPositionsCount() * BlockIntensity;
	int Index;
	for (int i = 0; i < BlocksToSpawn; i++)
	{
		Index = FMath::RandRange(0, SpawnPoints.Num() - 1);
		GetWorld()->SpawnActor<ABlockBreakable>(BlockBreakableBP, SpawnPoints[Index], FRotator::ZeroRotator);
		SpawnPoints.RemoveAt(Index);
	}
}

// Returns whether the given position is valid
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

// Gets the total number of valid positions
int ABlockGenerator::GetValidPositionsCount()
{
	return SpawnPoints.Num();
}