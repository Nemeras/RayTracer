#include "classes.hpp"
#ifndef CAMERA_H
#define CAMERA_H

class Camera{
	public:
		Camera(double fov,Point C,int width, int height);
		double fov;
		Point C;
		Ray createRay(int i, int j);
		int width;
		int height;
};



#endif
