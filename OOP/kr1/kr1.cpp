#include <iostream>
#include <cmath>
#include <ctime>

class Point {
	float x;
	float y;

public:
	Point(float x, float y) {
		this->x = x;
		this->y = y;
	}

	Point(Point& p) {
		this->x = p.x;
		this->y = p.y;
	}

	Point() {
		this->x = 0;
		this->y = 0;
	}

	float get_x(){
		return x;
	}

	float get_y(){
		return y;
	}

	void set_x(float x) {
		this->x = x;
	}

	void set_y(float y) {
		this->y = y;
	}

	void print() {
		std::cout << "Point: " << this->x << ", " << this->y << "\n";
	}
};

class Circle {
	Point center;
	float radius;
	
public:
	Circle(Point& center, float radius) {
		this->center = center;
		this->radius = radius;
	}

	Circle() {
		Point zero(0, 0);
		this->center = zero;
		this->radius = 0;
	}
	
	Circle(Circle& cir) {
		this->center = cir.center;
		this->radius = cir.radius;
	}

	Point& get_center() {
		Point extraPoint(center);
		return extraPoint;
	}

	float get_radius() {
		return radius;
	}

	void set_center(Point& center) {
		this->center = center;
	}

	void set_radius(float radius) {
		if (radius > 0) {
			this->radius = radius;
		}
	}

	void set_random() {
		Point p(rand() % 10 - 5, rand() % 10 - 5);
		this->center = p;
		this->radius = rand() % 10 - 5;
	}

	void print() {
		std::cout << "Circle: Center:" << "\n";
		this->center.print();
		std::cout << "Radius: " << this->radius << "\n";
	}

	bool is_on_axes() {
		return center.get_x() == 0 || center.get_y() == 0;
	}

	static Circle* all_on_axes(Circle* array, int n) {
		int count_on_axes = 0;
		for (int i = 0; i < n; i++) {
			if (array[i].is_on_axes()) {
				count_on_axes++;
			}
		}
		Circle* ans_array = new Circle[n];
		count_on_axes = 0;
		for (int i = 0; i < n; i++) {
			if (array[i].is_on_axes()) {
				ans_array[count_on_axes] = array[i];
				count_on_axes++;
			}
		}

		return ans_array;
	}
};

bool is_inside(Point& p, Circle& cir) {
	float dx = p.get_x() - cir.get_center().get_x();
	float dy = p.get_y() - cir.get_center().get_y();
	float r = sqrt(dx * dx + dy * dy);
	return r <= cir.get_radius();
}

int main() {
	srand(time(NULL));
	Circle circles_static[5];
	Circle* circles_dynamic = new Circle[5];
	for (int i = 0; i < 5; i++) {
		circles_dynamic[i].set_random();
		circles_static[i].set_random();
	}
	std::cout << "Is on axes: " << "\n";
	for (int i = 0; i < 5; i++) {
		if (circles_dynamic[i].is_on_axes()) {
			circles_dynamic[i].print();
			std::cout << "\n";
		}
		if (circles_static[i].is_on_axes()) {
			circles_static[i].print();
			std::cout << "\n";
		}
	}

	std::cout << "\n";
	Point p;
	p.set_x(rand() % 10 - 5);
	p.set_y(rand() % 10 - 5);
	p.print();
	std::cout << "Inside it: \n";
	bool found_static = false, found_dynamic=false;
	for (int i = 0; i < 5; i++) {
		if (is_inside(p, circles_dynamic[i])) {
			circles_dynamic[i].print();
			std::cout << "\n";
			found_dynamic = true;
		}
		if (is_inside(p, circles_static[i])) {
			circles_static[i].print();
			std::cout << "\n";
			found_static = true;
		}
	}
	if (!found_dynamic) {
		std::cout << "Not found in dynamic \n";
	}
	if (!found_static) {
		std::cout << "Nor found in static \n";
	}
	delete[] circles_dynamic;
}