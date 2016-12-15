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
	return Vector(-x,-y-z);
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

Color::Color(int red, int green, int blue) : red(red), green(green), blue(blue){
}


Ray::Ray(Point orig,Vector dir) : origin(orig),direction(dir){
}


Material::Material(Color diff, Color spec, bool isspec) : diff(diff), spec(spec), isspec(isspec){
}


Sphere::Sphere(Point origin, double radius,Material mat,int id) : origin(origin),radius(radius),mat(mat),id(id){
}

Intersection::Intersection(bool b,Point p, Sphere* sphere) : notEmpty(b),intersectionPoint(p),sphere(sphere){
}

Intersection Sphere::intersection(Ray& ray){
	Vector v = ray.origin - origin;
	double b =  2*ray.direction.dotProduct(v);
	double c = v.normSquared() - radius*radius;
	double delta = b*b - 4*c;
	bool notEmpty = delta >= 0; 
	Point P;
	if (notEmpty){
		double t = (-b-sqrt(delta))/2;
		if (t < 0){
			t = (-b+sqrt(delta))/2;
			if(t < 0)
				return Intersection(false,P,this);
		}
		P = ray.origin + ray.direction*0.999*t;
	}
	return Intersection(notEmpty,P,this);
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
pixels[((height-i-1)*width+j)] = color.red;
pixels[((height-i-1)*width+j) + width*height] = color.green;
pixels[((height-i-1)*width+j) + 2*width*height] = color.blue;
}


/*Color Sphere::getColor(Ray ray, int n, Scene scene, Point interpoint){
	Color result(0,0,0);
	if (n>0 && isspec){
		Vector v = Scene.reflect(ray, sphere,interpoint);
		Intersection intersection = Scene.intersection(Ray(interpoint,v);
		if (intersection.notEmpty)
			result = intersection.sphere->getColor(scene.reflect(ray, scene),n-1, scene, intersection);
	}
	
	result.red = result.red * Mat.spec.red/255;
	result.blue = result.blue * Mat.spec.blue/255;
	result.green = result.green * Mat.spec.green/255;
	
	result.red = 0.8*result.red + 0.2*Mat.diff.red;
	result.blue = 0.8*result.blue + 0.2*Mat.diff.blue;
	result.green = 0.8*result.green + 0.2*Mat.diff.green;
}*/
