// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Equipment.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class BOTGAME_API AWeapon : public AEquipment
{
	GENERATED_BODY()
	
public:
	EAttackMethod AttackMethod = EAttackMethod::AttackOnSight;
	
private:
	// Attack Parameters
	// 
	float AttacksPerSecond = 0.f;

	float AttackCooldown = 0.f;

	// Measured in cm or Unreal units. 100 = 1 meter
	int AttackRange = 0.f;

	AEquipment* TargetedEquipment;

	float WeaponTurnRate = 0.0f;

	// Rotation is relative to bot rotation.
	FRotator WeaponRotation;

public:
	AWeapon();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void SetAttacksPerSecond(float Value) { if(Value > 0.f) {AttacksPerSecond = Value;} }

	UFUNCTION(BlueprintCallable, Category = "Attack")
	float GetAttacksPerSecond() const { return AttacksPerSecond;}

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void SetAttackCooldown(float Value) {if(Value > 0.f) {AttackCooldown = Value;}}

	UFUNCTION(BlueprintCallable, Category = "Attack")
	float GetAttackCooldown() const {return AttackCooldown;}

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void SetAttackRange(int Value) {if(Value > 0) {AttackRange = Value;} }

	UFUNCTION(BlueprintCallable, Category = "Attack")
	int GetAttackRange() const {return AttackRange; }

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void SetTargetedEquipment(AEquipment* Value) { if(Value && Value->GetIsDestroyed()) { TargetedEquipment = Value;} }

	UFUNCTION(BlueprintCallable, Category = "Attack")
	AEquipment* GetTargetedEquipment() const { return TargetedEquipment;}
};
