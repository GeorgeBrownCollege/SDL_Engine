#include "SoundManager.h"
#include <algorithm>

SoundManager::SoundManager()
{
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 2048);
	panReset();
}

SoundManager::~SoundManager()
= default;

void SoundManager::allocateChannels(const int channels) const
{
	Mix_AllocateChannels(channels);
}

bool SoundManager::load(const std::string & file_name, const std::string & id, const SoundType type)
{
	if (type == SOUND_MUSIC)
	{
		Mix_Music* pMusic = Mix_LoadMUS(file_name.c_str());
		if (pMusic == nullptr)
		{
			std::cout << "Could not load music: ERROR - " << Mix_GetError() << std::endl;
			return false;
		}
		m_music[id] = pMusic;
		return true;
	}
	else if (type == SOUND_SFX)
	{
		Mix_Chunk* pChunk = Mix_LoadWAV(file_name.c_str());
		if (pChunk == nullptr)
		{
			std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;
			return false;
		}
		m_sfxs[id] = pChunk;
		return true;
	}
	return false;
}

void SoundManager::unload(const std::string & id, const SoundType type)
{
	if (type == SOUND_MUSIC && m_music.find(id) != m_music.end())
	{
		Mix_FreeMusic(m_music[id]);
		m_music.erase(id);
	}
	else if (type == SOUND_SFX && m_sfxs.find(id) != m_sfxs.end())
	{
		Mix_FreeChunk(m_sfxs[id]);
		m_sfxs.erase(id);
	}
	else
	{
		std::cout << "Could not unload '" << id << "' - id not found!" << std::endl;
	}
}

void SoundManager::playMusic(const std::string & id, const int loop/* = -1 */, const int fade_in/* = 0 */)
{
	std::cout << "Playing music..." << fade_in << std::endl;
	if (Mix_FadeInMusic(m_music[id], loop, fade_in) == -1)
	{
		std::cout << "Unable to play music: ERROR - " << Mix_GetError() << std::endl;
	}
}

void SoundManager::stopMusic(const int fade_out/* = 0 */) const
{
	if (Mix_PlayingMusic())
	{
		Mix_FadeOutMusic(fade_out);
	}
}

void SoundManager::pauseMusic() const
{
	if (Mix_PlayingMusic())
	{
		Mix_PauseMusic();
	}
}

void SoundManager::resumeMusic() const
{
	if (Mix_PausedMusic())
	{
		Mix_ResumeMusic();
	}
}

void SoundManager::playSound(const std::string & id, const int loop/* = 0 */, const int channel/* = -1 */)
{
	if (Mix_PlayChannel(channel, m_sfxs[id], loop) == -1)
	{
		std::cout << "Unable to play SFX: ERROR - " << Mix_GetError() << std::endl;
	}
}

void SoundManager::setMusicVolume(const int vol) const
{
	if (vol >= 0 && vol <= 128)
	{
		Mix_VolumeMusic(vol);
	}
}

void SoundManager::setSoundVolume(const int vol) const
{
	if (vol >= 0 && vol <= 128)
	{
		Mix_Volume(-1, vol);
	}
}

void SoundManager::setAllVolume(const int vol) const
{
	setMusicVolume(vol);
	setSoundVolume(vol);
}

void SoundManager::panLeft(const unsigned increment, const int channel)
{
	panSet(m_pan - increment, channel);
}

void SoundManager::panRight(const unsigned increment, const int channel)
{
	panSet(m_pan + increment, channel);
}

void SoundManager::panReset(const int channel)
{
	panSet(75, channel);
}

void SoundManager::panSet(const int amount, const int channel)
{
	std::cout << "Pan:" << amount << std::endl;
	m_pan = std::max(0, std::min(amount, 100)); // Old clamp.
	std::cout << "Pan:" << m_pan << std::endl;
	const int leftVol = (255 * std::min((m_pan - 100.0) / (50.0 - 100.0), 1.0)); // z-min/max-min
	std::cout << "Left:" << leftVol << std::endl;
	const int rightVol = (255 * std::min(m_pan / 50.0, 1.0));
	std::cout << "Right:" << rightVol << std::endl;
	Mix_SetPanning(channel, leftVol, rightVol);
}

void SoundManager::quit()
{
	// Clean up sound effects.
	if (Mix_Playing(-1))
	{
		Mix_HaltChannel(-1); // Halt all channels.
	}

	for (auto const& i : m_sfxs)
	{
		Mix_FreeChunk(m_sfxs[i.first]);
	}
	m_sfxs.clear();

	// Clean up music.
	if (Mix_PlayingMusic())
	{
		Mix_HaltMusic();
	}

	for (auto const& i : m_music)
	{
		Mix_FreeMusic(m_music[i.first]);
	}
	m_music.clear();

	// Quit.
	Mix_CloseAudio();
	Mix_Quit();
}
