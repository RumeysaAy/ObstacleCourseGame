// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	FString Name = GetName();
	// ne tür bir günlük kategorisi, günlüğün seviyesi - ne kadar acil olduğu, yazdırılan metin,
	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"), *Name); // string
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

// AMovingPlatform sınıfı içinden MovePlatform fonksiyonunu tanımladım
void AMovingPlatform::MovePlatform(float DeltaTime)
{
	// ## çok ileri giderse platformu geri gönder ##

	// çok ileri giderseniz hareket yönünü tersine çevirin
	if (ShouldPlatformReturn())
	{
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MoveDistance;

		SetActorLocation(StartLocation);

		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
		// ## platformu ileri doğru hareket ettir ##
		// mevcut konumu al
		FVector CurrentLocation = GetActorLocation();
		// bu konuma vektör ekleyin
		CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime); // şu anki konumuna 100, 0, 0 ekler ve ileri doğru ilerler
		// konumu ayarlayın
		SetActorLocation(CurrentLocation); // şu anki konumu
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	// DistanceMoved = GetDistanceMoved(); // ne kadar ilerlendi
	return GetDistanceMoved() > MoveDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	// ne kadar ilerlediğimizi kontrol et
	// FVector::Dist(StartLocation, GetActorLocation() + (PlatformVelocity * DeltaTime))
	return FVector::Dist(StartLocation, GetActorLocation());
}
