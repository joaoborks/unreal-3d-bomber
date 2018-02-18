// Created by Joao Borks [joao.borks@gmail.com] 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"
#include "Bomb.generated.h"

UCLASS()
class UNREALBOMBERMAN_API ABomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomb();

	UFUNCTION(BlueprintCallable)
	void Detonate();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "2.0", ClampMax = "10.0"))
	float BlastRange = 3.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UMaterialInstanceDynamic* DynamicMaterial;

	virtual void BeginPlay() override;

private:
	UBoxComponent* Box;

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};