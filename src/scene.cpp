#include "scene.hpp"
#include <iostream>
#include <cmath>
#include <random>

std::default_random_engine engine;
std::uniform_real_distribution<double> distrib(0,1);



using namespace std;

Scene::Scene(vector<Sphere> spheres,Point L,double nair) : spheres(spheres), L(L),nair(nair){
}

Intersection Scene::intersection(Ray ray){
	Point P;
	Sphere* sphere;
	Intersection inter = Intersection(false,P,sphere,false); 
	for(Sphere& i:spheres){
		Intersection inter2 = i.intersection(ray);
		inter = minI(inter,inter2,ray);
	}
	return inter;
}


Ray Scene::reflect(Ray r, Sphere* sphere, Point p){
	Vector v = r.direction;
	Vector res = v - sphere->normal(p)*v.dotProduct(sphere->normal(p))*2;
	return Ray(p,res);

}

Ray Scene::refract(Ray r, Sphere* sphere, Point p, bool inout){
	double nin = nair;
	double nout = sphere->mat.nmat;
	if (!inout)
		std::swap(nin,nout);
	double frac = nin/nout;
	Vector i = r.direction;
	Vector n = sphere->normal(p);
	double dotP = i.dotProduct(n);
	double testRefract =  1.-frac*frac*(1.-dotP*dotP);
	if(testRefract<0){
		return reflect(r, sphere, p);
	}else{
		Vector v = i*frac - n * (frac*dotP + sqrt(testRefract));
		Point np = sphere->correct(p);
		v.normalize();
		return Ray(np,v);
	}

}


Color Scene::getColor(Ray ray,int maxIter, int nsample){
Intersection intersectionScene = intersection(ray);
Color result(0,0,0);
if (intersectionScene.notEmpty){
	Sphere* spherei = intersectionScene.sphere;
	Vector l = L - intersectionScene.intersectionPoint;
	int d = l.normSquared();
	Point interpoint = intersectionScene.intersectionPoint;
	l.normalize();
	Ray rayl = Ray(intersectionScene.intersectionPoint,l);
	Intersection intersectionl =intersection(rayl);
	Vector dist = intersectionl.intersectionPoint - interpoint;
	double difffrac = 1.;
	if (intersectionl.notEmpty && dist.normSquared() < d){
		difffrac = 0.;
	}
	Vector n = spherei->normal(intersectionScene.intersectionPoint);
	double intensity = 1500*max(0.,l.dotProduct(n))*difffrac/d;
	if(maxIter > 0 && spherei->mat.isspec){
		Ray v = reflect(ray,spherei,interpoint);
		Intersection intersectionColor = intersection(v);
			result=getColor(v,maxIter-1,nsample);
			double specf = spherei->mat.specfrac;
			Color diffcolor = spherei->mat.diff*intensity*(1.-specf);
			result = result * specf;
			result =  diffcolor + result;

	} else{
		if(maxIter > 0 && spherei->mat.istrans){
			Ray r = refract(ray,spherei,interpoint,intersectionScene.inout);
			Intersection intersectionColor = intersection(r);
			result=getColor(r,maxIter-1, nsample);


		} else {
			result = spherei->mat.diff*intensity;
			if (nsample != 0 && maxIter>0) {
				Color c = getColorBRDF(intersectionScene.intersectionPoint,spherei->normal(intersectionScene.intersectionPoint),maxIter,nsample);
				Color diff = spherei->mat.diff;
				c.red = c.red * diff.red;
				c.green = c.green * diff.green;
				c.blue = c.blue * diff.blue;
				result = result + c;
			}
		}
	}
}
return result;

}




Color Scene::getColorBRDF(Point P, Vector n, int maxIter, int nsample){
	Color result(0,0,0);
	Vector i = n.orthogonal();
	Vector j = n.crossProduct(i);
	double pi = 3.14156535;
	for (int k = 0; k<nsample;k++){
		double r1 = distrib(engine);
		double r2 = distrib(engine);
		Vector v = i*cos(2*pi*r1)*sqrt(1-r2) + j*sin(2*pi*r1)*sqrt(1-r2) + n*sqrt(r2);
		v.normalize();
		result = result + getColor(Ray(P,v),maxIter-1,1);

	}
	return result*(1/(pi*nsample));

}


