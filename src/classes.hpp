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
		Color(int red, int green, int blue);
		int red;
		int green;
		int blue;

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
		Material(Color diff, Color spec, bool isspec);
		Color diff;
		Color spec;
		bool isspec;

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
//		Color getColor(Ray ray, int n, Scene scene, Point interpoint);

};

class Intersection{
	public:
		Intersection(bool b, Point p,Sphere* sphere);
		bool notEmpty;
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
