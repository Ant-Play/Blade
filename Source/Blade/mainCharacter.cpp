// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
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
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 200.0f; // The camera follows at this distance behind the character
	SpringArmComponent->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	SpringArmComponent->SocketOffset = FVector(0, 65.0f, 25.0f);

	// Create a follow camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	CameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	//bIsCrouching = false;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	// Call the base class 
	Super::BeginPlay();
	
	//Add Input Mapping Context
	if (APlayerController* playerController = CastChecked<APlayerController>(GetController())) {
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer())) {
			subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//////////////////////////////////////////////////////////////////////////
// Input

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		enhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		enhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::Move);
		enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &AMainCharacter::SetRotationTrue);
		enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AMainCharacter::SetRotationFalse);
		enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Canceled, this, &AMainCharacter::SetRotationFalse);

		
		// Looking
		enhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainCharacter::Look);

		// Crouching
		//enhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AMainCharacter::Crouch);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this))
	}

}

void AMainCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D movementVector = Value.Get<FVector2D>();
	if (Controller != nullptr) {
		// find out which way is forward
		//const FRotator rotation = GetMesh()->GetComponentRotation();
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yawRotation(0, rotation.Yaw, 0);

		// get forward vector
		//const FVector forwardDirection = GetMesh()->GetForwardVector();
		const FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		//const FVector rightDirection = GetMesh()->GetRightVector();
		const FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

		// add movement
		AddMovementInput(forwardDirection, movementVector.Y);
		AddMovementInput(rightDirection, movementVector.X);
	}
	UE_LOG(LogTemp, Warning, TEXT("Move"))
}

void AMainCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D lookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr) {
		//SpringArmComponent->AddLocalRotation(FRotator(0, lookAxisVector.X, 0));
		//SpringArmComponent->AddLocalRotation(FRotator(lookAxisVector.Y, 0, 0));
		//SpringArmComponent->AddRelativeRotation(FRotator(lookAxisVector.Y, lookAxisVector.X, 0));
		AddControllerYawInput(lookAxisVector.X);
		AddControllerPitchInput(lookAxisVector.Y);
		//CameraComponent->AddLocalRotation(FRotator(lookAxisVector.Y, 0, 0));
		//CameraComponent->AddLocalRotation(FRotator(0, lookAxisVector.X, 0));
	}
	UE_LOG(LogTemp, Warning, TEXT("Look"))
}

void AMainCharacter::SetRotationTrue()
{
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
}

void AMainCharacter::SetRotationFalse()
{
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
}

//void AMainCharacter::Crouch(const FInputActionValue& Value)
//{
//	bIsCrouching = !bIsCrouching;
//}

