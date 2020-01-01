// TextFileToVector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> parse_row(string data, char delimiter) {
	string str_delimiter;
	str_delimiter += delimiter;
	vector<int> row;
	int length = data.size();
	if (data.at(0) == ' ') {
		int offset = 0;
		for (offset = 0; offset < (signed)data.length(); offset++) {
			if (isdigit(data.at(offset)))
				break;
		}
		data = data.substr(offset, data.length());
	}
	int index_end = data.find(str_delimiter);
	int elements = 0;
	while (true) {
		row.push_back(stoi(data.substr(0, index_end)));
		if (index_end != -1) {
			int offset = 0;
			bool digits_remaining = false;
			for (int j = index_end; j < (signed)data.length(); j++) {
				if (isdigit(data.at(j))) {
					digits_remaining = true;
					break;
				}
			}
			if (!digits_remaining)
				break;
			else {
				while (data.at(index_end + 1 + offset) == delimiter)
					offset++;
				data = data.substr(index_end + offset + 1, data.length());
				index_end = data.find(str_delimiter);
				elements++;
			}
		}
		else
			break;
	}
	return row;
}

int main()
{
	ifstream file;
	file.open("test.txt"); //Type your file's name between the parenthesis
	string line;
	vector<vector<int>> data;
	while (getline(file, line))
		data.push_back(parse_row(line, ' '));
	file.close();
	string out = "";
	for (int i = 0; i < (signed)data.size(); i++) {
		for (int j = 0; j < (signed)data[i].size(); j++)
			out += to_string(data[i][j]) + " ";
		if (i != (signed)data.size() - 1)
			out += "\n";
	}
	cout << out << endl;

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
