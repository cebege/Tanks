// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InFireRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	//review above

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);

}

void ATower::CheckFireCondition()
{
	if (InFireRange())
	{
		Fire(); // debug sphere for now
	}
}

bool ATower::InFireRange()
{
	if (Tank)
	{
		float DistanceBetween = FVector::Dist(Tank->GetActorLocation(), GetActorLocation());
		if (DistanceBetween <= FireRange)
		{
			return true;
		}
	}
	return false;
}
