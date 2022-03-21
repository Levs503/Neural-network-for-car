// Fill out your copyright notice in the Description page of Project Settings.


#include "MyNeuralNetworkSkyMonza.h"
#include<fstream>
#include<ctime>
#include<vector>
#include"MyMatrix.h"

UMyNeuralNetworkSkyMonza::UMyNeuralNetworkSkyMonza()
{
    std::string filename = "SkyMonza.txt";
    FString directory = FPaths::GameSourceDir();
    std::string directory2 = TCHAR_TO_UTF8(*directory);
    std::string myFile = directory2 + filename;
    std::ifstream from(myFile);
   // std::ifstream from("C:/Users/Лев/CLionProjects/NeuralNetwork/saving.txt");
    if (from) {
        from >> totalDistance;
        from >> inputNeural;
        from >> hiddenNeural;
        from >> outputNeural;
        from >> learningRate;
        InHidMatrix = matrix::MyMatrix<float>(hiddenNeural, inputNeural);
        HidOutMatrix = matrix::MyMatrix<float>(outputNeural, hiddenNeural);
        for (size_t a = 0; a < InHidMatrix.Rows(); a++) {
            for (size_t f = 0; f < InHidMatrix.Cols(); f++) {
                from >> InHidMatrix[a][f];
            }
        }
        for (size_t a = 0; a < HidOutMatrix.Rows(); a++) {
            for (size_t f = 0; f < HidOutMatrix.Cols(); f++) {
                from >> HidOutMatrix[a][f];
            }
        }
    }


    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}


UMyNeuralNetworkSkyMonza::~UMyNeuralNetworkSkyMonza() {}

void UMyNeuralNetworkSkyMonza::sigmoid(matrix::MyMatrix<float>& a) {
    for (size_t g = 0; g < a.Rows(); g++) {
        for (size_t f = 0; f < a.Cols(); f++) {
            float qwer = 1 + exp(-a[g][f]);
            a[g][f] = 1 / qwer;
        }
    }
}


// Called when the game starts
void UMyNeuralNetworkSkyMonza::BeginPlay()
{
    Super::BeginPlay();

    // ...

}


matrix::MyMatrix<float>& UMyNeuralNetworkSkyMonza::Query(matrix::MyMatrix<float>& input) {
    hiddenInputOutput = InHidMatrix * input;
    sigmoid(hiddenInputOutput);
    finalInputOutput = HidOutMatrix * hiddenInputOutput;
    sigmoid(finalInputOutput);
    return finalInputOutput;
}

// Called every frame
void UMyNeuralNetworkSkyMonza::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}


FVector4 UMyNeuralNetworkSkyMonza::Query111(float forward, float rightdown, float rightup1, float rightup2, float leftup2, float leftup1, float leftdown, float newRight, float newLeft, float speed, float angle) {

    matrix::MyMatrix <float> inputs(11, 1);
    inputs[0][0] = forward;
    inputs[1][0] = rightdown;
    inputs[2][0] = rightup1;
    inputs[3][0] = rightup2;
    inputs[4][0] = leftup2;
    inputs[5][0] = leftup1;
    inputs[6][0] = leftdown;
    inputs[7][0] = newRight;
    inputs[8][0] = newLeft;
    inputs[9][0] = speed;
    if (angle < -1.2 || angle > 1.2) {
        if (angle < 5 && angle > -5)
        {
            if (angle < -2 && angle > -4) {
                inputs[10][0] = angle + 3.1415;
            }
            else {
                if (angle > 2 && angle < 4) {
                    inputs[10][0] = angle - 3.1415;
                }
                else inputs[10][0] = 0;
            }
        }
        else {
            if (angle < -4 && angle > -7) {
                inputs[10][0] = angle + 6.283;
            }
            else {
                if (angle > 4 && angle < 7) {
                    inputs[10][0] = angle - 6.283;
                }
                else inputs[10][0] = 0;
            }
        }

    }
    else {
        inputs[10][0] = angle;
    }
    matrix::MyMatrix<float> output = Query(inputs);
    FVector4 ret;
    ret.X = output[0][0];
    ret.Y = output[1][0];
    return ret;
}

