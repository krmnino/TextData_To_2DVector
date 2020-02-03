#include <iostream>
#include <assert.h>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> data_dimensions(string file_name, string delimiter) {
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

vector<vector<int>> parse_file(string file_name, vector<int> dimensions, string delimiter) {
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

vector<vector<int>> get_rows(vector<vector<int>> &data, int from, int to) {
	assert(0 <= from && from < to && to < data.size());
	vector<vector<int>> out;
	for (int i = from; i < to; i++) 
		out.push_back(data[i]);
	return out;
}

vector<vector<int>> get_columns(vector<vector<int>> &data, int from, int to) {
	assert(0 <= from && from < to && to < data[0].size());
	vector<vector<int>> out;
	for (int i = 0; i < data.size(); i++) {
		vector<int> row;
		for (int j = from; j < to; j++)
			row.push_back(data[i][j]);
		out.push_back(row);
	}
	return out;
}

void save_txt(vector<vector<int>> data, string delimiter, string name) {
	ofstream out_file;
	out_file.open(name);
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data[0].size(); j++) {
			if (j == data[0].size() - 1) 
				out_file << to_string(data[i][j]) + "\n";
			else 
				out_file << to_string(data[i][j]) + delimiter;
		}
	}
}

void display_data(vector<vector<int>> data) {
	for (int i = 0; i < (signed)data.size(); i++) {
		for (int j = 0; j < (signed)data[i].size(); j++)
			cout << to_string(data[i][j]) << " ";
		if (i != (signed)data.size() - 1)
			cout << endl;
	}
	cout << endl;
}

void display_usage() {
	
	cout << "Usage:		[action] [shape] [from] [to] [delimiter] [in_file] [out_file] " << endl;
	cout << "		-v <in_file>" << endl;
	cout << "		-d -r|-c <INT> <INT> <delim> <in_file> <out_file>" << endl;
	cout << "		-e -r|-c <INT> <INT> <delim> <in_file> <out_file>\n" << endl;
	cout << "action:	-v: view text file in terminal" << endl;
	cout << "		-d: display..." << endl;
	cout << "		-e: extract...\n" << endl;
	cout << "shape:		-r: rows" << endl;
	cout << "		-c: columns\n" << endl;
	cout << "from:		select rows/columns from index (inclusive)\n" << endl;
	cout << "to:		select rows/columns to index (exclusive)\n" << endl;
	cout << "in_file:	name of the file where data is read from (include extension)\n" << endl;
	cout << "out_file:	name of the file where dara is written to\n" << endl;
}

int main(int argc, char *argv[]) {
	if (argc != 4 && argc != 6 && argc != 8) {
		display_usage();
		exit(EXIT_FAILURE);
	}
	string flag = argv[1];
	if (flag == "-v") {
		string delimiter = argv[2];
		string file_name = argv[3];
		display_data(parse_file(file_name, data_dimensions(file_name, delimiter), delimiter));
	}
	else if (flag == "-d") {
		flag = argv[2];
		if (flag == "-r") {
			string delimiter = argv[5];
			string file_name = argv[6];
			vector<vector<int>> data = parse_file(file_name, data_dimensions(file_name, delimiter), delimiter);
			display_data(get_rows(data, stoi(argv[3]), stoi(argv[4])));
		}
		else if (flag == "-c") {
			string delimiter = argv[5];
			string file_name = argv[6];
			vector<vector<int>> data = parse_file(file_name, data_dimensions(file_name, delimiter), delimiter);
			display_data(get_columns(data, stoi(argv[3]), stoi(argv[4])));
		}
		else {
			display_usage();
			exit(EXIT_FAILURE);
		}
	}
	else if (flag == "-e") {
		flag = argv[2];
		if (flag == "-r") {
			string delimiter = argv[5];
			string file_name = argv[6];
			string out_file = argv[7];
			vector<vector<int>> data = parse_file(file_name, data_dimensions(file_name, delimiter), delimiter);
			save_txt(get_rows(data, stoi(argv[3]), stoi(argv[4])), delimiter, out_file);
		}
		else if (flag == "-c") {
			string delimiter = argv[5];
			string file_name = argv[6];
			string out_file = argv[7];
			vector<vector<int>> data = parse_file(file_name, data_dimensions(file_name, delimiter), delimiter);
			save_txt(get_columns(data, stoi(argv[3]), stoi(argv[4])), delimiter, out_file);
		}
		else {
			display_usage();
			exit(EXIT_FAILURE);
		}
	}
	else {
		display_usage();
		exit(EXIT_FAILURE);
	}
}
