// Fill out your copyright notice in the Description page of Project Settings.


#include "mainCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AmainCharacter::AmainCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	RootComponent = m_SkeletalMesh;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> m_StaticMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonShinbi/Characters/Heroes/Shinbi/Meshes/Shinbi.Shinbi'"));
	if (m_StaticMeshAsset.Succeeded())
	{
		m_SkeletalMesh->SetSkeletalMesh(m_StaticMeshAsset.Object);
	}
	//m_SkeletalMesh->AddRelativeLocation(FVector(0.0f, 0.0f, -83.0f));

	m_SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	m_SpringArm->SetupAttachment(m_SkeletalMesh);
	m_SpringArm->AddRelativeRotation(FRotator(-45.0f, 90.0f, 0.0f));
	m_SpringArm->TargetArmLength = 400.0f;
	m_SpringArm->bEnableCameraLag = true;
	m_SpringArm->CameraLagSpeed = 3.0f;

	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_Camera->SetupAttachment(m_SpringArm);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	bUseControllerRotationYaw = true;

	m_MaxSpeed = 100.0f;

	m_MoveVelocity = FVector(0.0f);

}

// Called when the game starts or when spawned
void AmainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AmainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(m_MoveVelocity * DeltaTime, true);
	AddControllerYawInput(m_MoveInput.X);

	FRotator newSpringArmRotation = m_SpringArm->GetComponentRotation();
	newSpringArmRotation.Pitch = FMath::Clamp(newSpringArmRotation.Pitch + m_MoveInput.Y, -80.0f, -15.0f);
	m_SpringArm->SetWorldRotation(newSpringArmRotation);
}

// Called to bind functionality to input
void AmainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AmainCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AmainCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AmainCharacter::LookRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AmainCharacter::LookUp);

}

void AmainCharacter::MoveForward(float AxisValue)
{
	m_MoveVelocity.Y = FMath::Clamp(AxisValue * m_MaxSpeed, -100.0f, 100.0f);
}

void AmainCharacter::MoveRight(float AxisValue)
{
	m_MoveVelocity.X = FMath::Clamp(AxisValue * m_MaxSpeed, -100.0f, 100.0f);
}

void AmainCharacter::LookRight(float AxisValue)
{
	m_MoveInput.X = FMath::Clamp(AxisValue, -1.0f, 1.0f);
}

void AmainCharacter::LookUp(float AxisValue)
{
	m_MoveInput.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f);
}

