// Copyright Epic Games, Inc. All Rights Reserved.


#include "BattleRoyalePlayerController.h"
#include "EnhancedInputSubsystems.h"

void ABattleRoyalePlayerController::ServerSpawnProjectile_Implementation(TSubclassOf<class ABattleRoyaleProjectile> ProjectileClass, FVector SpawnLocation_, FRotator SpawnRotation) {
	UWorld* const World = GetWorld();
	if (World != nullptr) {
		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		ActorSpawnParams.Owner = PlayerController;

		World->SpawnActor<ABattleRoyaleProjectile>(ProjectileClass, SpawnLocation_, SpawnRotation, ActorSpawnParams);
	}
}

void ABattleRoyalePlayerController::ServerDestroyProjectile_Implementation(ABattleRoyaleProjectile* Projectile) {
	Projectile->SetLifeSpan(0.1f);
}

void ABattleRoyalePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);

		UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	}
}