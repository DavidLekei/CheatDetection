import tensorflow as tf
import pandas as pd
import numpy as np
import os

training_data = [ ]
testing_data = [ ]

def load_data_array(data, filename):
	a = np.array([(0,0)])
	with open(filename) as f:
		for line in f:
			line = line.strip('\n')
			if(line != '/'):
				nums = line.split(',')
				t = [nums[0], nums[1]]
				t = tuple(t)
				a = np.append(a, t)
			else:
				data.append(a)
				a = np.array([(0,0)])

def load_data():
	#data = tf.data.TFRecordDataset()
	data = tf.data.Dataset.from_tensor_slices([(0, 1), (1, 2), (4, 7)])

	column_names = ['x_coord', 'y_coord']

	print(data)

def run():
	print('Running TensorFlow test')
	load_data()

def test():
	column_names = ['x_coord', 'y_coord', 'is_ai']
	training_data = pd.read_csv('AI_MouseData.csv', names=column_names) 
	testing_data = pd.read_csv('HUMAN_MouseData.csv', names=column_names)

	feature_names = column_names[:-1]
	label_names = column_names[-1]
	
	batch_size = 2

	train_dataset = tf.data.experimental.make_csv_dataset(
		'AI_MouseData.csv',
		batch_size,
		column_names=column_names,
		label_name=label_names,
		num_epochs=1
	)

	features, labels = next(iter(train_dataset))
	print(features)
	#training_set = tf.data.Dataset.from_tensor_slices(training_data)
	#testing_set = tf.data.Dataset.from_tensor_slices(testing_data)
	#print(testing_data)

	# train_set = tfdata_generator(training_data, is_training=True, batch_size=len(training_data))
	# test_set = tfdata_generator(testing_data, is_training=False, batch_size=len(testing_data))

	# print(training_data)
	# print(testing_data)

	# model = tf.keras.Sequential([
	# 	tf.keras.layers.Dense(input_dim=2, units=128, activation="relu"),
	# 	tf.keras.layers.Dense(units=64, activation="relu"),
	# 	tf.keras.layers.Dropout(0.2),
	# 	tf.keras.layers.Dense(units=32, activation="relu"),
	# 	tf.keras.layers.Dropout(0.2),
	# 	tf.keras.layers.Dense(units=32, activation="relu"),
	# 	tf.keras.layers.Dropout(0.2),
	# 	tf.keras.layers.Dense(units=16, activation="relu"),
	# 	tf.keras.layers.Dropout(0.2),
	# 	tf.keras.layers.Dense(units=1, activation="sigmoid")])
	# model.summary()

	# metrics = [tf.keras.metrics.Accuracy(name="Accuracy"), tf.keras.metrics.Precision(name="Precision"), tf.keras.metrics.Recall(name="Recall")]

	# model.compile(optimizer="adam", loss="binary_crossentropy", metrics=metrics)
	# model.fit(training_data, batch_size=32,
	# 						 steps_per_epoch=len(training_data),
	#  						 epochs=100,
	#  						 verbose=1)
	print("Evaluate on test data")
	#score = model.evaluate(X_test, Y_test)
	#print("test loss, test accuracy, test precision, test recall: ", score)
	# load_data_array()
	# for a in data:
	# 	print('**********************************************\n', a, '\n*******************************************\n')
	


if __name__ == '__main__':
	test()
	#run()