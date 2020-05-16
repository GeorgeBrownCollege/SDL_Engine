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
	static SoundManager& Instance()
	{
		static SoundManager instance; // Magic statics.
		return instance;
	}
	void allocateChannels(const int channels) const;
	bool load(std::string fileName, std::string id, sound_type type);
	void unload(std::string id, sound_type type);
	void playMusic(std::string id, int loop = -1, int fadeIn = 0);
	void stopMusic(int fadeOut = 0) const;
	void pauseMusic() const;
	void resumeMusic() const;
	void playSound(std::string id, int loop = 0, int channel = -1);
	void setMusicVolume(const int vol) const;
	void setSoundVolume(const int vol) const;
	void setAllVolume(const int vol) const;
	// Panning converts a single slider value from 0 to 100 to the stereo speaker volumes.
	void panLeft(const unsigned increment = 5, const int channel = MIX_CHANNEL_POST);
	void panRight(const unsigned increment = 5, const int channel = MIX_CHANNEL_POST);
	void panReset(const int channel = MIX_CHANNEL_POST);
	void panSet(const int amount, const int channel = MIX_CHANNEL_POST);
	void quit();
private: // Methods.
	SoundManager();
	SoundManager(const SoundManager&);
	~SoundManager();
private: // Properties.
	static SoundManager* s_pInstance;
	std::map<std::string, Mix_Chunk*> m_sfxs;
	std::map<std::string, Mix_Music*> m_music;
	int m_pan; // A slider value from 0 to 100. 0 = full left, 100 = full right.
};

#endif /* defined (__SoundManager__) */