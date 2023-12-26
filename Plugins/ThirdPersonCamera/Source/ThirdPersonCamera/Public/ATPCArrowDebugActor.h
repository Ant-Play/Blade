// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ATPCArrowDebugActor.generated.h"

UCLASS()
class THIRDPERSONCAMERA_API AATPCArrowDebugActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AATPCArrowDebugActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "ATPC")
	void PickActor(AActor* Actor);
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	class USceneComponent* SceneRootComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	class UArrowComponent* ArrowComponent;
private:
	float CurrentArrowAnimTime = 0.f;
	float CurrentArrowAnimTimeSign = 1.f;
};
