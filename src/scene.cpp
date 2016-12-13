#include "scene.hpp"
#include "classes.hpp"

using namespace std;

Scene::Scene(vector<Sphere> spheres) : spheres(spheres){
}

Intersection Scene::intersection(Ray ray){
	Point P;
	Sphere* sphere;
	Intersection inter = Intersection(false,P,sphere); 
	for(Sphere& i:spheres){
		inter = minI(inter,i.intersection(ray),ray);
	}
	return inter;
}


Ray Scene.reflect(Ray r, Sphere sphere, Point p){
	Vector v = r.direction;
	Vector res = v - sphere.normal(p)*v.dotproduct(sphere.normal(p))*2;
	Return Ray(p,v);

}
