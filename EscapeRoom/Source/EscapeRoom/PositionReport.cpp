// Fill out your copyright notice in the Description page of Project Settings.


#include "PositionReport.h"

#include "Classes/GameFramework/Actor.h"


// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	FString ObjectName = GetOwner()->GetName();

	FString ObjectPos = GetOwner()->GetActorLocation().ToString();
	/*
	FString ObjectPos = "X = ";
	FVector PosVector = GetOwner()->GetActorLocation();
	FString YPos = ", Y = ", ZPos = ", Z = ";
	ObjectPos.AppendInt(PosVector.X);
	ObjectPos.AppendChars(*YPos, 6);
	ObjectPos.AppendInt(PosVector.Y);
	ObjectPos.AppendChars(*ZPos, 6);
	ObjectPos.AppendInt(PosVector.Z);
	*/

	UE_LOG(LogTemp, Warning, TEXT("%s is at %s"), *ObjectName, *ObjectPos);
	
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

