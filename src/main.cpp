#include <iostream>
#include "CImg.h"
#include "classes.hpp"

using namespace std;

int main(){
	Vector truc = Vector(0,0,0);
	Vector machin = Vector(1,1,1);
	truc = truc+machin;
	cout <<truc.z << endl;
	return 0;
}
