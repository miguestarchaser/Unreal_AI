// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT.generated.h"

/**
 * 
 */
UCLASS()
class AICPP_API UBTT : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTT();
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector PlayerKey;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	/*buscar al jugador*/
};
