#include <stdio.h>

#include "fann.h"

int main()
{
	const unsigned int num_layers = 4;
	const unsigned int num_neurons_hidden_1 = 2;
	const unsigned int num_neurons_hidden_2 = 5;

	const float desired_error = /*(const float)*/ 100;
	struct fann *ann;
	struct fann_train_data *train_data, *test_data;
	fann_type *output;

	unsigned int i = 0;

	printf("Creating network.\n");

	train_data = fann_read_train_from_file("spambase.train");

	test_data = fann_read_train_from_file("spambase.test");

	ann = fann_create_standard(num_layers, train_data->num_input, num_neurons_hidden_1, num_neurons_hidden_2, train_data->num_output);

	printf("Training network.\n");

	fann_set_training_algorithm(ann, FANN_TRAIN_INCREMENTAL);
	fann_set_learning_momentum(ann, 0.4f);

	// fann_set_learning_rate(ann, 0.5);
	fann_set_train_stop_function(ann, FANN_STOPFUNC_BIT);

	fann_train_on_data(ann, train_data, 3000, 1000, desired_error);

	int errNum_Train = 0, errNum_Test = 0, FP_Train = 0, FP_Test = 0, FN_Train = 0, FN_Test = 0;

	for (float treshold = 0.2; treshold < 1.0; treshold += 0.2)
	{
		for (i = 0; i < train_data->num_data; i++)
		{
			output = fann_run(ann, train_data->input[i]);

			if (train_data->output[i][0] != (output[0] > treshold ? 1 : 0)) // count error (FP+FN)
			{
				errNum_Train++;
			}

			if ((train_data->output[i][0] == 0) && (output[0] > treshold)) // count FP
			{
				FP_Train++;
			}
			if ((train_data->output[i][0] == 1) && (output[0] < treshold)) // count FN
			{
				FN_Train++;
			}
		}
		printf("Treshold: %f\n", treshold);
		printf("Train Accuracy: %d/%d = %f\n", train_data->num_data - errNum_Train, train_data->num_data, 1.0 - (float)errNum_Train / train_data->num_data);
		printf("For training dataset: False Positive: %d, False Negative: %d\n", FP_Train, FN_Train);

		for (i = 0; i < test_data->num_data; i++)
		{
			output = fann_run(ann, test_data->input[i]);
			if (test_data->output[i][0] != (output[0] > treshold ? 1 : 0))
			{
				errNum_Test++;
			}
			if ((test_data->output[i][0] == 0) && (output[0] > treshold)) // count FP
			{
				FP_Test++;
			}
			if ((test_data->output[i][0] == 1) && (output[0] < treshold)) // count FN
			{
				FN_Test++;
			}
		}
		printf("Test Accuracy: %d/%d = %f\n", test_data->num_data - errNum_Test, test_data->num_data, 1.0 - (float)errNum_Test / test_data->num_data);
		printf("For testing dataset: False Positive: %d, False Negative: %d\n\n", FP_Test, FN_Test);

		errNum_Train = 0, errNum_Test = 0, FP_Train = 0, FP_Test = 0, FN_Train = 0, FN_Test = 0;
	}

	fann_destroy_train(train_data);
	fann_destroy_train(test_data);
	fann_destroy(ann);

	return 0;
}
