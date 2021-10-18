// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"

AWall::AWall()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AWall::BeginPlay()
{
	Super::BeginPlay();
}

void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
