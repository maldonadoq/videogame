#include "../inc/random.h"

int RandomInt(int _a, int _b){
	return (rand()%(_b - _a)) + _a;
}

glm::vec3 RandomPosition(int _x, int _y, int _z){	
	return glm::vec3(RandomInt(-_x,_x), _y, RandomInt(-_z,_z));
}

float Random(){
	return (float)rand()/(float)RAND_MAX;
}

glm::vec3 RandomVect(){
	float x = (Random()*2.0f)-1;
	float y = 0;
	float z = (Random()*2.0f)-1;

	return glm::normalize(glm::vec3(x,y,z));
}

glm::vec3 RandomUnitVect(){
	float x = (Random()*2.0f)-1;
	float y = (Random()*2.0f)-1;
	float z = (Random()*2.0f)-1;

	return glm::normalize(glm::vec3(x,y,z));
}

glm::vec3 RandomColor(){
	return glm::vec3(Random(), Random(), Random());
}

float RandomBeetwen(float a, float b){
	float rnd = Random();
	float diff = b-a;
	return (rnd*diff) + a;
}