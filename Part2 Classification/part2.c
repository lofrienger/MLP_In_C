#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "genann.h"
#include "part2_helper.h"

#define Data_RowTotal 4601
#define Data_ColTotal 58
#define Spam_Total 1813
#define Train_Total 3065
#define Test_Total 1536
#define Train_Spam_Num 1191
#define Test_Spam_Num 622
#define Train_NonSpam_Num (Train_Total - Train_Spam_Num)
#define Test_NonSpam_Num (Test_Total - Test_Spam_Num)

// #define LOGTRANSFORM
#define BINARIZATION

int main(int argc, char *argv[])
{
    printf("Part 2 Classification.\n");
    printf("Classify the Spambase dataset with MLP.\n");

    /* This will make the neural network initialize differently each run. */
    /* If you don't get a good result, try again for a different result. */
    srand(time(0));

    char filename[] = "spambase.data";
    char line[1024];
    double **data;
    int row, col;
    row = get_row(filename);
    col = get_col(filename);
    printf("\nIn original dataset, row = %d, col = %d\n", row, col);

    //dynamically allocate 2-D array
    data = (double **)malloc(row * sizeof(int *));
    for (int i = 0; i < row; ++i)
    {
        data[i] = (double *)malloc(col * sizeof(double));
    }
    get_data(line, data, filename);

    // print_data(data, row, col);

    // In orginal dataset, row 1-1813 are spam, row 1814-4601 are non-spam;
    // Randomly select 3065 (about 2/3) as training set, among which 1191 (about 1/3) are spam and
    // The remaining 1536 data are for testing, among which 622 are spam.
    double Train_X[Train_Total][57] = {{0, 0}};
    double Train_Y[Train_Total] = {0};
    float Test_X[Test_Total][57] = {{0, 0}};
    float Test_Y[Test_Total] = {0};
    int Train_Row = 0;
    int Test_Row = 0;

    // assign data
    for (int i = 0; i < Data_RowTotal; i++)
    {
        if (i < Train_Spam_Num)
        {
            for (int j = 0; j < 57; j++)
            {
                Train_X[Train_Row][j] = data[i][j];
            }
            Train_Y[Train_Row] = data[i][57];
            Train_Row += 1;
        }
        else if (i >= Train_Spam_Num && i < Spam_Total)
        {
            for (int j = 0; j < 57; j++)
            {
                Test_X[Test_Row][j] = data[i][j];
            }
            Test_Y[Test_Row] = data[i][57];
            Test_Row += 1;
        }
        else if (i >= Spam_Total && i < (Train_Total + Test_Spam_Num))
        {
            for (int j = 0; j < 57; j++)
            {
                Train_X[Train_Row][j] = data[i][j];
            }
            Train_Y[Train_Row] = data[i][57];
            Train_Row += 1;
        }
        else
        {
            for (int j = 0; j < 57; j++)
            {
                Test_X[Test_Row][j] = data[i][j];
            }
            Test_Y[Test_Row] = data[i][57];
            Test_Row += 1;
        }
    }

    // randomize data
    double temp_X[57] = {0};
    double temp_Y = 0;
    for (int i = 0, randIdx = 0; i < Train_Total; i++)
    {
        randIdx = rand() % Train_Total;
        if (randIdx != i)
        {
            for (int j = 0; j < 57; j++)
            {
                temp_X[j] = Train_X[i][j];
                Train_X[i][j] = Train_X[randIdx][j];
                Train_X[randIdx][j] = temp_X[j];
            }
            temp_Y = Train_Y[i];
            Train_Y[i] = Train_Y[randIdx];
            Train_Y[randIdx] = temp_Y;
        }
    }
    for (int i = 0, randIdx = 0; i < Test_Total; i++)
    {
        randIdx = rand() % Test_Total;
        if (randIdx != i)
        {
            for (int j = 0; j < 57; j++)
            {
                temp_X[j] = Test_X[i][j];
                Test_X[i][j] = Test_X[randIdx][j];
                Test_X[randIdx][j] = temp_X[j];
            }
            temp_Y = Test_Y[i];
            Test_Y[i] = Test_Y[randIdx];
            Test_Y[randIdx] = temp_Y;
        }
    }

    // data preprocessing
    // 1. Binarization: if a feature is  greater than 0, it’s simply set to 1. If it’s less than or equal to 0, it’s set to 0.
    // 2. Log-Transformed: transform each feature using log(X[i][j] + 0.1) (assume natural log)
#ifdef LOGTRANSFORM
    for (int i = 0; i < Train_Total; i++)
    {
        for (int j = 0; j < 57; j++)
        {
            Train_X[i][j] = log(Train_X[i][j] + 0.1);
        }
    }
    for (int i = 0; i < Test_Total; i++)
    {
        for (int j = 0; j < 57; j++)
        {
            Test_X[i][j] = log(Test_X[i][j] + 0.1);
        }
    }
#endif

#ifdef BINARIZATION
    for (int i = 0; i < Train_Total; i++)
    {
        for (int j = 0; j < 57; j++)
        {
            Train_X[i][j] = Train_X[i][j] > 0 ? 1 : 0;
        }
    }
    for (int i = 0; i < Test_Total; i++)
    {
        for (int j = 0; j < 57; j++)
        {
            Test_X[i][j] = Test_X[i][j] > 0 ? 1 : 0;
        }
    }
#endif

    /* Create a new network*/
    genann *ann = genann_init(57, 2, 5, 1);

    printf("\nInitialize a network with %d inputs, %d hidden layer of %d neurons and %d output.\n",
           ann->inputs, ann->hidden_layers, ann->hidden, ann->outputs);

    printf("\nTraining in progress...\n");

    /* Train many times. */
    for (int i = 0; i < 5000; ++i)
    {
        for (int j = 0; j < Train_Total; j++)
        {
            genann_train(ann, Train_X[j], Train_Y + j, 0.1);
        }
    }

    printf("\nTraining finished.\n");

    int Train_correct = 0, Test_correct = 0;
    for (int i = 0; i < Train_Total; i++)
    {
        // printf("%f\t%1.f\t%1.f\n", *genann_run(ann, Train_X[i]), *genann_run(ann, Train_X[i]), Train_Y[i]);
        if ((*genann_run(ann, Train_X[i]) > 0.5 ? 1 : 0) == Train_Y[i])
        {
            Train_correct++;
        }
    }
    for (int i = 0; i < Test_Total; i++)
    {
        if ((*genann_run(ann, (double *)Test_X[i]) > 0.5 ? 1 : 0) == (double)Test_Y[i])
        {
            Test_correct++;
        }
    }
    printf("\nTrain_correct/Train_Total: %d/%d\n", Train_correct, Train_Total);
    printf("Accuracy: %f\n", (float)Train_correct / Train_Total);
    printf("\nTest_correct/Test_Total: %d/%d\n", Test_correct, Test_Total);
    printf("Accuracy: %f\n", (float)Test_correct / Test_Total);

    genann_free(ann);
    return 0;
}
