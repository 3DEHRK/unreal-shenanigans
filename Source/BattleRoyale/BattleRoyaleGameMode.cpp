// Copyright Epic Games, Inc. All Rights Reserved.

#include "BattleRoyaleGameMode.h"
#include "BattleRoyaleCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "BattleRoyalePlayerController.h"
#include "BRPlayerState.h"
#include "BRGameState.h"

ABattleRoyaleGameMode::ABattleRoyaleGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

void ABattleRoyaleGameMode::PostLogin(APlayerController* JoinedPlayer) {
	Super::PostLogin(JoinedPlayer);
	AlivePlayers.Add(Cast<ABattleRoyalePlayerController>(JoinedPlayer));
}

void ABattleRoyaleGameMode::PlayerDied(ABattleRoyaleCharacter* Dead, ABattleRoyaleCharacter* Killer) {
	if (!IsValid(Killer))
		return;

	ABattleRoyalePlayerController* DeadController = Cast<ABattleRoyalePlayerController>(Dead->GetController());
	if (IsValid(DeadController))
		AlivePlayers.RemoveSingle(DeadController);

	if (AlivePlayers.Num() == 1 && AlivePlayers.IsValidIndex(0))
		WinnerFound(Cast<ABattleRoyalePlayerController>(AlivePlayers[0]));
}

void ABattleRoyaleGameMode::WinnerFound(class ABattleRoyalePlayerController* Winner) {
	ABRPlayerState* PlayerState = Cast<ABRPlayerState>(Winner->PlayerState);
	if (!IsValid(PlayerState))
		return;

	ABRGameState* GameState_ = GetGameState<ABRGameState>();
	if (IsValid(GameState_))
		GameState_->Winner = PlayerState;
}
