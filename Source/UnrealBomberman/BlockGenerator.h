// Created by Joao Borks [joao.borks@gmail.com] 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockGenerator.generated.h"

USTRUCT()
struct FVectorContainer
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FVector> PositionRow;
};

UCLASS()
class UNREALBOMBERMAN_API ABlockGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	ABlockGenerator();

	virtual void Tick(float DeltaSeconds) override;
	virtual bool ShouldTickIfViewportsOnly() const override;

protected:
	virtual void BeginPlay() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;

private:
	UPROPERTY(EditAnywhere)
	FVector InitSpawnPoint;
	UPROPERTY(EditAnywhere)
	FVector FinalSpawnPoint;
	UPROPERTY(EditAnywhere)
	TArray<FVector> IgnoredPoints;
	UPROPERTY(EditAnywhere)
	bool ShowDebugPoints = true;
	UPROPERTY(VisibleAnywhere)
	TArray<FVectorContainer> SpawnPoints;

	const FLinearColor ValidColor = FLinearColor(0.f, 0.f, .8f);
	const FLinearColor InvalidColor = FLinearColor(.8f, 0.f, 0.f);

	float CurrentTime;

	UFUNCTION(BlueprintCallable)
	void SpawnBlocks();
	void DrawDebugPoint(FVector &Center, const FLinearColor &Color);
	void CalculatePoints();
	bool AllowedSpawnPosition(FVector Position);
	int GetValidPositionsCount();
};