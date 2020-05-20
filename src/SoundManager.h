#pragma once
#ifndef __SOUND_MANAGER__
#define __SOUND_MANAGER__

// Core Libraries
#include <iostream>
#include <string>
#include <map> 

#include "SoundType.h"
#include <SDL_mixer.h>

/* Singleton */
class SoundManager
{
public:
	static SoundManager& Instance()
	{
		static SoundManager instance; // Magic statics.
		return instance;
	}
	
	void allocateChannels(const int channels) const;
	bool load(const std::string& file_name, const std::string& id, SoundType type);
	void unload(const std::string& id, SoundType type);
	void playMusic(const std::string& id, int loop = -1, int fade_in = 0);
	void stopMusic(int fade_out = 0) const;
	void pauseMusic() const;
	void resumeMusic() const;
	void playSound(const std::string& id, int loop = 0, int channel = -1);
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

#endif /* defined (__SOUND_MANAGER__) */