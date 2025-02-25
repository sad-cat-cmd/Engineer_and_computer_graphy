#pragma once

#include "framework.h"
#include <vector>

using namespace std;

vector <int> vector_X_Points = { 100, 150, 150, 50,  50, 100, 50,  10,  10,  50,  150, 190, 190, 150};
vector <int> vector_Y_Points = { 0,   50 , 550, 550, 50, 0,   500, 600, 400, 500, 500, 600, 400, 500};

void movements_images(int _X_movements, int _Y_movements) {
	for (int i = 0; i < vector_X_Points.size(); i++) { vector_X_Points[i] = vector_X_Points[i] + _X_movements; }
	for (int i = 0; i < vector_X_Points.size(); i++) { vector_Y_Points[i] = vector_Y_Points[i] - _Y_movements; }
}
void decrease_images(int ratio) {
	for (int i = 0; i < vector_X_Points.size(); i++) { vector_X_Points[i] = vector_X_Points[i] / ratio; }
	for (int i = 0; i < vector_X_Points.size(); i++) { vector_Y_Points[i] = vector_Y_Points[i] / ratio; }
}
void mapping_X_Y() {
	vector <int> temp_vector = vector_X_Points;
	for (int i = 0; i < vector_X_Points.size(); i++) {
		vector_X_Points[i] = vector_Y_Points[i];
		vector_Y_Points[i] = temp_vector[i];
	}
}

// shows pattern: <3
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

void show_images(HDC _hdc) {
	for (int i = 0; i < vector_X_Points.size(); i++) {
		if (i == 0 || i == 6 || i == 10) {
			MoveToEx(_hdc, vector_X_Points[i], vector_Y_Points[i], NULL);
			continue;
		}
		LineTo(_hdc, vector_X_Points[i], vector_Y_Points[i]);
	}
}