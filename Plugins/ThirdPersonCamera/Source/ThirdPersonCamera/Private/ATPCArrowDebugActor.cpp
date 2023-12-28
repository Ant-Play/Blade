// Fill out your copyright notice in the Description page of Project Settings.


#include "ATPCArrowDebugActor.h"

#include "Components/ArrowComponent.h"

// Sets default values
AATPCArrowDebugActor::AATPCArrowDebugActor()
{
	SceneRootComponent = CreateDefaultSubobject<USceneComponent>("SceneRootComponent");
	SetRootComponent(SceneRootComponent);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>("ArrowComponent");
	ArrowComponent->SetupAttachment(SceneRootComponent);
	ArrowComponent->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	ArrowComponent->SetRelativeScale3D(FVector(1.f, 2.f, 2.f));
	ArrowComponent->ArrowSize = 1.5f;


#if !UE_BUILD_SHIPPING
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
#endif

}

// Called every frame
void AATPCArrowDebugActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float animDistance = 60.0f;
	const float animTime = 1.f;

	CurrentArrowAnimTime += DeltaTime * CurrentArrowAnimTimeSign;

	if (CurrentArrowAnimTime > animTime)
	{
		CurrentArrowAnimTimeSign = -1.f;
	}
	else if (CurrentArrowAnimTime < 0.f)
	{
		CurrentArrowAnimTimeSign = 1.f;
	}
	CurrentArrowAnimTime = FMath::Clamp(CurrentArrowAnimTime, 0.f, animTime);

	ArrowComponent->SetRelativeLocation(FVector(0.f, 0.f, FMath::Lerp(0.f, animDistance, CurrentArrowAnimTime / animTime)));

}

void AATPCArrowDebugActor::PickActor(AActor* Actor)
{
	if (Actor != nullptr)
	{
		FVector origin, boxExtent;
		Actor->GetActorBounds(true, origin, boxExtent);
		SetActorLocation(origin + FVector(0.f, 0.f, boxExtent.Z + 125.f));
	}

	ArrowComponent->SetHiddenInGame(Actor == nullptr);
}
