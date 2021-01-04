#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "genann.h"
#include "part1_helper.h"

#define num_Train 200
#define num_Test 50
#define num_Total (num_Train + num_Test)

int main(int argc, char *argv[])
{
    printf("Part 1 Funtion Approximation.\n");
    printf("z = x * y (x range [0, 1], y range [0, 1]).\n");

    /* This will make the neural network initialize differently each run. */
    /* If you don't get a good result, try again for a different result. */
    srand(time(0));

    // Construct training and testing dataset
    double input_Train[num_Train][2] = {{0, 0}};
    double input_Test[num_Test][2] = {{0, 0}};
    double output_Train[num_Train] = {0};
    double output_Test[num_Test] = {0};
    double temp_X[num_Total] = {0};
    double temp_Y[num_Total] = {0};

    getRand(temp_X, num_Total);
    getRand(temp_Y, num_Total);
    for (int i = 0; i < num_Train; i++)
    {
        input_Train[i][0] = temp_X[i], input_Train[i][1] = temp_Y[i];
        output_Train[i] = input_Train[i][0] * input_Train[i][1];
        // printf("%f\t%f\t%f\n", input_Train[i][0], input_Train[i][1], output_Train[i]);
    }
    for (int i = 0; i < num_Test; i++)
    {
        input_Test[i][0] = temp_X[i + num_Train], input_Test[i][1] = temp_Y[i + num_Train];
        // printf("%f\t%f\n", input_Test[i][0], input_Test[i][1]);
    }

    /* New network */
    genann *ann = genann_init(2, 1, 5, 1);

    printf("\nInitialize a network with %d inputs, %d hidden layer of %d neurons and %d output.\n",
           ann->inputs, ann->hidden_layers, ann->hidden, ann->outputs);

    // default activation function is sigmoid, change to linear
    ann->activation_output = genann_act_linear;

    /* Train many times. */
    for (int i = 0; i < 5000; ++i)
    {
        for (int j = 0; j < num_Train; j++)
        {
            genann_train(ann, input_Train[j], output_Train + j, 0.1);
        }
    }

    double squareErrSum = 0.0;
    for (int j = 0; j < num_Test; j++)
    {
        squareErrSum += pow(input_Test[j][0] * input_Test[j][1] - *genann_run(ann, input_Test[j]), 2);
        // printf("Output for x = %f, y = %f is %f. True value is %f. Error is %f.\n",
        //        input_Test[j][0], input_Test[j][1], *genann_run(ann, input_Test[j]), input_Test[j][0] * input_Test[j][1],
        //        input_Test[j][0] * input_Test[j][1] - *genann_run(ann, input_Test[j]));
    }

    printf("\nTesting for %d data point, MSE: %f\n", num_Test, squareErrSum / num_Test);

    genann_free(ann);
    return 0;
}
