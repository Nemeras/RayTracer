#include "camera.hpp"
#include <cmath>
#include <stdlib.h>


Camera::Camera(double fov, Point C, int width, int height,int maxIter, int nsample, bool AA) : fov(fov),C(C),width(width),height(height),maxIter(maxIter),nsample(nsample),AA(AA){
}

Ray Camera::createRay(int i, int j, double u, double v){
	Vector direct = Vector(0.5 + j + v -((double) width)/2, 0.5+ i+u- ((double) height)/2, -((double) height)/(2*tan(fov/2)));
	direct.normalize();
	return Ray(C,direct);
}


void Camera::render(Scene& scene, Image& image){
#pragma omp parallel for schedule(dynamic,1)
for (int i = 0; i< height; i++){
	for(int j = 0; j < width; j++){
		Color pixelColor(0,0,0);
		if(AA && nsample > 0){
			for (int k = 0; k < nsample; k++){
				double x = drand48();
				double y = drand48();
				double R=sqrt(-2*log(x));
				double u =  R*cos(2*3.1416*y)*0.5;
				double v =  R*sin(2*3.1416*y)*0.5;
	
				Ray ray = createRay(i,j,u,v);
				//Color pixelColor = scene.getColor(ray,maxIter,nsample);
				pixelColor =pixelColor+ scene.getColor(ray,maxIter,1);
			}
			pixelColor = pixelColor/nsample;
		} else  {
			Ray ray = createRay(i,j,0.,0.);
			pixelColor = scene.getColor(ray,maxIter,nsample);
		
		}
		image.setRGB(i,j,pixelColor);
		
	}
}

}
