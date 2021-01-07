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

Part 2 Classification.

1. Classify the Spambase dataset with library genann (https://github.com/codeplea/genann).

In original dataset, row = 4601, col = 58

Initialize a network with 57 inputs, 2 hidden layer of 5 neurons and 1 output.

Training in progress...

Training finished.

Train_correct/Train_Total: 3007/3065
Accuracy: 0.981077

Test_correct/Test_Total: 914/1536
Accuracy: 0.595052

2. Classify the Spambase dataset with library fann (https://github.com/libfann/fann).

With fann, Training accuracy can reach 95% and testing accuracy can be >85%. Overfitting issue can be greatly improved.

Besides, **False positives (marking good mail as spam) are very undesirable. We can adjust treshold to reduce this.**

In folder Part2_fann, build with command: **gcc -g part2.c -o part2 -lfann -lm**, below information shoud be seen:

Creating network.
Training network.
Max epochs     3000. Desired error: 100.0000000000.
Epochs            1. Current error: 0.0987039804. Bit fail 697.
Epochs         1000. Current error: 0.0297055691. Bit fail 150.
Epochs         2000. Current error: 0.0285867881. Bit fail 149.
Epochs         3000. Current error: 0.0283926558. Bit fail 146.
Treshold: 0.200000
Train Accuracy: 2950/3065 = 0.962480
For training dataset: False Positive: 91, False Negative: 24
Test Accuracy: 1325/1536 = 0.862630
For testing dataset: False Positive: 150, False Negative: 61

Treshold: 0.400000
Train Accuracy: 2950/3065 = 0.962480
For training dataset: False Positive: 91, False Negative: 24
Test Accuracy: 1327/1536 = 0.863932
For testing dataset: False Positive: 148, False Negative: 61

Treshold: 0.600000
Train Accuracy: 2949/3065 = 0.962153
For training dataset: False Positive: 44, False Negative: 72
Test Accuracy: 1347/1536 = 0.876953
For testing dataset: False Positive: 108, False Negative: 81

Treshold: 0.800000
Train Accuracy: 2949/3065 = 0.962153
For training dataset: False Positive: 28, False Negative: 88
Test Accuracy: 1375/1536 = 0.895182
For testing dataset: False Positive: 66, False Negative: 95

## TODO:
With genann, accuracy for training dataset is very high while for testing dataset it is only about 60%. 

Need to consider avoiding overfitting issue during training with methods like regulation
