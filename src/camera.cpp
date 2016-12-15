#include "camera.hpp"
#include <cmath>

Camera::Camera(double fov, Point C, int width, int height,int maxIter) : fov(fov),C(C),width(width),height(height),maxIter(maxIter){
}

Ray Camera::createRay(int i, int j){
	Vector direct = Vector(0.5 + j-((double) width)/2, 0.5+ i- ((double) height)/2, -((double) height)/(2*tan(fov/2)));
	direct.normalize();
	return Ray(C,direct);
}

void Camera::render(Scene& scene, Image& image){
for (int i = 0; i< width; i++){
	for(int j = 0; j < height; j++){
		Ray ray = createRay(i,j);
		Color pixelColor = scene.getColor(ray,maxIter);
		image.setRGB(i,j,pixelColor);


	}
}

}
