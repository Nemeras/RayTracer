#include "classes.hpp"

Vector::Vector(double valx, double valy,double valz) : x(valx),y(valy),z(valz){
}

Vector Vector::operator+(const Vector& v) {
	return Vector(x+v.x,y+v.y,z+v.z);
}

Vector Vector::operator-(const Vector& v) {
	return Vector(x-v.x,y-v.y,z-v.z);
}

Vector Vector::operator-(){
	return Vector(-x,-y-z);
}

Vector Vector::operator*(double a){
	return Vector(a*x,a*y,a*z);
}

Vector Vector::crossproduct(const Vector& v){
	return Vector(y*v.z-z*v.y,z*v.x-x*v.z,x*v.y-y*v.x);
}

double Vector::dotproduct(const Vector& v){
	return x*v.x+y*v.y+z*v.z;
}

