#pragma once
#ifndef __SoundManager__
#define __SoundManager__

// Core Libraries
#include <iostream>
#include <string>
#include <map> 

#include <SDL_mixer.h>

enum sound_type
{
	SOUND_MUSIC = 0,
	SOUND_SFX = 1
};

class SoundManager {
public:
	static SoundManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new SoundManager();
		}
		return s_pInstance;
	}

	bool load(std::string fileName, std::string id, sound_type type);
	void playSound(std::string id, int loop);
	void playMusic(std::string id, int loop);
private:
	static SoundManager* s_pInstance;

	std::map<std::string, Mix_Chunk*> m_sfxs;
	std::map<std::string, Mix_Music*> m_music;

	SoundManager();
	~SoundManager();

	SoundManager(const SoundManager&);
};

typedef SoundManager TheSoundManager;

#endif /* defined (__SoundManager__) */