import tensorflow as tf
import pandas as pd
import numpy as np
import os

def load_data_array(data, labels, filename):
	# a = np.array([(0,0)])
	a = [ ]
	with open(filename) as f:
		for line in f:
			line = line.strip('\n')
			if(line != '/'):
				nums = line.split(',')
				a.append(nums[1])
			else:
				print('-----------------------------------------------')
				print('a at the end of load_data_array')
				print(a)
				print('-----------------------------------------------')
				data.append(np.asarray(a).astype(np.float32))
				a.clear()
				line = f.readline()
				line = line.strip('\n')
				labels.append(line)
	data.append(np.asarray(a).astype(np.float32))
	data.pop(0)
	print('-----------------------------------------------')
	print('Data at the end of load_data_array')
	print(data)
	print('-----------------------------------------------')
	l = len(data)


def test():
	training_data = [ ]
	testing_data = [ ]
	training_labels = [ ]

	class_labels = ['human', 'ai']

	load_data_array(training_data, training_labels, 'TrainingData.csv');

	training_data = np.asarray(training_data)
	training_labels = np.asarray(training_labels).astype(np.float32)



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
		tf.keras.layers.Dense(2, activation=tf.nn.softmax)
	])

	model.compile(optimizer='adam',
				  loss='sparse_categorical_crossentropy',
				  metrics=['accuracy'])

	model.fit(training_data, training_labels, epochs=5)


	print("Evaluate on test data")
	


if __name__ == '__main__':
	test()
	#run()