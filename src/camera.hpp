#include "classes.hpp"
#include "scene.hpp"
#ifndef CAMERA_H
#define CAMERA_H

class Camera{
	public:
		Camera(double fov,Point C,int width, int height, int maxIter, int nsample, bool AA);
		double fov;
		Point C;
		Ray createRay(int i, int j,double di, double dj);
		void render(Scene& scene, Image& image);
		bool AA;
		int nsample;
		int width;
		int height;
		int maxIter;
};



#endif
