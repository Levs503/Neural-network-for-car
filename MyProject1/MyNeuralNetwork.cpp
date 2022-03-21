// Fill out your copyright notice in the Description page of Project Settings.


#include "MyNeuralNetwork.h"
#include<fstream>
#include<ctime>
#include<vector>
#include"MyMatrix.h"


// Sets default values for this component's properties
UMyNeuralNetwork::UMyNeuralNetwork()
{
    std::ifstream from("C:/Users/���/CLionProjects/NeuralNetwork/saving.txt");
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


// Called when the game starts
void UMyNeuralNetwork::BeginPlay()
{
    Super::BeginPlay();

    // ...

}


// Called every frame
void UMyNeuralNetwork::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

UMyNeuralNetwork::UMyNeuralNetwork(int inputNeural, int hiddenNeural,
    int outputNeural, float learningRate)
    : inputNeural(inputNeural),
    hiddenNeural(hiddenNeural),
    outputNeural(outputNeural),
    InHidMatrix(hiddenNeural, inputNeural),
    HidOutMatrix(outputNeural, hiddenNeural),
    hiddenInputOutput(hiddenNeural, 1),
    finalInputOutput(outputNeural, 1),
    learningRate(learningRate)
{
    InHidMatrix.RandFromTo(-1, 1);
    HidOutMatrix.RandFromTo(-1, 1);
}


matrix::MyMatrix<float>& UMyNeuralNetwork::Query(matrix::MyMatrix<float>& input) {
    hiddenInputOutput = InHidMatrix * input;
    sigmoid(hiddenInputOutput);
    finalInputOutput = HidOutMatrix * hiddenInputOutput;
    sigmoid(finalInputOutput);
    return finalInputOutput;
}

void UMyNeuralNetwork::sigmoid(matrix::MyMatrix<float>& a) {
    for (size_t g = 0; g < a.Rows(); g++) {
        for (size_t f = 0; f < a.Cols(); f++) {
            float qwer = 1 + exp(-a[g][f]);
            a[g][f] = 1 / qwer;
        }
    }
}




void UMyNeuralNetwork::Train(matrix::MyMatrix<float>& input, matrix::MyMatrix<float>& target) {
    hiddenInputOutput = InHidMatrix * input;
    sigmoid(hiddenInputOutput);
    finalInputOutput = HidOutMatrix * hiddenInputOutput;
    sigmoid(finalInputOutput);
    // ���������� ��� ��������-���������
    matrix::MyMatrix<float> output_error = target - finalInputOutput;
    HidOutMatrix.Transposition();
    matrix::MyMatrix<float> hiddenError = HidOutMatrix * output_error;
    HidOutMatrix.Transposition();
    matrix::MyMatrix<float> correcting = output_error & finalInputOutput;
    correcting = correcting & (1.0 - finalInputOutput);
    hiddenInputOutput.Transposition();
    correcting = correcting * hiddenInputOutput;
    hiddenInputOutput.Transposition();
    correcting = correcting * learningRate;
    HidOutMatrix = HidOutMatrix + correcting;

    // ���������� ��� ��������-�������� ����

    correcting = hiddenError & hiddenInputOutput;
    correcting = correcting & (1.0 - hiddenInputOutput);
    input.Transposition();
    correcting = correcting * input;
    input.Transposition();
    correcting = correcting * learningRate;
    InHidMatrix = InHidMatrix + correcting;

}

void UMyNeuralNetwork::findBest(int amount) {

    float totalDistance_ = 0;
    float totalDistance_max = 0;
    int inputNeural_ = 0;
    int hiddenNeural_ = 0;
    int outputNeural_ = 0;
    float learningRate_ = 0;
    matrix::MyMatrix<float> InHidMatrix_(29, 11);
    matrix::MyMatrix<float> HidOutMatrix_(2, 29);
    std::ifstream from("C:/Users/���/CLionProjects/NeuralNetwork/AI.txt");
    for (size_t g = 0; g < amount + 1; g++) {
        from >> totalDistance_;
        from >> inputNeural_;
        from >> hiddenNeural_;
        from >> outputNeural_;
        from >> learningRate_;
        if (totalDistance_ > totalDistance_max) {
            totalDistance_max = totalDistance_;
            for (size_t a = 0; a < InHidMatrix_.Rows(); a++) {
                for (size_t f = 0; f < InHidMatrix_.Cols(); f++) {
                    from >> InHidMatrix_[a][f];
                }
            }
            for (size_t a = 0; a < HidOutMatrix_.Rows(); a++) {
                for (size_t f = 0; f < HidOutMatrix_.Cols(); f++) {
                    from >> HidOutMatrix_[a][f];
                }
            }
        }
        else {
            float trash;
            for (size_t a = 0; a < InHidMatrix_.Rows(); a++) {
                for (size_t f = 0; f < InHidMatrix_.Cols(); f++) {
                    from >> trash;
                }
            }
            for (size_t a = 0; a < HidOutMatrix_.Rows(); a++) {
                for (size_t f = 0; f < HidOutMatrix_.Cols(); f++) {
                    from >> trash;
                }
            }
        }
    }
    from.clear();
    from.close();
    std::ofstream filo("C:/Users/���/CLionProjects/NeuralNetwork/AI.txt");
    if (filo) {
        filo << totalDistance_max * 0.983 << " ";
        filo << inputNeural_ << " ";
        filo << hiddenNeural_ << " ";
        filo << outputNeural_ << " ";
        filo << learningRate_ << std::endl;
        for (size_t a = 0; a < InHidMatrix_.Rows(); a++) {
            for (size_t f = 0; f < InHidMatrix_.Cols(); f++) {
                filo << InHidMatrix_[a][f] << " ";
            }
            filo << std::endl;
        }
        for (size_t a = 0; a < HidOutMatrix_.Rows(); a++) {
            for (size_t f = 0; f < HidOutMatrix_.Cols(); f++) {
                filo << HidOutMatrix_[a][f] << " ";
            }
            filo << std::endl;
        }
    }
    filo.close();
    std::ofstream file("C:/Users/���/CLionProjects/NeuralNetwork/saving.txt");

    if (file) {
        file << 0 << " ";
        file << inputNeural_ << " ";
        file << hiddenNeural_ << " ";
        file << outputNeural_ << " ";
        file << learningRate_ << std::endl;
        for (size_t a = 0; a < InHidMatrix_.Rows(); a++) {
            for (size_t f = 0; f < InHidMatrix_.Cols(); f++) {
                file << InHidMatrix_[a][f] << " ";
            }
            file << std::endl;
        }
        for (size_t a = 0; a < HidOutMatrix_.Rows(); a++) {
            for (size_t f = 0; f < HidOutMatrix_.Cols(); f++) {
                file << HidOutMatrix_[a][f] << " ";
            }
            file << std::endl;
        }
    }
    file.close();

    std::ofstream fil("C:/Users/���/CLionProjects/NeuralNetwork/all.txt", std::ios::app);
    if (fil) {
        fil << totalDistance_max << " ";
        fil << inputNeural_ << " ";
        fil << hiddenNeural_ << " ";
        fil << outputNeural_ << " ";
        fil << learningRate_ << std::endl;
        for (size_t a = 0; a < InHidMatrix_.Rows(); a++) {
            for (size_t f = 0; f < InHidMatrix_.Cols(); f++) {
                fil << InHidMatrix_[a][f] << " ";
            }
            fil << std::endl;
        }
        for (size_t a = 0; a < HidOutMatrix_.Rows(); a++) {
            for (size_t f = 0; f < HidOutMatrix_.Cols(); f++) {
                fil << HidOutMatrix_[a][f] << " ";
            }
            fil << std::endl;
        }
        fil << std::endl;
    }
    fil.close();



}

UMyNeuralNetwork::~UMyNeuralNetwork() {

}


UMyNeuralNetwork::UMyNeuralNetwork(std::string file) {
    std::ifstream from(file);
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
}




FVector4 UMyNeuralNetwork::Query111(float forward, float rightdown, float rightup1, float rightup2, float leftup2, float leftup1, float leftdown, float newRight, float newLeft, float speed, float angle) {

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


void UMyNeuralNetwork::randomizeCoeff(int seed) {

    srand(seed);
    for (size_t k = 0; k < InHidMatrix.Rows(); k++) {
        for (size_t f = 0; f < InHidMatrix.Cols(); f++) {
            float coeff = (((rand() % 11) - 5) / 100.0) + 1;
            if (rand() % 600 == 0) coeff *= -1;
            if (InHidMatrix[k][f] == 0) {
                InHidMatrix[k][f] = ((rand() % 200000) / 100000.0) - 1;
            }

            if (rand() % 2 == 0)
                InHidMatrix[k][f] *= coeff;

        }

    }
    for (size_t k = 0; k < HidOutMatrix.Rows(); k++) {
        for (size_t f = 0; f < HidOutMatrix.Cols(); f++) {
            float coeff = (((rand() % 11) - 5) / 100.0) + 1;
            if (rand() % 600 == 0) coeff *= -1;
            if (HidOutMatrix[k][f] == 0) {
                HidOutMatrix[k][f] = ((rand() % 200000) / 100000.0) - 1;
            }

            if (rand() % 2 != 0)
                HidOutMatrix[k][f] *= coeff;

        }

    }

}


void UMyNeuralNetwork::writeToFile() {
    std::ofstream file("C:/Users/���/CLionProjects/NeuralNetwork/AI.txt", std::ios::app);
    if (file) {
        file << totalDistance << " ";
        file << inputNeural << " ";
        file << hiddenNeural << " ";
        file << outputNeural << " ";
        file << learningRate << std::endl;
        for (size_t a = 0; a < InHidMatrix.Rows(); a++) {
            for (size_t f = 0; f < InHidMatrix.Cols(); f++) {
                file << InHidMatrix[a][f] << " ";
            }
            file << std::endl;
        }
        for (size_t a = 0; a < HidOutMatrix.Rows(); a++) {
            for (size_t f = 0; f < HidOutMatrix.Cols(); f++) {
                file << HidOutMatrix[a][f] << " ";
            }
            file << std::endl;
        }
    }
    file.close();

}


void UMyNeuralNetwork::dataForTrain(float forward, float rightdown, float rightup1, float rightup2, float leftup2, float leftup1, float leftdown, float newRight, float newLeft, float moveForward, float moveRight, float speed, float angle) {
    std::ofstream file("C:/Users/���/CLionProjects/NeuralNetwork/training.txt", std::ios::app);
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


    for (int f = 0; f < inputs.Rows(); f++) {
        file << inputs[f][0] << " ";
    }
    file << moveForward << " " << moveRight << std::endl;
}