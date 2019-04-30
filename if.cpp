#include <iostream>
#include <glm/glm.hpp>

void print_vec(glm::vec3 _v){
	std::cout << "[" << _v.x << "," << _v.y << "," << _v.z << "]\n";
}

int main(int argc, char const *argv[]){
	
	float t = 0.0;

	if(t){
		std::cout << "accept\n";
	}
	else{
		std::cout << "no accept\n";
	}

	glm::vec3 a(1,2,3);
	glm::vec3 b(12,6,4);

	print_vec(a);
	print_vec(b);

	std::cout << "\n\n";

	print_vec(a+b);
	print_vec(a*b);

	return 0;
}