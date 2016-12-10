#include "classes.hpp"
#ifndef CAMERA_H
#define CAMERA_H

class camera{
	public:
		double fov;
		Point C;
		Ray createRay(int i, int j);
		int width;
		int height;
};



#endif
