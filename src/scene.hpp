#pragma once
#include <vector>
#include "classes.hpp"



using namespace std;


class Scene{
	public:
		Scene(vector<Sphere> spheres,Point L,double nair);
		Point L;
		double nair;
		vector<Sphere> spheres;
		Intersection intersection(Ray ray);
		Ray reflect(Ray r, Sphere* sphere, Point p);
		Color getColor(Ray ray, int maxIter);
		Ray refract(Ray r, Sphere* sphere, Point p,bool inout);
};
