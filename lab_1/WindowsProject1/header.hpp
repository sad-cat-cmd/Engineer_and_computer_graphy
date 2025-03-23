#pragma once

#include "framework.h"
#include <vector>
#include <chrono>
#include <thread>
#include <math.h>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

vector <float> vector_X_Points = { 100, 150, 150, 50,  50, 100, 50,  10,  10,  50,  150, 190, 190, 150};
vector <float> vector_Y_Points = { 0,   50 , 550, 550, 50, 0,   500, 600, 400, 500, 500, 600, 400, 500};

float move_matrix[3][3] = {
	{1, 0, 0},
	{0, 1, 0},
	{0, 0, 1}
};
float decrease_matrix[3][3] = {
	{1, 0, 0},
	{0, 1, 0},
	{0, 0, 1}
};
float mapping_matrix[3][3] = {
		{0, 1, 0},
		{1, 0, 0},
		{0, 0, 1}
};

void movements_images(float _X_movements, float _Y_movements) {
	for (int i = 0; i < vector_X_Points.size(); i++) { vector_X_Points[i] = vector_X_Points[i] + _X_movements; }
	for (int i = 0; i < vector_X_Points.size(); i++) { vector_Y_Points[i] = vector_Y_Points[i] - _Y_movements; }
}
void decrease_images(float ratio) {
	for (int i = 0; i < vector_X_Points.size(); i++) {
		vector_X_Points[i] = vector_X_Points[i] / ratio; 
	}
	for (int i = 0; i < vector_X_Points.size(); i++) {
		vector_Y_Points[i] = vector_Y_Points[i] / ratio;
	}
}
void mapping_X_Y() {
	vector <float> temp_vector = vector_X_Points;
	for (int i = 0; i < vector_X_Points.size(); i++) {
		vector_X_Points[i] = vector_Y_Points[i];
		vector_Y_Points[i] = temp_vector[i];
	}
}
void sleep_wiev_images() {
	sleep_for(nanoseconds(10));
	sleep_until(system_clock::now() + seconds(3));
}
float get_figure_length() {
	float min_X = *min_element(vector_X_Points.begin(), vector_X_Points.end());
	float max_X = *max_element(vector_X_Points.begin(), vector_X_Points.end());
	return abs(max_X - min_X);
}
float get_figure_height() {
	float min_Y = *min_element(vector_Y_Points.begin(), vector_Y_Points.end());
	float max_Y = *max_element(vector_Y_Points.begin(), vector_Y_Points.end());
	return abs(max_Y - min_Y);
}

void show_images(HDC _hdc) {
	for (int i = 0; i < vector_X_Points.size(); i++) {
		if (i == 0 || i == 6 || i == 10) {
			MoveToEx(_hdc, vector_X_Points[i], vector_Y_Points[i], NULL);
			continue;
		}
		LineTo(_hdc, vector_X_Points[i], vector_Y_Points[i]);
	}
}
void multiplication_matrix(int number_operation) {
	switch (number_operation)
	{
	case 0:
	{
		for (int i = 0; i < vector_X_Points.size(); i++) {
			float temp_ORIG_Matrix[1][3] = { {vector_X_Points[i], vector_Y_Points[i], 1} };
			float result_Matrix[1][3] = { {0.0f, 0.0f, 0.0f} };

			for (int i = 0; i < 3; ++i) { // перебираем столбцы второй матрицы
				for (int k = 0; k < 3; ++k) { // перебираем элементы строки первой матрицы и столбца второй
					result_Matrix[0][i] += temp_ORIG_Matrix[0][k] * move_matrix[k][i];
				}
			}
			vector_X_Points[i] = static_cast<int>(round(result_Matrix[0][0]));
			vector_Y_Points[i] = static_cast<int>(round(result_Matrix[0][1]));
		}
		break;
	}
	case 1:
	{
		for (int i = 0; i < vector_X_Points.size(); i++) {
			float temp_ORIG_Matrix[1][3] = { {vector_X_Points[i], vector_Y_Points[i], 1} };
			float result_Matrix[1][3] = { {0.0f, 0.0f, 0.0f} };

			for (int i = 0; i < 3; ++i) { // перебираем столбцы второй матрицы
				for (int k = 0; k < 3; ++k) { // перебираем элементы строки первой матрицы и столбца второй
					result_Matrix[0][i] += temp_ORIG_Matrix[0][k] * decrease_matrix[k][i];
				}
			}
			vector_X_Points[i] = static_cast<int>(round(result_Matrix[0][0]));
			vector_Y_Points[i] = static_cast<int>(round(result_Matrix[0][1]));
		}
		break;
	}
	case 2:
		for (int i = 0; i < vector_X_Points.size(); i++) {
			float temp_ORIG_Matrix[1][3] = { {vector_X_Points[i], vector_Y_Points[i], 1} };
			float result_Matrix[1][3] = { {0.0f, 0.0f, 0.0f} };

			for (int i = 0; i < 3; ++i) { // перебираем столбцы второй матрицы
				for (int k = 0; k < 3; ++k) { // перебираем элементы строки первой матрицы и столбца второй
					result_Matrix[0][i] += temp_ORIG_Matrix[0][k] * mapping_matrix[k][i];
				}
			}
			vector_X_Points[i] = static_cast<int>(round(result_Matrix[0][0]));
			vector_Y_Points[i] = static_cast<int>(round(result_Matrix[0][1]));
		}
	default:
		break;
	}
}
void mapping_X_Y_with_shift(int number_operation) {
	// Шаг 1: Найдём минимальные координаты фигуры
	float min_X = *min_element(vector_X_Points.begin(), vector_X_Points.end());
	float min_Y = *min_element(vector_Y_Points.begin(), vector_Y_Points.end());

	// Переносим фигуру в начало экрана (0,0)
	for (size_t i = 0; i < vector_X_Points.size(); i++) {
		vector_X_Points[i] -= min_X;
		vector_Y_Points[i] -= min_Y;
	}

	// Шаг 2: Отражаем относительно прямой x = y
	multiplication_matrix(number_operation);

	// Шаг 3: Переносим фигуру обратно на исходное место
	for (size_t i = 0; i < vector_X_Points.size(); i++) {
		vector_X_Points[i] += min_Y;
		vector_Y_Points[i] += min_X;
	}
}
void operations_matrix(int number_operation, float num, float num_1) {
	switch (number_operation)
	{
	case 0:
		{
			move_matrix[2][0] = num;
			move_matrix[2][1] = num_1;
			multiplication_matrix(number_operation);
			break;
		}
	case 1:
		{
			decrease_matrix[0][0] = num;
			decrease_matrix[1][1] = num;
			multiplication_matrix(number_operation);
			break;
		}
	case 2:
		{
			//mapping_matrix[0][0] = -1;
			mapping_X_Y_with_shift(number_operation);
			break;
		}
	default:
		break;
	}
}
