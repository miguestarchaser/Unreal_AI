// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCAIController.h"
#include "MyCharacter.h"
#include "NPC.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"


ANPCAIController::ANPCAIController(FObjectInitializer const& ObjectInitializer)
{
	SetupPerceptionSystem();
}

void ANPCAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (ANPC* const npc = Cast<ANPC>(InPawn))
	{
		if (UBehaviorTree* const tree = npc->GetBehaviorTree()) 
		{
			UBlackboardComponent* b;
			UseBlackboard(tree->BlackboardAsset, b);
			Blackboard = b;
			RunBehaviorTree(tree);
		}
	}
}

//AI PERCEPTION
void ANPCAIController::SetupPerceptionSystem()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (SightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
		SightConfig->SightRadius = 500.f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.f;
		SightConfig->PeripheralVisionAngleDegrees = 90.f;
		SightConfig->SetMaxAge(5.f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ANPCAIController::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
		
	}
}

void ANPCAIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	if (auto* const ch = Cast<AMyCharacter>(Actor))
	{
		GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", Stimulus.WasSuccessfullySensed());
	}
}