#include <vector>
#include <cmath>
#ifndef CLASSES_H
#define CLASSES_H

class Vector{
	public:
		Vector(double valx = 0, double valy = 0, double valz = 0);
		Vector operator+(const Vector& v);
		Vector operator-(const Vector& v);
		Vector operator-();
		Vector operator*(double a);
		Vector crossProduct(const Vector& v);
		void normalize();
		double norm();
		double normSquared();
		double dotProduct(const Vector& v);
		double x;
		double y;
		double z;

};


class Color{
	public:
		Color(int redint, int greenint, int blueint);
		double red;
		double green;
		double blue;
		void gammaCorrection();

};

typedef Vector Point;

class Ray{
	public:
		Ray(Point orig,Vector dir);
		Point origin;
		Vector direction;


};

class Intersection;

class Material{
	public:
		Material(Color diff, Color spec, bool isspec,bool istrans, double nmat, double specfrac);
		Color diff;
		Color spec;
		bool istrans;
		bool isspec;
		double nmat;
		double specfrac;

};


class Sphere{
	public:
		Sphere(Point origin,double radius,Material mat, int id);
		int id;
		Material mat;
		Point origin;
		double radius;
		Intersection intersection(Ray& ray);
		Vector normal(Point& P);
		Point correct(Point p);

};

class Intersection{
	public:
		Intersection(bool b, Point p,Sphere* sphere,bool inout);
		bool notEmpty;
		bool inout;
		Point intersectionPoint;
		Sphere* sphere;

};

Intersection& minI(Intersection& i1, Intersection& i2, Ray& ray);

class Image{
	public:
		int width;
		int height;
		std::vector<unsigned char> pixels;
		Image(int width, int height);
		void setRGB(int i, int j, Color color);

};


#endif
