#include "../inc/random.h"

int RandomInt(int _a, int _b){
	return (rand()%(_b - _a)) + _a;
}

glm::vec3 RandomPosition(int _x, int _y, int _z){	
	return glm::vec3(RandomInt(0,_x), _y, RandomInt(0,_z));
}