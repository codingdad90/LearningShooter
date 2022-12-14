// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AShooterCharacter::AShooterCharacter() :
	BaseLookUpRate(45.f),
	BaseTurnRate(45.f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create a camera boom(pulls in towards character if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.f; //Camera follows behind the character at this distance
	CameraBoom->bUsePawnControlRotation = true; //Rotate the arm based on the controller
	
	//Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); //attach camera to end of boom
	FollowCamera->bUsePawnControlRotation = false; //Camera does not rotate relative to arm


}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();






	//FOR REFERENCE: USING UE_LOG TO DISPLAY INFORMATION IN THE LOG
	//UE_LOG(LogTemp, Warning, TEXT("BeginPlay() Called again!"));

	//int myInt{ 42 };
	//UE_LOG(LogTemp, Warning, TEXT("int MyInt: %d"), myInt);

	//float myFloat{ 3.14159f };
	//UE_LOG(LogTemp, Warning, TEXT("float MyFloat: %f"), myFloat);

	//double myDouble{ 0.000756 };
	//UE_LOG(LogTemp, Warning, TEXT("double myDouble: %lf"), myDouble);

	//char myChar{ 'J' };
	//UE_LOG(LogTemp, Warning, TEXT("char myChar: %c"), myChar);

	//wchar_t wideChar{ L'J' };
	//UE_LOG(LogTemp, Warning, TEXT("wchar_t wideChar: %lc"), wideChar);

	//bool myBool{ true };
	//UE_LOG(LogTemp, Warning, TEXT("bool myBool: %d"), myBool);

	//UE_LOG(LogTemp, Warning, TEXT("int MyInt: %d, float MyFloat: %f, bool myBool: %d"), myInt, myFloat, myBool);

	//FString myString{ TEXT("My String!!") };
	//UE_LOG(LogTemp, Warning, TEXT("FString myString: %s"), *myString);

	//UE_LOG(LogTemp, Warning, TEXT("FString myString: %s"), *GetName());
	

}

void AShooterCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		//find which way is forward
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0, Rotation.Yaw, 0 };
		
		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::X) };
		AddMovementInput(Direction, Value);
	}
}

void AShooterCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		//find which way is forward
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0, Rotation.Yaw, 0 };

		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::Y) };
		AddMovementInput(Direction, Value);
	}
}

void AShooterCharacter::TurnAtRate(float Rate)
{
	//calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds()); // deg/sec *sec/frame
}

void AShooterCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnRate", this, &AShooterCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AShooterCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);


}





