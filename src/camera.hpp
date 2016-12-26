#include "classes.hpp"
#include "scene.hpp"
#ifndef CAMERA_H
#define CAMERA_H

class Camera{
	public:
		Camera(double fov,Point C,int width, int height, int maxIter, int nsample);
		double fov;
		Point C;
		Ray createRay(int i, int j);
		void render(Scene& scene, Image& image);
		int nsample;
		int width;
		int height;
		int maxIter;
};



#endif
