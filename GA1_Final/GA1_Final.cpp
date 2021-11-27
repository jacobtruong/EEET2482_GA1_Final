#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>

using namespace std;

bool validNum(string input) {
	// If string is empty, return false
	int len = input.length();
	if (len <= 0) {
		return false;
	}

	// If first letter is not a '+', '-', '.', or numerical value, return false
	if (input[0] != '-' && input[0] != '+' && input[0] != '.' && (input[0] < '0' || input[0] > '9')) {
		return false;
	}

	bool dot_found = false;

	// If first character is a dot, set dot_found value to true
	if (input[0] == '.') {
		dot_found = true;
	}

	// Check through each of the remaining characters, detecting if the dot has been found at every step. 
	for (int i = 1; i < len; i++) {
		// If the character is not a numerical value or a dot, return false.
		if ((input[i] < '0' || input[i] > '9') && input[i] != '.') {
			return false;
		}
		else {
			// If the current character is a dot and there has already been a dot, return false
			if (input[i] == '.' && dot_found == false) {
				dot_found = true;
			}
			else if (input[i] == '.' && dot_found == true) {
				return false;
			}
		}
	}
	return true;
}

//Function to sort the array elements in ascending order
void sortFunction(double* arr, int size) {
	double tmp;
	for (int i = 0; i < size; i++) { // The loop to allocate the elements in the array
		for (int j = i + 1; j < size; j++) { // The loop to allocate the elements from 1 in the array
			if (arr[i] > arr[j]) { //Compare the element n with the element n+1
				//swap two values by using the temporary element
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}

int countLine(string filename) {
	ifstream file(filename);
	int count = 0;

	string line;
	while (getline(file, line)) {
		count++;
	}
	file.close();
	return count;
}

//Function to find the Mean of the array.
double findMean(double* arr, unsigned int size) {
	double sum = 0;
	for (int i = 0; i < size; i++) {
		sum += arr[i];
	}
	return sum / size; //Return the average of the array.
}

//B.1 Function to find the Median value
//double findMedian(double* arr, int size) {
//	if (size % 2 == 1) { //check if the array size is odd.
//		return arr[size / 2]; //return the median of the odd array
//	}
//	else if (size % 2 == 0) { //check if the array size is even.
//		return (arr[(size / 2) - 1] + arr[(size / 2)]) / 2; //return the median of the even array
//	}
//}

double findMedian(double* arr, int arraySize) {
	float q2_position_full = -1 + 2 * double(arraySize) / 4 + 0.5;

	// Taking the integer part
	int q2_position_int = int(q2_position_full);

	// Taking the fractional part
	float q2_position_frac = q2_position_full - q2_position_int;

	// Calculating the Median (Q2 - 2nd Quartile) value
	double q2 = arr[q2_position_int] + (arr[q2_position_int + 1] - arr[q2_position_int]) * q2_position_frac;

	return q2;
}

//B.2 Function to find the Mode value
double findMode(double* arr, int size) {
	int maxCount = 0;
	double mostFrequentElement = 0;

	//Loops to find the maximum number of occurrences. 
	for (int i = 0; i < size; i++) {
		int count = 1;
		for (int j = i + 1; j < size; j++) {
			if (arr[i] == arr[j]) {
				count++;
			}
		}
		if (count > maxCount) {
			maxCount = count;
		}
	}

	//Loops to compare the maximum number of occurrences to the occurrences of elements. 
	for (int i = 0; i < size; i++) {
		int count = 1;
		for (int j = i + 1; j < size; j++) {
			if (arr[i] == arr[j]) {
				count++;
			}
		}

		//Find the lowest mode value because the array is sorted.
		if (count == maxCount) {
			mostFrequentElement = arr[i];
			break;
		}
	}

	return mostFrequentElement; //Return the most frequently occured element in the array.
}

//B.3.1 Function to Find the variance 
double findVariance(double* arr, unsigned int size) {
	double sum = 0;
	for (unsigned int i = 0; i < size; i++) { //For loop to count the sum of (x-mean(x))^2.
		sum = sum + pow(arr[i] - findMean(arr, size), 2);
	}
	double var = sum / (size - 2); //Calculate the variance by dividing sum by (size - 1 - 1) in the true size.
	return var;
}

//B.3.2 Function to find the Standard Deviation
double findStandardDeviation(double variance) {
	double stdDeviation = 0;
	stdDeviation = sqrt(variance); //Calculate by using the sqrt() function.
	return stdDeviation;
}

//B.4 Function to find mean standard deviation
double findMAD(double* arr, int size, double mean) {
	double sum = 0;

	for (int i = 0; i < size; i++) //for each row in the dataset
		sum = sum + abs(arr[i] - mean); //calculation

	return sum / size; //return the mean standard deviation
}


//B.5 Function to find the 3rd Quartile Exclusively
double find3rdQuartile(double* arr, int arraySize) {
	float q3_position_full = -1 + 3 * float(arraySize) / 4 + 0.75;

	// Taking the integer part
	int q3_position_int = int(q3_position_full);

	// Taking the fractional part
	float q3_position_frac = q3_position_full - q3_position_int;

	// Calculating the Quartile value
	double q3 = arr[q3_position_int] + (arr[q3_position_int + 1] - arr[q3_position_int]) * q3_position_frac;

	return q3;
}

//B.6 Function to find the Skewness
double findSkewness(double* arr, int arraySize, double mean, double standard_deviation) {
	double total = 0;
	double n = arraySize;

	// Loop through each element of the array and calculate total using the formula
	for (int i = 0; i < n; i++) {
		total += pow(((arr[i] - mean) / standard_deviation), 3);
	}

	return (1 / n) * total;
}

// B.7 Function to find kurtosis
double findKurtosis(double* arr, int size, double mean, double standard_deviation) {
	double sum = 0;
	for (int i = 0; i < size; i++) //for each row in the dataset
		sum += pow((arr[i] - mean), 4); //calculation
	return (sum / ((size * pow(standard_deviation, 4)))) - 3; //return the kurtosis
}


//C.1 Function to find the Covariance    
double findCovariance(double* arrX, double* arrY, int size, double x_mean, double y_mean) {
	double sum = 0;

	//For loop to count sum of x-mean(x) * y-mean(y).
	for (int i = 1; i < size; i++) {
		sum = sum + (arrX[i] - x_mean) * (arrY[i] - y_mean);
	}

	sum = sum / (size - 1 - 1); //Calculate Covariance by dividing sum by (size - 1).

	return sum;
}


//C.2 Function to find the Correlation Coefficient   
double findCorrelationCoefficient(double* arrX, double* arrY, int size) {
	double total_X = 0, total_Y = 0, total_XY = 0;
	double square_sum_X = 0, square_sum_Y = 0;

	for (int i = 0; i < size; i++) {
		total_X = total_X + arrX[i]; //calculate total value of array X
		total_Y = total_Y + arrY[i]; //calculate total value of array Y
		total_XY = total_XY + arrX[i] * arrY[i]; //calculate total value of x * y
		square_sum_X = square_sum_X + arrX[i] * arrX[i]; //calculate total value of x^2
		square_sum_Y = square_sum_Y + arrY[i] * arrY[i]; //calculate total value of y^2
	}

	double r = (size * total_XY - total_X * total_Y) / sqrt((size * square_sum_X - (total_X * total_X)) * (size * square_sum_Y - (total_Y * total_Y)));

	return r; //return the Correlation Coefficient
}

//C.3 Function to find linear regression
void findLinearRegression(double* xArr, double* yArr, int size, double x_mean, double y_mean, double x_stdev, double y_stdev, double correlation_coefficient) {
	// calculations
	double a = correlation_coefficient * y_stdev / x_stdev;
	double b = y_mean - a * x_mean;

	//output the equation	
	cout << "y = " << a << "x + " << b << endl;
}


int main(int argc, char* argv[]) {
	/* Time function returns the time since the
		Epoch(jan 1 1970). Returned time is in seconds. */
	time_t start, end;

	/* You can call it like this : start = time(NULL);
	 in both the way start contain total time in seconds
	 since the Epoch. */
	time(&start);

	// unsync the I/O of C and C++.
	ios_base::sync_with_stdio(false);



	// Return error code -1 when file has been unsuccessfully opened
	ifstream file(argv[1]);
	if (!file) {
		cerr << "Cannot open file.\n";
		return -1;
	}

	// Count the number of lines within the csv file
	int arraySizeRaw = countLine(argv[1]);

	// Create "heap" arrays with the counted size, then initialise all the elements with null
	double* xArrRaw = new double[arraySizeRaw] {'\0'};
	double* yArrRaw = new double[arraySizeRaw] {'\0'};

	string line;
	int i = 0;

	// From the opened file, get the x and y values and put them into the respective arrays
	while (getline(file, line)) {
		stringstream ss(line);
		string token1;
		string token2;

		getline(ss, token1, ',');
		getline(ss, token2, ',');

		if (!validNum(token1) || !validNum(token2)) {
			continue;
		}
		else {
			xArrRaw[i] = stod(token1);
			yArrRaw[i] = stod(token2);
			i++;
		}
	}

	// This is the count of the final array size (valid values only)
	int arraySize = i;

	file.close();

	// Create 2 arrays, this time only with valid values in the elements
	double* xArr = new double[arraySize];
	double* yArr = new double[arraySize];

	// Only valid values are added into the new, final arrays, by checking if the element is '\0' or not
	int j = 0;
	for (int i = 0; i < arraySizeRaw; i++) {
		if (xArrRaw[i] == '\0') {
			continue;
		}
		else {
			xArr[j] = xArrRaw[i];
			yArr[j] = yArrRaw[i];
			j++;
		}
	}

	// Delete the original arrays
	delete(xArrRaw);
	delete(yArrRaw);

	// Sort the arrays
	sortFunction(xArr, arraySize);
	sortFunction(yArr, arraySize);

	// Function calls
	double x_median = findMedian(xArr, arraySize);
	double x_mean = findMean(xArr, arraySize);
	double x_variance = findVariance(xArr, arraySize);
	double x_stdev = findStandardDeviation(x_variance);

	double y_median = findMedian(yArr, arraySize);
	double y_mean = findMean(yArr, arraySize);
	double y_variance = findVariance(yArr, arraySize);
	double y_stdev = findStandardDeviation(y_variance);
	

	// Output
	cout << fixed;
	cout << setprecision(5);

	// Task B
	cout << "Task B:\n";
	// B.1
	cout << "median_x = " << x_median << " - " << "median_y = " << y_median << endl;
	// B.2
	cout << "mode_x = " << findMode(xArr, arraySize) << " - " << "mode_y = " << findMode(yArr, arraySize) << endl;
	// B.3
	cout << "var_x = " << x_variance << " - " << "var_y = " << y_variance << endl;
	cout << "stdev_x = " << x_stdev << " - " << "stdev_y = " << y_stdev << endl;
	// B.4
	cout << "mad_x = " << findMAD(xArr, arraySize, x_mean) << " - " << "mad_y = " << findMAD(yArr, arraySize, y_mean) << endl;
	// B.5
	cout << "Q3_x = " << find3rdQuartile(xArr, arraySize) << " - " << "Q3_y = " << find3rdQuartile(yArr, arraySize) << endl;
	// B.6
	cout << "skew_x = " << findSkewness(xArr, arraySize, x_mean, x_stdev) << " - " << "skew_y = " << findSkewness(yArr, arraySize, y_mean, y_stdev) << endl;
	// B.7
	cout << "kurt_x = " << findKurtosis(xArr, arraySize, x_mean, x_stdev) << " - " << "kurt_y = " << findKurtosis(yArr, arraySize, y_mean, y_stdev) << endl;

	// Task C
	cout << "\nTask C:\n";
	// C.1
	cout << "cov(x_y) = " << findCovariance(xArr, yArr, arraySize, x_mean, y_mean) << endl;
	// C.2
	double correlation_coefficient = findCorrelationCoefficient(xArr, yArr, arraySize);
	cout << "r(x_y) = " << correlation_coefficient << endl;
	// C.3
	findLinearRegression(xArr, yArr, arraySize, x_mean, y_mean, x_stdev, y_stdev, correlation_coefficient);

	// Recording end time.qq 
	time(&end);

	// Calculating total time taken by the program.
	double time_taken = double(end - start);
	cout << "Time taken by program is : " << fixed
		<< time_taken << setprecision(5);
	cout << " sec " << endl;

	return 0;
}
