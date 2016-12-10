#include "camera.hpp"
#include <cmath>

Ray camera::createRay(int i, int j){
	Vector direct = Vector(0.5 + j-((double) width)/2, 0.5+ i- ((double) height)/2, -((double) height)/(2*tan(fov/2)));
}
