// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterTest.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ThirdPersonCamera/Public/ATPCCameraComponent.h"

// Sets default values
AMainCharacterTest::AMainCharacterTest()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;				// Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);	// ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 400.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	TPCCameraComponent = CreateDefaultSubobject<UATPCCameraComponent>(TEXT("TPCCamera"));
	TPCCameraComponent->SetupAttachment(RootComponent);

	// Create a follow camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	CameraComponent->SetupAttachment(TPCCameraComponent);
	CameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AMainCharacterTest::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D movementVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yawRotation(0, rotation.Yaw, 0);
		
		// get forward vector
		const FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);

		// get right vector
		const FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

		// add movement
		AddMovementInput(forwardDirection, movementVector.Y);
		AddMovementInput(rightDirection, movementVector.X);
	}
}

void AMainCharacterTest::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D lookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(lookAxisVector.X);
		AddControllerPitchInput(lookAxisVector.Y);
	}
}

// Called when the game starts or when spawned
void AMainCharacterTest::BeginPlay()
{
	// Call the base class 
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* playerController = CastChecked<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
		{
			subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

// Called every frame
void AMainCharacterTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacterTest::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{

		// Jumping
		enhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &ACharacter::Jump);
		enhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		enhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMainCharacterTest::Move);
		
		// Looking
		enhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AMainCharacterTest::Look);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this))
	}
}

