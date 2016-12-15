#include "scene.hpp"

using namespace std;

Scene::Scene(vector<Sphere> spheres,Point L) : spheres(spheres), L(L){
}

Intersection Scene::intersection(Ray ray){
	Point P;
	Sphere* sphere;
	Intersection inter = Intersection(false,P,sphere); 
	for(Sphere& i:spheres){
		Intersection inter2 = i.intersection(ray);
		inter = minI(inter,inter2,ray);
	}
	return inter;
}


Ray Scene::reflect(Ray r, Sphere* sphere, Point p){
	Vector v = r.direction;
	Vector res = v - sphere->normal(p)*v.dotProduct(sphere->normal(p))*2;
	return Ray(p,v);

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
	if (intersectionl.notEmpty && dist.normSquared() < d)
		return result;
	Vector n = spherei->normal(intersectionScene.intersectionPoint);
	double intensity = 800*max(0.,l.dotProduct(n))/d;
	if(maxIter>0 && spherei->mat.isspec){
		Ray v = reflect(ray,spherei,interpoint);
		Intersection intersectionColor = intersection(v);
		if (intersectionColor.notEmpty){
			result=getColor(v,maxIter-1);
			result.red = result.red*spherei->mat.spec.red/255;
			result.blue = result.blue*spherei->mat.spec.blue/255;
			result.green = result.green *spherei->mat.spec.green/255;
		}

	} else {
		result.red = spherei->mat.diff.red*intensity;
		result.green = spherei->mat.diff.green*intensity;
		result.blue = spherei->mat.diff.blue*intensity;
	}
}
return result;

}
