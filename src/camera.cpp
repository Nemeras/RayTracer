#include "camera.hpp"
#include <cmath>

Camera::Camera(double fov, Point C, int width, int height) : fov(fov),C(C),width(width),height(height){
}

Ray Camera::createRay(int i, int j){
	Vector direct = Vector(0.5 + j-((double) width)/2, 0.5+ i- ((double) height)/2, -((double) height)/(2*tan(fov/2)));
	direct.normalize();
	return Ray(C,direct);
}
