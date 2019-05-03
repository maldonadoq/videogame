#ifndef _AUDIO_H_
#define _AUDIO_H_

#include <SFML/Audio.hpp>

class TAudio{
private:
	std::vector<sf::SoundBuffer> m_buffers;
	sf::Sound audio;
public:
	TAudio(){
		m_buffers.resize(2),
		m_buffers[0].loadFromFile("data/audio/explosion.wav");
		m_buffers[1].loadFromFile("data/audio/footstep-dirt.wav");
	}

	~TAudio(){
		
	}

	void play_sound(int id){
		audio.setBuffer(m_buffers[id]);
		audio.play();
	}
};

#endif