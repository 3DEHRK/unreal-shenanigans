// Fill out your copyright notice in the Description page of Project Settings.


#include "BRGameState.h"
#include "Net/UnrealNetwork.h"

void ABRGameState::OnRep_Winner() {
	OnWinnerFound.Broadcast();
}

void ABRGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABRGameState, Winner);
}
