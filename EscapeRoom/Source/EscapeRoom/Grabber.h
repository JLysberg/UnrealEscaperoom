// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/GameFramework/PlayerController.h"
#include "Classes/GameFramework/Actor.h"
#include "Classes/PhysicsEngine/PhysicsHandleComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//Player reach in cm
	float Reach = 100.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	// Ray-cast and grab/release what's in reach
	void Grab();
	void Release();

	//look for attached physics handle component and assign to variable
	void FindPhysicsHandleComponent();

	//Look for attached input component, assign to variable and bind keys
	void FindInputComponent();

	//Draw debug line
	void DebugLine();

	//Line Trace and return first physicsbody hit within reach
	FHitResult GetLineTraceHit() const;
};
