// TestObject.h

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TestObject.generated.h"

UCLASS()
class TEMPORARY_API UTestObject : public UObject
{
	GENERATED_BODY()
	
	UTestObject();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 TestValue;
};
