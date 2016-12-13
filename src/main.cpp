#include <iostream>
#include "CImg.h"
#include "classes.hpp"
#include "camera.hpp"
#include "scene.hpp"
#include <vector>
#include <cmath>

using namespace std;

int main(){
	Point O(0,0,0);
	Point O2(10,0,0);
	Point C(0,0,55);
	Point L(-10,20,40);
	Point center(0,-1000,0);
	Point center2(0,1000,0);
	Point center3(0,0,1000);
	Point center4(0,0,-1000);
	Color white(255,255,255);
	Color blue(0,0,255);
	Color red(255,0,0);
	Color pink(255,105,180);
	Color green(0,255,0);
	Sphere sphere2(center,990,Material(blue,white,false),2);
//	Sphere sphere3(center2,940,red,3);
//	Sphere sphere4(center3,940,pink,4);
//	Sphere sphere5(center4,940,green,5);
	Sphere sphere(O,10,Material(white,white,true),1);
	double fov = 60;
	fov = fov * 0.0174533;
	int width = 500;
	int height = 500;
	Camera camera(fov,C,width,height);
	
	Image image(width,height);

//	vector<Sphere> vectorscene = {sphere,sphere2,sphere3,sphere4,sphere5};
	vector<Sphere> vectorscene = {sphere,sphere2};
//	vector<Sphere> vectorscene = {sphere};
	Scene scene(vectorscene);
	for(int i = 0; i<width;i++){
		for(int j = 0; j < height; j++){
			Ray ray = camera.createRay(i,j);
			Intersection intersection = scene.intersection(ray);
			if (intersection.notEmpty){
				Sphere* spherei = intersection.sphere;
				Vector l = L - intersection.intersectionPoint;
				int d = l.normSquared();
				Point interpoint = intersection.intersectionPoint;
				l.normalize();	
				Ray ray2 = Ray(intersection.intersectionPoint,l);
				Intersection intersection2=scene.intersection(ray2);
				Vector dist = intersection2.intersectionPoint - interpoint;
				if(intersection2.notEmpty && (dist.normSquared() < d)){
					if (spherei->id ==1)
	//					cout << intersection2.sphere->id << spherei->id << " "<<intersection2.intersectionPoint.x<<" "<<intersection2.intersectionPoint.y <<" "<< intersection2.intersectionPoint.z << " " << interpoint.x << " " << interpoint.y << " " << interpoint.z << " " << l.x << " " << l.y << " " << l.z<< endl;
					image.setRGB(i,j,0,0,0);
				}else{
				Vector n =spherei->normal(intersection.intersectionPoint);
				double intensity = 800 * max(0.,l.dotProduct(n))/d;
				image.setRGB(i,j,spherei->mat.red*intensity,spherei->mat.green*intensity,spherei->mat.blue*intensity);
				}
			} else {
				image.setRGB(i,j,0,0,0);
			}
			

		}

	}
/*	Vector vectortest = O-C;
	vectortest.normalize();
	Ray raytest(C, vectortest);

	Intersection inter = scene.intersection(raytest);

	cout << inter.notEmpty << endl;

	Point interpoint2 = inter.intersectionPoint;

	Vector vectortest2 = L-interpoint2;
	vectortest2.normalize();

	Ray raytest2(interpoint2,vectortest2);

	Intersection inter2 = scene.intersection(raytest2);

	cout << inter2.notEmpty << endl;

	Point interpoint3 = inter2.intersectionPoint;
		
	cout << interpoint2.x << " " << interpoint2.y << " " << interpoint2.z << endl;	
	cout << interpoint3.x << " " << interpoint3.y << " " << interpoint3.z << endl;
	cout << vectortest2.x << " " << vectortest2.y << " " << vectortest2.z << endl;	*/


	cimg_library::CImg<unsigned char> cimg(&image.pixels[0], width, height, 1, 3);	
	cimg.save("fichier.bmp");
	return 0;
}
