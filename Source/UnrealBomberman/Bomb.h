// Created by Joao Borks [joao.borks@gmail.com] 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"
#include "BombDestroyable.h"
#include "Bomb.generated.h"

UCLASS()
class UNREALBOMBERMAN_API ABomb : public AActor, public IBombDestroyable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomb();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1.0", ClampMax = "10.0"))
	float BlastRange = 1.f;

	UFUNCTION(BlueprintCallable, Category = "Bomb Blast")
	void Detonate();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Bomb Blast")
	// Event called by the bomb when it blows and hits an object
	void OnBombBlastHit();
	// Event called by the bomb when it blows and hits an object
	virtual void OnBombBlastHit_Implementation() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UClass* BlastFxBP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UMaterialInstanceDynamic* DynamicMaterial;

	virtual void BeginPlay() override;

private:
	UBoxComponent* Box;

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SpawnBlast(FVector Direction);
	FVector LineTraceDirection(FVector Direction) const;
	FVector GetCenterLocation() const;
};