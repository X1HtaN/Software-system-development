#include <vector>
#include <fstream>
#include <string>
#include "GeneralFunctions.h"

using namespace std;

vector<int> comb_sort(vector<int> input) {
	vector<int> result_vec = input;
	int step = result_vec.size();
	bool flag = false;
	while (step > 1 || flag) {
		if (step > 1) {
			step = step * 4 / 5;
		}
		flag = false;
		int i = 0;
		while (i + step < result_vec.size()) {
			if (result_vec[i] > result_vec[i + step]) {
				flag = true;
				swap(result_vec[i], result_vec[i + step]);
			}
			i += step;
		}
	}

	return result_vec;
}

void save_vector(std::vector<int> vec, vector<int> result_vec, string url)
{
	ofstream output(url);
	output << "Исходный вектор:" << endl;
	for (int i = 0; i < vec.size(); i++)
	{
		output << vec[i] << " ";
	}
	output << endl << "Отсортированный вектор:" << endl;
	for (int i = 0; i < result_vec.size(); i++)
	{
		output << result_vec[i] << " ";
	}

	output.close();
}
