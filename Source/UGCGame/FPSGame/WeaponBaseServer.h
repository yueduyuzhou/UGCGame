// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Common/FPSGameType.h"
#include "WeaponBaseServer.generated.h"

class USkeletalMeshComponent;
class USphereComponent;
class AWeaponBaseClient;
class UParticleSystem;

UCLASS()
class UGCGAME_API AWeaponBaseServer : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere)
		USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere)
		EWeaponType WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AWeaponBaseClient> ClientWeaponClass;

	UPROPERTY(EditAnywhere)
		UParticleSystem* ServerWeaponMuzzleFlash;

	UPROPERTY(EditAnywhere)
		USoundBase* ServerWeaponFireSound;

	UPROPERTY(EditAnywhere)
		UAnimMontage* ClientBodyFireMontage;

	UPROPERTY(EditAnywhere)
		UAnimMontage* ClientBodyReloadMontage;

	UPROPERTY(EditAnywhere)
		float BulletDistance;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* BulletHoleDecal;

	UPROPERTY(EditAnywhere)
		float BaseDamage;

	UPROPERTY(EditAnywhere)
		UCurveFloat* WeaponVerticalRecoilCurve;

	UPROPERTY(EditAnywhere)
		UCurveFloat* WeaponHorizontalRecoilCurve;

	UPROPERTY(EditAnywhere, Category = "Psitol Weapon Data")
		float PsitolRecoilRate;

public:	
	AWeaponBaseServer();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:

	/*武器重叠时自动附加到Character*/
	UFUNCTION()
	void OnAttackerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/*装备武器时处理*/
	UFUNCTION()
	void EquipWeapon();

	/*解除武器绑定*/
	//void DetachWeapon();

	/*抛出武器*/
	void ThrowWeapon(FVector InForwardDirection);

	/*弹药填充*/
	void ReloadAmmo();
	

public:
	UFUNCTION(NetMulticast, unreliable)
		void MulticastFireEffect();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE const int32& GetCurrentClipAmmo() { return CurrentClipAmmo; }
	FORCEINLINE const int32& GetCurrentAmmo() { return CurrentAmmo; }
	FORCEINLINE const int32& GetMaxClipAmmo() { return MaxClipAmmo; }
	FORCEINLINE void ExpendAmmo() { CurrentClipAmmo--; }

	FORCEINLINE const float& GetAutomaticFireRate() { return AutomaticFireRate; }
	FORCEINLINE const float& GetMoveingFireRandomRange() { return MoveingFireRandomRange; }
	FORCEINLINE bool IsAutomaticWeapon() { return IsAutomatic; }
	FORCEINLINE const float& GetResetRecoilFrequency() { return ResetRecoilFrequency; }

	/*Callback function for when ReplicatedUsing var is updated*/
	UFUNCTION()
		void OnRep_ReplicatedLocation();

	UFUNCTION()
		void OnRep_ReplicatedRotation();

private:
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_ReplicatedLocation)
		FVector ReplicatedLocation;

	UPROPERTY(Replicated, ReplicatedUsing = OnRep_ReplicatedRotation)
		FRotator ReplicatedRotation;

	UPROPERTY(EditAnywhere)
		int32 CurrentAmmo;	//当前的弹药量

	UPROPERTY(EditAnywhere, Replicated)
		int32 CurrentClipAmmo;	//当前弹夹的弹药量

	UPROPERTY(EditAnywhere)
		int32 MaxClipAmmo;	//弹夹最大弹药量

	UPROPERTY(EditAnywhere)
		bool IsAutomatic;

	UPROPERTY(EditAnywhere)
		float AutomaticFireRate;

	UPROPERTY(EditAnywhere)
		float MoveingFireRandomRange;

	UPROPERTY(EditAnywhere, Category = "Psitol Weapon Data")
		float ResetRecoilFrequency;
};
