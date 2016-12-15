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
//	Sphere sphere5(center4,940,green,5)²;
	Sphere sphere(O,10,Material(white,white,false),1);
	double fov = 60;
	fov = fov * 0.0174533;
	int width = 500;
	int height = 500;
	Camera camera(fov,C,width,height,5);
	
	Image image(width,height);

//	vector<Sphere> vectorscene = {sphere,sphere2,sphere3,sphere4,sphere5};
	vector<Sphere> vectorscene = {sphere,sphere2};
//	vector<Sphere> vectorscene = {sphere};
	Scene scene(vectorscene,L);
	camera.render(scene,image);

	cimg_library::CImg<unsigned char> cimg(&image.pixels[0], width, height, 1, 3);	
	cimg.save("fichier.bmp");
	return 0;
}
