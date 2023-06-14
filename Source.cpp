#include <iostream>
#include <vector>
#include <fstream>
#include <thread>
#include <mutex>

using namespace std;

mutex mutex1;

void matrixMultiply(vector<vector<int>> matrixA, vector<vector<int>> matrixB, int a_rows, int a_cols, int b_rows, int b_cols) { //result
	mutex1.lock();
	vector<vector<int>> result(a_rows, vector<int>(b_cols, 0));
	for (int i = 0; i < a_rows; i++) {
		for (int j = 0; j < b_cols; j++) {
			for (int k = 0; k < a_cols; k++) {
				result[i][j] += matrixA[i][k] * matrixB[k][j];					//A is good . result : result[i][j]
			}
		}
	}
	for (int i = 0; i < a_rows; i++) {
		for (int j = 0; j < b_cols; j++) {
			cout << result[i][j] << " ";
		}
		cout << endl;
	}
	mutex1.unlock();
}


int main(int argc, char* argv[]) {
	/*if (argc > 4) {
		cout << "Error, more than 4 arguments" << endl;
	}
	*/
	ifstream A;
	A.open("A.txt");

	int arg1 = 4;
	int arg2 = 5;
	int arg3 = 6;
	if (!A.is_open()) {
		cout << "File A cannot be opened" << endl;
	}

	//vector A input
	vector<vector<int>> matrixA(arg1, vector<int>(arg2));
	for (int i = 0; i < arg1; i++) {
		for (int j = 0; j < arg2; j++) {
			A >> matrixA[i][j];
		}
	}
	A.close();

	//testing vector A output
	for (int i = 0; i < arg1; i++) {
		for (int j = 0; j < arg2; j++) {
			cout << matrixA[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;
	cout << endl;

	ifstream B;
	B.open("B.txt");

	if (!B.is_open()) {
		cout << "File B cannot be read" << endl;
	}

	vector<vector<int>> matrixB(arg2, vector<int>(arg3));
	for (int i = 0; i < arg2; i++) {
		for (int j = 0; j < arg3; j++) {
			B >> matrixB[i][j];
		}
	}
	B.close();

	for (int i = 0; i < arg2; i++) {
		for (int j = 0; j < arg3; j++) {
			cout << matrixB[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;
	cout << endl;
	cout << "Matrix Multiply Result:" << endl;
	std::thread t1(matrixMultiply,matrixA, matrixB, arg1, arg2, arg2, arg3); //every thread calculates for c(i,j)
	std::thread t2(matrixMultiply, matrixA, matrixB, arg1, arg2, arg2, arg3);
	t1.join();
	t2.join();

}