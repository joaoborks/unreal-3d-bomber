// Created by Joao Borks [joao.borks@gmail.com] 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockGenerator.generated.h"

UCLASS()
// Handles breakable blocks generation at runtime
class UNREALBOMBERMAN_API ABlockGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	ABlockGenerator();

	virtual void Tick(float DeltaSeconds) override;
	virtual bool ShouldTickIfViewportsOnly() const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Block Generation|Debug")
    // Should the points be visible on the viewport?
	bool ShowDebugPoints = true;

	virtual void BeginPlay() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;

private:
	UPROPERTY(EditAnywhere, Category = "Block Generation")
	// The block blueprint
	UClass* BlockBreakableBP;
	UPROPERTY(EditAnywhere, Category = "Block Generation", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	// How much of the free space should the blocks fill from 0 to 1
	float BlockIntensity = .7f;
	UPROPERTY(EditAnywhere, Category = "Block Generation|Settings")
	FVector InitSpawnPoint = *new FVector(700.f, -700.f, 0);
	UPROPERTY(EditAnywhere, Category = "Block Generation|Settings")
	FVector FinalSpawnPoint = *new FVector(-700.f, 700.f, 0);
	UPROPERTY(EditAnywhere, Category = "Block Generation|Settings")
	// Points where the blocks will not spawn
	TArray<FVector> IgnoredPoints;
	UPROPERTY(VisibleAnywhere, Category = "Block Generation|Debug")
	// Calculated spawn points
	TArray<FVector> SpawnPoints;

	// Color for valid spawn points
	const FLinearColor ValidColor = FLinearColor(0.f, 0.f, .8f);
	// Color for invalid spawn points
	const FLinearColor InvalidColor = FLinearColor(.8f, 0.f, 0.f);
	
	UFUNCTION(BlueprintCallable)
	// Spawns the blocks at the free spaces
	void SpawnBlocks();
	void DrawDebugPoint(FVector &Center, const FLinearColor &Color);
	// Calculates the possible spawn points on the level
	void CalculatePoints();
	// Returns whether the given position is valid
	bool AllowedSpawnPosition(FVector Position);
	// Gets the total number of valid positions
	int GetValidPositionsCount();
};