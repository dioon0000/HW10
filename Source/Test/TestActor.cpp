// TestActor.cpp


#include "TestActor.h"
#include "Kismet/KismetSystemLibrary.h"

ATestActor::ATestActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();

	UKismetSystemLibrary::PrintString(this, TEXT("ATestActor::BeginPlay()"));
}
