// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ATPCLockOnTargetLocComponent.generated.h"


UCLASS(Blueprintable, Category = "ATPC", meta = (BlueprintSpawnableComponent))
class THIRDPERSONCAMERA_API UATPCLockOnTargetLocComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintPure, Category = "ATPC")
	virtual FVector GetTargetLocation();
		
};
