# MLP_In_C
## Part I:
Use the C (or C++) programming language to design and train multilayer perceptron neural networks to approximate the following functions
(1) z = x + y (0≤x≤1, 0≤y≤1)
(2) z = x*y (0≤x≤1, 0≤y≤1)
(3) z = x*x + y*y (0≤x≤1, 0≤y≤1)
Note that the training dataset and testing dataset should be different. Please measure and report the test accuracy of your trained neural networks.

(1) In folder **Part1 Function Approximation**, excute part1_1.exe directly or run **gcc -g genann.c part1_helper.c part1_1.c -o part1_1.exe** to build then excute part1_1.exe, 
below information should be seen:

Part 1 Funtion Approximation.
z = x + y (x range [0, 1], y range [0, 1]).

Initialize a network with 2 inputs, 1 hidden layer of 2 neurons and 1 output.

Testing for 50 data point, MSE: 0.000003.

(2) In folder **Part1 Function Approximation**, excute part1_2.exe directly or run **gcc -g genann.c part1_helper.c part1_2.c -o part1_2.exe** to build then excute part1_2.exe, 
below information should be seen:

Part 1 Funtion Approximation.
z = x * y (x range [0, 1], y range [0, 1]).

Initialize a network with 2 inputs, 1 hidden layer of 5 neurons and 1 output.

Testing for 50 data point, MSE: 0.000012

(3) In folder **Part1 Function Approximation**, excute part1_3.exe directly or run **gcc -g genann.c part1_helper.c part1_3.c -o part1_3.exe** to build then excute part1_3.exe, 
below information should be seen:

Part 1 Funtion Approximation.
z = x*x + y*y (x range [0, 1], y range [0, 1]).

Initialize a network with 2 inputs, 1 hidden layer of 5 neurons and 1 output.

Testing for 50 data point, MSE: 0.000028

## Part II:
Use the C (or C++) programming language to design and train a multilayer perceptron neural network to classify the spambase dataset: https://archive.ics.uci.edu/ml/datasets/spambase

In folder **Part1 Function Approximation**, excute part1_3.exe directly or run **gcc -g genann.c part1_helper.c part1_3.c -o part1_3.exe** to build then excute part1_3.exe, 
below information should be seen:

Part 2 Classification.
Classify the Spambase dataset with MLP.

In original dataset, row = 4601, col = 58

Initialize a network with 57 inputs, 2 hidden layer of 5 neurons and 1 output.

Training in progress...

Training finished.

Train_correct/Train_Total: 3007/3065
Accuracy: 0.981077

Test_correct/Test_Total: 914/1536
Accuracy: 0.595052

## TODO:
Accuracy for training dataset is very high while for testing dataset it is only about 60%. 

Need to consider avoiding overfitting issue during training with methods like regulation
