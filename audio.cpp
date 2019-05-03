#include <SFML/Audio.hpp>

// g++ audio.cpp -o audio.out -lsfml-system -lsfml-audio
int main(int argc, char const *argv[]){
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("data/audio/explosion.wav"))
        return -1;

    sf::Sound sound;
	sound.setBuffer(buffer);

	sound.play();

	sf::sleep(sf::seconds(2));
    return 0;
}