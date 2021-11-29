#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>

using namespace std;

// Function to check if the inputted number is valid
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

//Functions to sort the array elements in ascending order
void merge(double array[], int const left, int const mid, int const right)
{
	auto const subArrayOne = mid - left + 1;
	auto const subArrayTwo = right - mid;

	// Create temp arrays
	auto* leftArray = new double[subArrayOne],
		* rightArray = new double[subArrayTwo];

	// Copy data to temp arrays leftArray[] and rightArray[]
	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = array[left + i];
	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = array[mid + 1 + j];

	auto indexOfSubArrayOne = 0, // Initial index of first sub-array
		indexOfSubArrayTwo = 0; // Initial index of second sub-array
	int indexOfMergedArray = left; // Initial index of merged array

	// Merge the temp arrays back into array[left..right]
	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
			array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else {
			array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}
	// Copy the remaining elements of
	// left[], if there are any
	while (indexOfSubArrayOne < subArrayOne) {
		array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	// Copy the remaining elements of
	// right[], if there are any
	while (indexOfSubArrayTwo < subArrayTwo) {
		array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
}

// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
void sortArray(double array[], int const begin, int const end)
{
	if (begin >= end)
		return; // Returns recursively

	auto mid = begin + (end - begin) / 2;
	sortArray(array, begin, mid);
	sortArray(array, mid + 1, end);
	merge(array, begin, mid, end);
}

//Function to count the number of file's lines
int countLine(string filename) {
	//Open file
	ifstream file(filename);

	int count = 0;
	string line;

	//While loop to count line 
	while (getline(file, line)) {
		count++;
	}

	//Close file
	file.close();
	return count;
}

//Function to find the Mean of the array.
double findMean(double* arr, int arraySize) {
	double sum = 0;
	for (int i = 0; i < arraySize; i++) {
		sum += arr[i];
	}
	return sum / arraySize; //Return the average of the array.
}

//B.1 Function to find the Median value
double findMedian(double* arr, int arraySize) {
	float q2_position_full = -1 + 2 * float(arraySize) / 4 + float(0.5);

	// Taking the integer part
	int q2_position_int = int(q2_position_full);

	// Taking the fractional part
	float q2_position_frac = q2_position_full - q2_position_int;

	// Calculating the Median (Q2 - 2nd Quartile) value
	double q2 = arr[q2_position_int] + (arr[q2_position_int + 1] - arr[q2_position_int]) * q2_position_frac;

	return q2;
}

//B.2 Function to find the Mode value
double findMode(double* arr, int arraySize) {
	int currentCount = 1, maxCount = 1;
	double mode = arr[0];

	//For loops to find the maximum number of occurrences 
	//and the smallest most frequent element
	for (int i = 1; i < arraySize; i++) {
		if (arr[i] == arr[i - 1])
			currentCount++;
		else {
			if (currentCount > maxCount) {
				maxCount = currentCount;
				mode = arr[i - 1];
			}
			currentCount = 1;
		}
	}

	//check if the last element is mode value
	if (currentCount > maxCount)
	{
		maxCount = currentCount;
		mode = arr[arraySize - 1];
	}

	//Return the most frequently occured element in the array.
	return mode;
}

//B.3.1 Function to Find the variance 
double findVariance(double* arr, int arraySize, double mean) {
	double sum = 0;

	//For loop to count the sum of (x-mean(x))^2.
	for (int i = 0; i < arraySize; i++) {
		sum = sum + pow(arr[i] - mean, 2);
	}

	//Calculate the variance by dividing sum by (arraySize - 1)
	double var = sum / (arraySize - 1);

	return var;
}

//B.3.2 Function to find the Standard Deviation
double findStandardDeviation(double variance) {
	double stdDeviation = 0;

	//Calculate by using the sqrt() function for variance.
	stdDeviation = sqrt(variance);

	return stdDeviation;
}

//B.4 Function to find mean absolute deviations
double findMAD(double* arr, int arraySize, double mean) {
	double sum = 0;

	for (int i = 0; i < arraySize; i++) //for each row in the dataset
		sum = sum + abs(arr[i] - mean); //calculation

	return sum / arraySize; //return the mean absolute deviations
}


//B.5 Function to find the 3rd Quartile Exclusively
double findThirdQuartile(double* arr, int arraySize) {
	float q3_position_full = -1 + 3 * float(arraySize) / 4 + float(0.75);

	// Taking the integer part
	int q3_position_int = int(q3_position_full);

	// Taking the fractional part
	float q3_position_frac = q3_position_full - q3_position_int;

	// Calculating the 3rd Quartile (Q3) value
	double q3 = arr[q3_position_int] + (arr[q3_position_int + 1] - arr[q3_position_int]) * q3_position_frac;

	return q3;
}

//B.6 Function to find the Skewness
double findSkewness(double* arr, int arraySize, double mean, double standard_deviation) {
	double total = 0;

	// arraySize could be used directly, but n is shorter and cleaner
	double n = arraySize;

	// Loop through each element of the array and calculate total using the formula
	for (int i = 0; i < n; i++) {
		total += pow(((arr[i] - mean) / standard_deviation), 3);
	}

	return (1 / n) * total;
}

// B.7 Function to find kurtosis
double findKurtosis(double* arr, int arraySize, double mean, double standard_deviation) {
	double sum = 0;
	for (int i = 0; i < arraySize; i++) //for each row in the dataset
		sum += pow((arr[i] - mean), 4); //calculation
	return (sum / ((arraySize * pow(standard_deviation, 4)))) - 3; //return the kurtosis
}


//C.1 Function to find the Covariance    
double findCovariance(double* arrX, double* arrY, int arraySize, double x_mean, double y_mean) {
	double sum = 0;

	//For loop to count sum of x-mean(x) * y-mean(y).
	for (int i = 0; i < arraySize; i++) {
		sum = sum + (arrX[i] - x_mean) * (arrY[i] - y_mean);
	}

	sum = sum / (arraySize - 1); //Calculate Covariance by dividing sum by (size - 1).

	return sum;
}


//C.2 Function to find the Correlation Coefficient   
double findCorrelationCoefficient(double* arrX, double* arrY, int arraySize) {
	double total_X = 0, total_Y = 0, total_XY = 0;
	double square_sum_X = 0, square_sum_Y = 0;

	for (int i = 0; i < arraySize; i++) {
		total_X = total_X + arrX[i]; //calculate total value of array X
		total_Y = total_Y + arrY[i]; //calculate total value of array Y
		total_XY = total_XY + arrX[i] * arrY[i]; //calculate total value of x * y
		square_sum_X = square_sum_X + arrX[i] * arrX[i]; //calculate total value of x^2
		square_sum_Y = square_sum_Y + arrY[i] * arrY[i]; //calculate total value of y^2
	}

	double r = (arraySize * total_XY - total_X * total_Y) / sqrt((arraySize * square_sum_X - (total_X * total_X)) * (arraySize * square_sum_Y - (total_Y * total_Y)));

	return r; //return the Correlation Coefficient
}

//C.3 Function to find linear regression
void findLinearRegression(double x_mean, double y_mean, double x_stdev, double y_stdev, double correlation_coefficient) {
	// calculations
	double a = correlation_coefficient * y_stdev / x_stdev;
	double b = y_mean - a * x_mean;

	//output the equation
	if (b < 0) {
		cout << "y = " << a << "x " << b << endl;
	}
	else
		cout << "y = " << a << "x + " << b << endl;
}

double** processCSVToArrays(string fileName) {
	// Open file
	ifstream file(fileName);

	// Count the number of lines within the csv file
	int arraySizeRaw = countLine(fileName);

	// Create "heap" arrays with the counted size, then initialise all the elements with null
	double* xArrRaw = new double[arraySizeRaw] {'\0'};
	double* yArrRaw = new double[arraySizeRaw] {'\0'};

	string token1, token2;
	int i = 0;

	// From the opened file, get the x and y values and put them into the respective arrays
	while (getline(file, token1, ',')) {
		getline(file, token2);

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
	delete[] xArrRaw;
	delete[] yArrRaw;

	double** tmp = new double* [3];

	for (int i = 0; i < 3; i++) {
		tmp[i] = new double[arraySize];
	}

	for (int i = 0; i < arraySize; i++) {
		tmp[0][i] = xArr[i];
		tmp[1][i] = yArr[i];
	}

	tmp[2][0] = double(arraySize);

	return tmp;
}

void computeAndDisplayResult(string fileName) {
	// Call processCSVToArrays function to process arrays from csv file
	double** tmp = processCSVToArrays(fileName);

	// Get the arraySize from tmp
	int arraySize = int(tmp[2][0]);

	// Get xArr and yArr from tmp (not copying, but rather using the address from the tmp)
	double* xArr = tmp[0];
	double* yArr = tmp[1];

	// Clone the arrays (which won't be sorted) for usage in task C
	double* unsortedx = new double[arraySize];
	double* unsortedy = new double[arraySize];

	for (int i = 0; i <= arraySize; i++) {
		unsortedx[i] = xArr[i];
		unsortedy[i] = yArr[i];
	}

	// Sort the arrays
	sortArray(xArr, 0, arraySize - 1);
	sortArray(yArr, 0, arraySize - 1);

	// Function calls
	double x_median = findMedian(xArr, arraySize);
	double x_mean = findMean(xArr, arraySize);
	double x_variance = findVariance(xArr, arraySize, x_mean);
	double x_stdev = findStandardDeviation(x_variance);

	double y_median = findMedian(yArr, arraySize);
	double y_mean = findMean(yArr, arraySize);
	double y_variance = findVariance(yArr, arraySize, y_mean);
	double y_stdev = findStandardDeviation(y_variance);


	// Output
	cout << fixed;
	cout << setprecision(10);

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
	cout << "Q3_x = " << findThirdQuartile(xArr, arraySize) << " - " << "Q3_y = " << findThirdQuartile(yArr, arraySize) << endl;
	// B.6
	cout << "skew_x = " << findSkewness(xArr, arraySize, x_mean, x_stdev) << " - " << "skew_y = " << findSkewness(yArr, arraySize, y_mean, y_stdev) << endl;
	// B.7
	cout << "kurt_x = " << findKurtosis(xArr, arraySize, x_mean, x_stdev) << " - " << "kurt_y = " << findKurtosis(yArr, arraySize, y_mean, y_stdev) << endl;

	// Task C
	cout << "\nTask C:\n";
	// C.1
	cout << "cov(x_y) = " << findCovariance(unsortedx, unsortedy, arraySize, x_mean, y_mean) << endl;
	// C.2
	double correlation_coefficient = findCorrelationCoefficient(unsortedx, unsortedy, arraySize);
	cout << "r(x_y) = " << correlation_coefficient << endl;
	// C.3
	findLinearRegression(x_mean, y_mean, x_stdev, y_stdev, correlation_coefficient);

	// Preventing Memory Leak 
	delete[] tmp[0];
	delete[] tmp[1];
	delete[] tmp[2];
	delete[] tmp;
}

int main(int argc, char* argv[]) {
	// We calculate the time the program takes to run by getting the time at the 
	// beginning and end of the main function and subtract the end time by the start time.
	time_t start, end;

	// Record start time
	time(&start);

	// Check if the syntax is correct. If not, returns the error code -1 and prompts the user with the correct syntax
	if (argc != 2) {
		cerr << "Invalid Syntax!\nPlease run the program with the following syntax: ./assignment1_group23.exe <filename>.csv\n";
		return -1;
	}

	// Check if the file is valid/openable. If not, returns the error code -2.
	ifstream f;
	f.open(argv[1]);
	if (!f) {
		cerr << "File cannot be accessed. Please check again\n";
		f.close();
		return -2;
	}
	else {
		f.close();
	}

	// Call function to compute and display the statistical calculations
	computeAndDisplayResult(argv[1]);

	// Record end time
	time(&end);

	// Calculating total time taken by the program.
	double time_taken = double(end - start);
	cout << "\nTime taken by program is: " << fixed << time_taken << " seconds " << endl;
	cout << "(If time taken is 0s, it means the program ran in less than 1s)\n";

	// Outputting Group information as specifed
	cout << "\nASSIGNMENT 1 GROUP 23\n";
	cout << "s3878145, s3878145@rmit.edu.vn, Tri, Truong\n";
	cout << "s3872105, s3872105@rmit.edu.vn, Thang, Nguyen\n";
	cout << "s3878496, s3878496@rmit.edu.vn, Dat, Pham\n";

	return 0;
}
