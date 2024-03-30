// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBox.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AMyBox::AMyBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ReplicatedVar = 100.f;
	bReplicates = true;
}

// Called when the game starts or when spawned
void AMyBox::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		GetWorld()->GetTimerManager().SetTimer(TestTimer, this, &AMyBox::MulticastRPCExplode, 2.f, false);
	}
}

// Called every frame
void AMyBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

}

void AMyBox::OnRep_ReplicatedVar()
{
	if (HasAuthority())
	{
		// GEngine->AddOnScreenDebugMessage(1, 15.f, FColor::Green, TEXT("Server: OnRep_ReplicatedVar"));

		FVector NewLocation = GetActorLocation() + FVector(0.f, 0.f, 200.f);
		SetActorLocation(NewLocation);
	}
	else
	{
		// GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("Client %d: OnRep_ReplicatedVar"), GPlayInEditorID));
	}

}

void AMyBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyBox, ReplicatedVar);
}

void AMyBox::DecreaseReplicatedVar()
{
	if (HasAuthority())
	{
		ReplicatedVar -= 1.f;
		OnRep_ReplicatedVar();
		if (ReplicatedVar > 0)
		{
			GetWorld()->GetTimerManager().SetTimer(TestTimer, this, &AMyBox::DecreaseReplicatedVar, 2.f, false);
		}
	}
}

void AMyBox::ClientRPCFunction_Implementation()
{
	if (SparksEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SparksEffect, GetActorLocation() + FVector(0.f, 0.f, 200.f));
	}
}

void AMyBox::MulticastRPCExplode_Implementation()
{
	if (HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, FString::Printf(TEXT("Server %d: MulticastRPCExplode_Implementation"), GPlayInEditorID));
		GetWorld()->GetTimerManager().SetTimer(TestTimer, this, &AMyBox::MulticastRPCExplode, 2.f, false);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(2, 3.f, FColor::Blue, FString::Printf(TEXT("Client %d: MulticastRPCExplode_Implementation"), GPlayInEditorID));
	}

	
	if (!IsRunningDedicatedServer())
	{
		FVector Location = GetActorLocation() + FVector(0.f, 0.f, 100.f);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, Location, FRotator::ZeroRotator, FVector(1), true, EPSCPoolMethod::AutoRelease);
	}
}

