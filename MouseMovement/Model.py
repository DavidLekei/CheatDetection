import tensorflow as tf
import pandas as pd
import numpy as np
import os

DATA_LENGTH = 57

#Reads data from CSV file and parses it into the Data array.
#The CSV file will also contain labels for the data which get stored in the labels array.
def load_data_array(data, labels, filename):
	a = [ ]
	with open(filename) as f:
		for line in f:
			line = line.strip('\n')
			if(line != '/'):
				nums = line.split(',')
				a.append(nums[1])
			else:
				data.append(np.asarray(a).astype(np.float32))
				a.clear()
				line = f.readline()
				line = line.strip('\n')
				labels.append(line)
	if(len(a) > DATA_LENGTH):
		a = np.resize(a, (1, 57))

	data.append(np.asarray(a).astype(np.float32))
	data.pop(0)



#Load all of the training, testing and prediction data
#Train the model
#Test the model
#Use the model to make predictions on the prediction data
#Prediction results get output to the console in the form of a list of lists.
#Each list contains 2 elements. The first element is the probability that the input was human.
#The second element is the probability that the input was NOT human.
def test():
	training_data = [ ]
	testing_data = [ ]
	training_labels = [ ]
	testing_labels = [ ]
	prediction_data = [ ]
	prediction_labels = [ ]

	class_labels = ['human', 'ai']

	load_data_array(training_data, training_labels, 'TrainingData.csv');
	load_data_array(testing_data, testing_labels, 'TestData.csv');
	load_data_array(prediction_data, prediction_labels, 'PredictData.csv')

	training_data = np.asarray(training_data)
	training_labels = np.asarray(training_labels).astype(np.float32)

	testing_data = np.asarray(testing_data)
	testing_labels = np.asarray(testing_labels).astype(np.float32)

	prediction_data= np.asarray(prediction_data)



	print('Info')
	print('-------------------------')
	print('-------------------------')
	print(training_data.shape)
	print(type(training_data))
	print(type(training_data[0]))
	print(type(training_data[0][0]))
	print('-------------------------')
	print('-------------------------')

	model = tf.keras.Sequential([
		tf.keras.layers.Flatten(input_shape=(1, 57)),
		tf.keras.layers.Dense(128, activation=tf.nn.relu),
		tf.keras.layers.Dense(32, activation=tf.nn.relu),
		tf.keras.layers.Dense(2, activation=tf.nn.softmax)
	])

	model.compile(optimizer='adam',
				  loss='sparse_categorical_crossentropy',
				  metrics=['accuracy'])

	model.fit(training_data, training_labels, epochs=20)


	print("Evaluate on test data")
	print("****************************************")
	print("****************************************")
	test_loss, test_acc = model.evaluate(testing_data, testing_labels, verbose=2)
	print('\nTest accuracy: ', test_acc)
	
	print("*****************************************")
	print("Predictions")
	print("*****************************************")
	predictions = model.predict(prediction_data)
	print(predictions)


if __name__ == '__main__':
	test()