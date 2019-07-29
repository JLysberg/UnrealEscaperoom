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


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber operational :)"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Update player location and rotation
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT Location, OUT Rotation);

	//Print location and rotation
	//UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *Location.ToString(), *Rotation.ToString());

	//Draw debug line
	FVector LineTraceEnd = Location + FVector(0.f, 0.f, 50.f);
	DrawDebugLine(GetWorld(), Location, LineTraceEnd, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);
}

