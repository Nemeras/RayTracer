#include "classes.hpp"
#include <iostream>
#include <cmath>


Vector::Vector(double valx, double valy,double valz) : x(valx),y(valy),z(valz){
}

Vector Vector::operator+(const Vector& v) {
	return Vector(x+v.x,y+v.y,z+v.z);
}

Vector Vector::operator-(const Vector& v) {
	return Vector(x-v.x,y-v.y,z-v.z);
}

Vector Vector::operator-(){
	return Vector(-x,-y,-z);
}

Vector Vector::operator*(double a){
	return Vector(a*x,a*y,a*z);
}

Vector Vector::crossProduct(const Vector& v){
	return Vector(y*v.z-z*v.y,z*v.x-x*v.z,x*v.y-y*v.x);
}

double Vector::dotProduct(const Vector& v){
	return x*v.x+y*v.y+z*v.z;
}

double Vector::normSquared(){
	return x*x+y*y +z*z;
}

double Vector::norm(){
	return sqrt(x*x+y*y+z*z);
}



void Vector::normalize(){
	double n = norm();
	x=x/n;
	y=y/n;
	z=z/n;
}

Color::Color(int redint, int greenint, int blueint) : red(redint/255.), green(greenint/255.), blue(blueint/255.){
}

void Color::gammaCorrection(){
	red=pow(red,1/2.2);
	green=pow(green,1/2.2);
	blue=pow(blue,1/2.2);
}

Ray::Ray(Point orig,Vector dir) : origin(orig),direction(dir){
}


Material::Material(Color diff, Color spec, bool isspec, bool istrans, double nmat, double specfrac) : diff(diff), spec(spec), isspec(isspec),istrans(istrans),nmat(nmat),specfrac(specfrac){
}


Sphere::Sphere(Point origin, double radius,Material mat,int id) : origin(origin),radius(radius),mat(mat),id(id){
}

Intersection::Intersection(bool b,Point p, Sphere* sphere, bool inout) : notEmpty(b),intersectionPoint(p),sphere(sphere),inout(inout){
}

Intersection Sphere::intersection(Ray& ray){
	Vector v = ray.origin - origin;
	double b =  2*ray.direction.dotProduct(v);
	double c = v.normSquared() - radius*radius;
	double delta = b*b - 4*c;
	bool notEmpty = delta >= 0; 
	Point P;
	bool inout = c>0;
	if (notEmpty){
		double t = (-b-sqrt(delta))/2;
		if (t < 0){
			t = (-b+sqrt(delta))/2;
			if(t < 0)
				return Intersection(false,P,this,inout);
		}
		P = ray.origin + ray.direction*0.999*t;
	}
	return Intersection(notEmpty,P,this,inout);
}

Vector Sphere::normal(Point& P){
	Vector v = P - origin;
	if (v.normSquared() < radius*radius) {
		v.normalize();
		return -v;

	} else {
		v.normalize();
		return v;
	}
	
}



Intersection& minI(Intersection& i1, Intersection& i2, Ray& ray){
	if(!(i2.notEmpty)){
		return i1;
	}
	if(!(i1.notEmpty)){
		return i2;
	}
	Vector v1 = ray.origin-i1.intersectionPoint;
	Vector v2 = ray.origin-i2.intersectionPoint;
	if(v1.normSquared() < v2.normSquared()){
		return i1;
	} else {
		return i2;
	}
}


Image::Image(int width, int height): width(width), height(height), pixels(3*width*height){
}

void Image::setRGB(int i, int j, Color color){
	color.gammaCorrection();
	int redint = 256 * color.red;
	int blueint = 256 * color.blue;
	int greenint = 256 * color.green;
	pixels[((height-i-1)*width+j)] = std::min(255,redint);
	pixels[((height-i-1)*width+j) + width*height] = std::min(255,greenint);
	pixels[((height-i-1)*width+j) + 2*width*height] = std::min(255,blueint);
}


Point Sphere::correct(Point p){
	Vector v = p - origin;
	if (v.normSquared()>radius*radius){
		v.normalize();
		v = v*radius*0.999;
		return(v+origin);
	} else {
		v.normalize();
		v = v*radius*1.001;
		return(v+origin);
	}

}
