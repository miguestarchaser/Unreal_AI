// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT.h"
#include "Kismet/GameplayStatics.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"


UBTT::UBTT()
{
	NodeName = "Find Player";
}


EBTNodeResult::Type UBTT::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		auto Blackboard = OwnerComp.GetBlackboardComponent();
		Blackboard->SetValueAsObject(PlayerKey.SelectedKeyName, Player);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

