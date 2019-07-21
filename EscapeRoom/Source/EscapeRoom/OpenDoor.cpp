// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"

#include "Classes/GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	Owner = GetOwner();
}

void UOpenDoor::OpenDoor()
{
	//Change owner attributes
	Owner->SetActorRotation(FRotator(0.,OpenAngle,0.));
}

void UOpenDoor::CloseDoor()
{
	//Change owner attributes
	Owner->SetActorRotation(FRotator(0., CloseAngle, 0.));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Poll trigger volume every frame
	//If ActorThatOpens is in TriggerVolume, then OpenDoor()
	
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	float TimeSinceLastClose = GetWorld()->GetTimeSeconds() - LastDoorOpenTime;
	if (TimeSinceLastClose > DoorCloseDelay) {
		CloseDoor();
	}
}

