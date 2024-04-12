// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleRoyaleGameMode.generated.h"

UCLASS(minimalapi)
class ABattleRoyaleGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABattleRoyaleGameMode();


	UPROPERTY(Transient)
	TArray<class ABattleRoyalePlayerController*> AlivePlayers;

	virtual void PostLogin(APlayerController* JoinedPlayer) override;

	void PlayerDied(class ABattleRoyaleCharacter* Dead, class ABattleRoyaleCharacter* Killer);
	void WinnerFound(class ABattleRoyalePlayerController* Winner);
};
