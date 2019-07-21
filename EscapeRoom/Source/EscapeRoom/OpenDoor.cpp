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
}

void UOpenDoor::OpenDoor()
{
	//Find the owning actor, door in this case
	AActor* Owner = GetOwner();

	//Find the actors rotator.
	FRotator Rotator = Owner->GetActorRotation();

	//Change rotator and owner attributes
	Rotator.Yaw = OpenAngle;
	Owner->SetActorRotation(Rotator);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Poll trigger volume every frame
	//If ActorThatOpens is in TriggerVolume, then OpenDoor()
	
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor();
	}


}

