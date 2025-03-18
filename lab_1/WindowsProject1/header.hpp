#pragma once

#include "framework.h"
#include <vector>
#include <chrono>
#include <thread>
#include <math.h>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

vector <int> vector_X_Points = { 100, 150, 150, 50,  50, 100, 50,  10,  10,  50,  150, 190, 190, 150};
vector <int> vector_Y_Points = { 0,   50 , 550, 550, 50, 0,   500, 600, 400, 500, 500, 600, 400, 500};

void movements_images(int _X_movements, int _Y_movements) {
	for (int i = 0; i < vector_X_Points.size(); i++) { vector_X_Points[i] = vector_X_Points[i] + _X_movements; }
	for (int i = 0; i < vector_X_Points.size(); i++) { vector_Y_Points[i] = vector_Y_Points[i] - _Y_movements; }
}
void decrease_images(int ratio) {
	for (int i = 0; i < vector_X_Points.size(); i++) {
		vector_X_Points[i] = vector_X_Points[i] / ratio; 
	}
	for (int i = 0; i < vector_X_Points.size(); i++) {
		vector_Y_Points[i] = vector_Y_Points[i] / ratio;
	}
}
void mapping_X_Y() {
	vector <int> temp_vector = vector_X_Points;
	for (int i = 0; i < vector_X_Points.size(); i++) {
		vector_X_Points[i] = vector_Y_Points[i];
		vector_Y_Points[i] = temp_vector[i];
	}
}
void sleep_wiev_images() {
	sleep_for(nanoseconds(10));
	sleep_until(system_clock::now() + seconds(3));
}
int get_figure_length() {
	int min_X = *min_element(vector_X_Points.begin(), vector_X_Points.end());
	int max_X = *max_element(vector_X_Points.begin(), vector_X_Points.end());
	return abs(max_X - min_X);
}

int get_figure_height() {
	int min_Y = *min_element(vector_Y_Points.begin(), vector_Y_Points.end());
	int max_Y = *max_element(vector_Y_Points.begin(), vector_Y_Points.end());
	return abs(max_Y - min_Y);
}
// shows pattern:
/*MoveToEx(hdc, 100, 0, NULL);
		   LineTo(hdc, 150, 50);
		   LineTo(hdc, 150, 550);
		   LineTo(hdc, 50, 550);
		   LineTo(hdc, 50, 50);
		   LineTo(hdc, 100, 0);
		   MoveToEx(hdc, 50, 500, NULL);
		   LineTo(hdc, 10, 600);
		   LineTo(hdc, 10, 400);
		   LineTo(hdc, 50, 500);
		   MoveToEx(hdc, 150, 500, NULL);
		   LineTo(hdc, 190, 600);
		   LineTo(hdc, 190, 400);
		   LineTo(hdc, 150, 500);
*/
// Отражение относительно прямой x=y с переносом в начало координат и обратно
void mapping_X_Y_with_shift() {
	// Шаг 1: Найдём минимальные координаты фигуры
	int min_X = *min_element(vector_X_Points.begin(), vector_X_Points.end());
	int min_Y = *min_element(vector_Y_Points.begin(), vector_Y_Points.end());

	// Переносим фигуру в начало экрана (0,0)
	for (size_t i = 0; i < vector_X_Points.size(); i++) {
		vector_X_Points[i] -= min_X;
		vector_Y_Points[i] -= min_Y;
	}

	// Шаг 2: Отражаем относительно прямой x = y
	for (size_t i = 0; i < vector_X_Points.size(); i++) {
		swap(vector_X_Points[i], vector_Y_Points[i]);
	}

	// Шаг 3: Переносим фигуру обратно на исходное место
	for (size_t i = 0; i < vector_X_Points.size(); i++) {
		vector_X_Points[i] += min_Y;
		vector_Y_Points[i] += min_X;
	}
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

