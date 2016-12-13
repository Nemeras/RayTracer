#include <vector>
#include "classes.hpp"


using namespace std;


class Scene{
	public:
		Scene(vector<Sphere> spheres);
		vector<Sphere> spheres;
		Intersection intersection(Ray ray);
};

Ray Scene::reflect(ray r,Sphere sphere, Point p);
