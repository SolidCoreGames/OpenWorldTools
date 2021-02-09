// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncActor.h"


// Sets default values
AAsyncActor::AAsyncActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
	OnContentReady.BindUObject(this, &AAsyncActor::OnContentLoadCallback);
}

// Called when the game starts or when spawned
void AAsyncActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAsyncActor::LoadAsync()
{
	UAssetManager& AssetMngr = UAssetManager::Get();

	FStreamableManager& StreamMngr = AssetMngr.GetStreamableManager();
	AssetHandle = StreamMngr.RequestAsyncLoad(MeshAssetPath.ToSoftObjectPath(), OnContentReady);

}

void AAsyncActor::OnContentLoadCallback()
{
	UStaticMesh* MeshToSetup = Cast< UStaticMesh>(AssetHandle.Get()->GetLoadedAsset());
	MeshComp->SetStaticMesh(MeshToSetup);
}

// Called every frame
void AAsyncActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

