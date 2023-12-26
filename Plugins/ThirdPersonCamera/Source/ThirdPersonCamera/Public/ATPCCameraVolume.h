// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "GameplayTagContainer.h"

#include "ATPCCameraVolume.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class THIRDPERSONCAMERA_API AATPCCameraVolume : public AVolume
{
	GENERATED_BODY()

public:
	AATPCCameraVolume(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FGameplayTag CameraModeTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bChangeCameraModeWithInterp = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (InlineEditConditionToggle))
	bool bCheckFilterActorClassWithCamera = false;
	//Exmp: Character or PlayerActor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bCheckFilterActorClassWithCamera"))
	TArray<TSubclassOf<AActor>> FilterActorClassesWithCamera;
protected:
	UFUNCTION()
	void OnVolumeBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnVolumeEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	virtual class UATPCCameraComponent* GetCameraFromActor(AActor* Actor);
};
