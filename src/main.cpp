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
	Point center5(1000,0,0);
	Point center6(-1000,0,0);
	Color black(0,0,0);
	Color white(255,255,255);
	Color blue(0,0,255);
	Color red(255,0,0);
	Color pink(255,105,180);
	Color green(0,255,0);
	Sphere sphere2(center,990,Material(blue,white,false,false,1.,0.8),2);
	Sphere sphere3(center2,940,Material(red,white,false,false,1.,0.8),3);
	Sphere sphere4(center3,940,Material(pink,white,false,false,1.,0.8),4);
	Sphere sphere5(center4,940,Material(green,white,false,false,1.,0.8),5);
	Sphere sphere6(center5,940,Material(white,white,true,false,1.,0.8),6);
	Sphere sphere7(center6,940,Material(white,white,true,false,1.,0.8),7);
	Sphere sphere(O,10,Material(white,white,true,false,1.7,0.8),1);
	double fov = 50;
	fov = fov * 0.0174533;
	int width = 1920;
	int height = 1080;
	Camera camera(fov,C,width,height,8);
	
	Image image(width,height);

	vector<Sphere> vectorscene = {sphere,sphere2,sphere3,sphere4,sphere5,sphere6,sphere7};
//	vector<Sphere> vectorscene = {sphere,sphere2};
//	vector<Sphere> vectorscene = {sphere};
	Scene scene(vectorscene,L,1.);
	camera.render(scene,image);

	cimg_library::CImg<unsigned char> cimg(&image.pixels[0], width, height, 1, 3);	
	cimg.save("fichier.bmp");
	return 0;
}
