// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BattleRoyaleProjectile.h"
#include "BattleRoyalePlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()
class BATTLEROYALE_API ABattleRoyalePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(Server, Reliable)
	void ServerSpawnProjectile(TSubclassOf<class ABattleRoyaleProjectile> ProjectileClass, FVector SpawnLocation_, FRotator SpawnRotation);

	UFUNCTION(Server, Unreliable)
	void ServerDestroyProjectile(class ABattleRoyaleProjectile* Projectile);

protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	// Begin Actor interface
protected:

	virtual void BeginPlay() override;

	// End Actor interface
};
