// Copyright Epic Games, Inc. All Rights Reserved.

#include "BattleRoyaleProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "BattleRoyaleCharacter.h"
#include "BattleRoyaleGameMode.h"
#include "BattleRoyalePlayerController.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BRPlayerState.h"

ABattleRoyaleProjectile::ABattleRoyaleProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ABattleRoyaleProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;

	bReplicates = true;
	SetReplicateMovement(true);
}

void ABattleRoyaleProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UParticleSystemComponent* ExplosionParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleAsset, Hit.ImpactPoint);

	// Only add impulse if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
	}

	if (!HasAuthority()) {	//Causes listen server issues haha
		ABattleRoyalePlayerController* KillerController = Cast<ABattleRoyalePlayerController>(GetOwner());
		if (IsValid(KillerController) && KillerController->IsLocalPlayerController())
			KillerController->ServerDestroyProjectile(this);
		return;
	}

	ABattleRoyaleCharacter* HitCharacter = Cast<ABattleRoyaleCharacter>(OtherActor);
	if (!IsValid(HitCharacter))
		return;

	ABattleRoyaleGameMode* GameMode = Cast<ABattleRoyaleGameMode>(GetWorld()->GetAuthGameMode());
	if (!IsValid(GameMode))
		return;

	ABattleRoyalePlayerController* KillerController = Cast<ABattleRoyalePlayerController>(GetOwner());
	if (!IsValid(KillerController))
		return;
	ABattleRoyaleCharacter* KillerCharacter = Cast<ABattleRoyaleCharacter>(KillerController->GetCharacter());
	if (!IsValid(KillerCharacter))
		return;

	ABRPlayerState* PlayerState = Cast<ABRPlayerState>(HitCharacter->GetPlayerState());
	PlayerState->Health = PlayerState->Health - 30.f;

	if (PlayerState->Health < 0.f) {
	HitCharacter->Killer = KillerCharacter;
	HitCharacter->OnRep_Killer();
	GameMode->PlayerDied(HitCharacter, KillerCharacter);
	}
}
