// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPCAIController.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(FObjectInitializer const& ObjectInitializer) 
{
	NodeName = "Find Random Location In NavMesh";
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//get Ai Controller and its NPC
	if (auto* const  cont = Cast<ANPCAIController>(OwnerComp.GetAIOwner()))
	{
		if (auto* const npc = cont->GetPawn()) 
		{
			//Obtain NPC LOCATION to use as origin
			auto const Origin  = npc->GetActorLocation();

			//get the navigation system and generate a random location
			if (auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation Loc;
				if (NavSys->GetRandomPointInNavigableRadius(Origin, SearchRadius, Loc)) 
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),Loc.Location);
				}

				// finish with success
				FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	//return Super::ExecuteTask(OwnerComp,NodeMemory);
	return EBTNodeResult::Failed;
}