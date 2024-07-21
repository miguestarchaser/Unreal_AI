// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "NPCAIController.generated.h"

/**
 * 
 */
UCLASS()
class AICPP_API ANPCAIController : public AAIController
{
	GENERATED_BODY()
public:
	explicit ANPCAIController(FObjectInitializer const& ObjectInitializer);

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	class UAISenseConfig_Sight* SightConfig;
	//class UAIPerceptionStimuliSourceComponent* StimulusSource;

	void SetupPerceptionSystem();

	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus);
};
