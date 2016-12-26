#include "scene.hpp"
#include <iostream>
#include <cmath>


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

Color Scene::getColor(Ray ray,int maxIter){
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
	double intensity = 600*max(0.,l.dotProduct(n))*difffrac/d;
	if(maxIter > 0 && spherei->mat.isspec){
		Ray v = reflect(ray,spherei,interpoint);
		Intersection intersectionColor = intersection(v);
			result=getColor(v,maxIter-1);
			double specf = spherei->mat.specfrac;
			result.red =specf*result.red +(1.-specf)*spherei->mat.diff.red* intensity;
			result.blue = specf*result.blue + (1.-specf)*spherei->mat.diff.blue*intensity;
			result.green = specf*result.green + (1.-specf)*spherei->mat.diff.green*intensity;

	} else{
		if(maxIter > 0 && spherei->mat.istrans){
			Ray r = refract(ray,spherei,interpoint,intersectionScene.inout);
			Intersection intersectionColor = intersection(r);
			result=getColor(r,maxIter-1);


		} else {
			result.red = spherei->mat.diff.red * intensity;
			result.green = spherei->mat.diff.green * intensity;
			result.blue = spherei->mat.diff.blue * intensity;
		}
	}
}
return result;

}
