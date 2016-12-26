#pragma once
#include <vector>
#include "classes.hpp"



using namespace std;


class Scene{
	public:
		Scene(vector<Sphere> spheres,Point L,double nair);
		Point L;
		double nair;
		int nsample;
		vector<Sphere> spheres;
		Intersection intersection(Ray ray);
		Ray reflect(Ray r, Sphere* sphere, Point p);
		Color getColor(Ray ray, int maxIter, int nsample);
		Color getColorBRDF(Point p, Vector n, int maxIter, int nsample);
		Ray refract(Ray r, Sphere* sphere, Point p,bool inout);
};
