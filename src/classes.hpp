#ifndef CLASSES_H
#define CLASSES_H

class Vector{
	public:
		Vector(double valx = 0, double valy = 0, double valz = 0);
		Vector operator+(const Vector& v);
		Vector operator-(const Vector& v);
		Vector operator-();
		Vector operator*(double a);
		Vector crossproduct(const Vector& v);
		double dotproduct(const Vector& v);
		double x;
		double y;
		double z;

};

typedef Vector Point;

class Sphere{
	public:
		Point origine;
		double radius;

};

class Ray{
	public:
		Point origin;
		Vector direction;
};


#endif
