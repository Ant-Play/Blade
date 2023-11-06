// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "mainCharacter.generated.h"

UCLASS()
class BLADE_API AmainCharacter : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = "MyPawn Component")
	class USkeletalMeshComponent* m_SkeletalMesh;

	UPROPERTY(VisibleAnywhere, Category = "MyPawn Component")
	class USpringArmComponent* m_SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "MyPawn Component")
	class UCameraComponent* m_Camera;

public:
	// Sets default values for this pawn's properties
	AmainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
