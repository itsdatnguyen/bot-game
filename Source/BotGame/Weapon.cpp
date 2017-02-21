// Fill out your copyright notice in the Description page of Project Settings.

#include "BotGame.h"
#include "Weapon.h"

AWeapon::AWeapon()
{

}

void AWeapon::BeginPlay()
{

}

void AWeapon::Tick(float DeltaSeconds)
{
	switch (AttackMethod) {
	case EAttackMethod::AttackOnlyTarget:
		break;


	}
}
