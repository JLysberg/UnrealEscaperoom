// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
	GetLineTraceHit();
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Grab released"));
}

void UGrabber::FindPhysicsHandleComponent()
{
	///Look for attached Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {
		///Physics Handle is found
		UE_LOG(LogTemp, Warning, TEXT("Physics handle component found on %s"), *GetOwner()->GetName());
	}
	else {
		///Physics Handle is not found
		UE_LOG(LogTemp, Error, TEXT("Physics handle component not found on %s"), *GetOwner()->GetName());
	}
}

void UGrabber::FindInputComponent()
{
	///Look for attached Input component
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		///Input Component is found
		UE_LOG(LogTemp, Warning, TEXT("Input component found on %s"), *GetOwner()->GetName());

		///Bind input axis
		InputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabber::Release);
	}
	else {
		///Input Component is not found
		UE_LOG(LogTemp, Error, TEXT("Input component not found on %s"), *GetOwner()->GetName());
	}
}

void UGrabber::DebugLine()
{
	///Update player location and rotation
	FVector Location;
	FRotator Rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT Location, OUT Rotation);
	FVector LineTraceEnd = Location + Rotation.Vector() * Reach;
	
	DrawDebugLine(GetWorld(), Location, LineTraceEnd, FColor(255, 0, 0)/*, false, 0.f, 0.f, 10.f*/);
}

FHitResult UGrabber::GetLineTraceHit() const
{
	///Update player location and rotation
	FVector Location;
	FRotator Rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT Location, OUT Rotation);
	FVector LineTraceEnd = Location + Rotation.Vector() * Reach;

	///Line trace (AKA ray-cast) to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		Location,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);

	///Log trace hit to output
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Actor hit: %s"), *ActorHit->GetName());
	}

	return FHitResult();
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();
	FindInputComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DebugLine();
}

