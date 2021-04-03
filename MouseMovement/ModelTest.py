import tensorflow as tf
import pandas as pd
import numpy as np
import os

def load_data():
	#data = tf.data.TFRecordDataset()
	data = tf.data.Dataset.from_tensor_slices([(0, 1), (1, 2), (4, 7)])
	print(data)

def run():
	print('Running TensorFlow test')
	load_data()

def test():
	# data = np.genfromtxt(r'test_data.txt', dtype=int, delimiter=',')
	# print(data)
	# dataset = tf.data.Dataset.from_tensor_slices(data)
	# print(dataset)
	# print('*****************************************************************')
	# for d in dataset:
	# 	print(d.numpy())
	a = np.array([(0,0)])
	with open('test_data.txt') as f:
		for line in f:
			line = line.strip('\n')
			if(line != '/'):
				nums = line.split(',')
				t = [nums[0], nums[1]]
				t = tuple(t)
				print(t)
				a = np.append(a, t)
			else:
				print('**********************************************\n', a, '\n*******************************************\n')
				a = np.array([(0,0)])


if __name__ == '__main__':
	test()
	#run()