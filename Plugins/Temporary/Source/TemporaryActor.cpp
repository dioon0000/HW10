// TemporaryActor.cpp


#include "TemporaryActor.h"
#include "Kismet/KismetSystemLibrary.h"

ATemporaryActor::ATemporaryActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATemporaryActor::BeginPlay()
{
	Super::BeginPlay();

	UKismetSystemLibrary::PrintString(this, TEXT("ATemporaryActor::BeginPlay()"));
}
