// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoKartMovementComponent.generated.h"

USTRUCT()
struct FGoKartMove
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		float Throttle;

	UPROPERTY()
		float SteeringThrow;

	UPROPERTY()
		float DeltaTime;

	UPROPERTY()
		float Time;

	bool IsValid() const 
	{
		return FMath::Abs(Throttle) <= 1 && FMath::Abs(SteeringThrow) <= 1;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KRAZYKARTS_API UGoKartMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGoKartMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetVelocity(FVector Val) { Velocity = Val; }
	FVector GetVelocity() { return Velocity; }

	void SetThrottle(float Val) { Throttle = Val; }
	//float GetThrottle() { return Throttle; }

	void SetSteeringThrow(float Val) { SteeringThrow = Val; }
	//float GetSteeringThrow() { return SteeringThrow; }

	void SimulateMove(const FGoKartMove& Move);

	FGoKartMove CreateMove(float DeltaTime);

	FGoKartMove GetLastMove() { return LastMove; }

private:
	FVector GetAirResistance();

	FVector GetRollingResistance();

	void ApplyRotation(float DeltaTime, float _SteeringThrow);

	void UpdateLocationFromVelocity(float DeltaTime);

	// The mass of the car (kg).
	UPROPERTY(EditAnywhere)
		float Mass = 1000; // 1��

	// ����Ʋ�� ������ ���������� ���� �������� ��? (���� N)
	UPROPERTY(EditAnywhere)
		float MaxDrivingForce = 10000;

	// ������ ���� ���¿��� �ڵ��� ȸ�� �ݰ��� �ּ� ������
	UPROPERTY(EditAnywhere)
		float MinTurningRadius = 10;

	// �������� �� ���� �׷� (kg/m)
	UPROPERTY(EditAnywhere)
		float DragCoefficient = 16;

	// ���� ����, �������� ŭ
	UPROPERTY(EditAnywhere)
		float RollingResistanceCoefficient = 0.015;

	FVector Velocity;
	float Throttle;
	float SteeringThrow;

	FGoKartMove LastMove;

};
