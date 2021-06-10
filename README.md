Requirements:
	Model.py:
		- tensorflow
		- pandas
		- numpy

	MouseTracker.c/MouseMover.c
		- Windows 7 or higher as it uses Windows API to capture mouse movements.
		- It was only ran and tested using MinGW64, so no idea if it will work with Cygwin.

Usage:
	The model should be usable as is and can be run with 'python Model.py'

	If you would like to create your own data, please follow these steps:

		1) Compile MouseTracker.c using 
			gcc MouseTracker.c -o MouseTracker

		2) Compile MouseMover using
			gcc MouseMover.c -o MouseMover

		3) Run MouseTracker.

			MouseTracker outputs all data to a CSV file. The name of this CSV file depends on whether or not you pass the '-ai' flag to it.
			If you run 'MouseTracker -ai', all mouse data will be logged in AI_MouseData.csv.
			If you run 'MouseTracker', all mouse data will be logged in HUMAN_MouseData.csv.

			The training data you are creating also gets labelled depending on the -ai flag. The data wil be labelled 0 if there is no -ai flag (ie human execution), or 1 with the -ai flag.

			Thus, run either MouseTracker -ai or just MouseTracker

		4) If you ran MouseTracker -ai in step 3, you will want to now launch MouseMover.
		   MouseMover takes in one command line argument: runs. This is an integer and will be the number of times the buttons get pressed (so the number of data points in the data set).

		   For example, if you want to collect 100 data points, you would run 'MouseMover 100'

		   If in step 3 you did not use the -ai flag, then you will need to click the buttons yourself to generate human data.

		5) Repeat step 3 with the opposite flag (If you used -ai, don't use it this time, and vice versa).

		6) Unfortunate manual step: you will need to open the newly created AI_MouseData.csv and HUMAN_MouseData.csv and copy/paste all of the data from both into a new file named TrainingData.csv

		7) Repeat steps 3 through 6 to generate Testing Data, but for step 6 name the final file TestData.csv

		8) Repeat steps 3 through 6 to generate Prediction Data, but for step 6 name the final file PredictData.csv

		9) You should now have 3 CSV files: TrainingData.csv, TestData.csv and PredictData.csv

		10) Run the model! 
		python Model.py


