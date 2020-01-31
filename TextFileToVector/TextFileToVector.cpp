// TextFileToVector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> data_dimensions(string file_name, char delimiter) {
	ifstream file;
	file.open(file_name);
	vector<int> dimensions;
	dimensions.resize(2, 0); //dimensions[0] = rows; dimenstions[1] = columns 
	string str_delimiter;
	str_delimiter += delimiter;
	string str_row;
	while (getline(file, str_row)) {
		int delim_pos = str_row.find(str_delimiter);
		int elements = 0;
		if (str_row.length() != 0) {
			while (delim_pos != -1) {
				str_row = str_row.substr(delim_pos + 1, str_row.length());
				delim_pos = str_row.find(str_delimiter);
				elements++;
			}
			elements++;
		}
		if (elements > dimensions[1])
			dimensions[1] = elements;
		dimensions[0]++;
	}
	file.close();
	return dimensions;
}

vector<vector<int>> parse_file(string file_name, vector<int> dimensions, char delimiter) {
	vector<vector<int>> data;
	data.resize(dimensions[0], vector<int>(dimensions[1], 0));
	ifstream file;
	file.open(file_name);
	string str_row;
	string str_delimiter;
	str_delimiter += delimiter;
	int n_rows = 0;
	while (getline(file, str_row)) {
		int index_end = str_row.find(str_delimiter);
		int index_str_row = 0;
		int n_cols = 0;
		while (n_cols < dimensions[1]) {
			string element = str_row.substr(0, index_end);
			bool digits_remaining = false;
			if (element.length() != 0) 
				data[n_rows][n_cols] = stoi(element);
			for (int i = index_end; i < str_row.length(); i++) {
				if (isdigit(str_row.at(i))) {
					digits_remaining = true;
					break;
				}
			}
			if (digits_remaining) {
				str_row = str_row.substr(index_end + 1, str_row.length());
				index_end = str_row.find(str_delimiter);
				n_cols++;
			}
			else
				break;
		}
		n_rows++;
	}
	file.close();
	return data;
}

vector<int> get_single_column(vector<vector<int>> data, int column) {
	vector<int> column_data;
	for (int i = 0; i < (signed)data.size(); i++) 
		column_data.push_back(data[i][column]);
	return column_data;
}

vector<int> get_single_row(vector<vector<int>> data, int row) {
	return data[row];
}

void display_data(vector<vector<int>> data) {
	for (int i = 0; i < (signed)data.size(); i++) {
		for (int j = 0; j < (signed)data[i].size(); j++)
			cout << to_string(data[i][j]) << " ";
		if (i != (signed)data.size() - 1)
			cout << endl;
	}
}

vector<int> extract_rows(int from, int to) {
	vector<int> out;
	return out;
}

vector<int> extract_columns(int from, int to) {
	vector<int> out;
	return out;
}

int main() {
	char delimiter = ','; //Change delimiter if different in raw data file
	string file_name = "test.txt"; //Type your file's name between the parenthesis
	vector<vector<int>> data;
	data = parse_file(file_name, data_dimensions(file_name, delimiter), delimiter);
	display_data(data);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
