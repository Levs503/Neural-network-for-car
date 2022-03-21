// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include"MyMatrix.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyNeuralNetworkSkySpa.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT1_API UMyNeuralNetworkSkySpa : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMyNeuralNetworkSkySpa();

	matrix::MyMatrix<float>& Query(matrix::MyMatrix<float>& target);

	UFUNCTION(BlueprintCallable)
		FVector4 Query111(float forward, float rightdown, float rightup1, float rightup2, float leftup2, float leftup1, float leftdown, float newRight, float newLeft, float speed, float angle);

	~UMyNeuralNetworkSkySpa();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float totalDistance;
	int inputNeural;
	int hiddenNeural;
	int outputNeural;
	float learningRate;
	matrix::MyMatrix<float> InHidMatrix;
	matrix::MyMatrix<float> HidOutMatrix;
	matrix::MyMatrix<float> hiddenInputOutput;
	matrix::MyMatrix<float> finalInputOutput;
	void sigmoid(matrix::MyMatrix<float>& a);
};
