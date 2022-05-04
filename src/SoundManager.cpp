#include "SoundManager.h"
#include <algorithm>

SoundManager::SoundManager()
{
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 2048);
	PanReset();
}

SoundManager::~SoundManager()
= default;

void SoundManager::AllocateChannels(const int channels) const
{
	Mix_AllocateChannels(channels);
}

bool SoundManager::Load(const std::string & file_name, const std::string & id, const SoundType type)
{
	if (type == SoundType::SOUND_MUSIC)
	{
		Mix_Music* music = Mix_LoadMUS(file_name.c_str());
		if (music == nullptr)
		{
			std::cout << "Could not load music: ERROR - " << Mix_GetError() << std::endl;
			return false;
		}
		m_music[id] = music;
		return true;
	}
	else if (type == SoundType::SOUND_SFX)
	{
		Mix_Chunk* chunk = Mix_LoadWAV(file_name.c_str());
		if (chunk == nullptr)
		{
			std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;
			return false;
		}
		m_sfxs[id] = chunk;
		return true;
	}
	return false;
}

void SoundManager::Unload(const std::string & id, const SoundType type)
{
	if (type == SoundType::SOUND_MUSIC && m_music.find(id) != m_music.end())
	{
		Mix_FreeMusic(m_music[id]);
		m_music.erase(id);
	}
	else if (type == SoundType::SOUND_SFX && m_sfxs.find(id) != m_sfxs.end())
	{
		Mix_FreeChunk(m_sfxs[id]);
		m_sfxs.erase(id);
	}
	else
	{
		std::cout << "Could not unload '" << id << "' - id not found!" << std::endl;
	}
}

void SoundManager::PlayMusic(const std::string & id, const int loop/* = -1 */, const int fade_in/* = 0 */)
{
	std::cout << "Playing music..." << fade_in << std::endl;
	if (Mix_FadeInMusic(m_music[id], loop, fade_in) == -1)
	{
		std::cout << "Unable to play music: ERROR - " << Mix_GetError() << std::endl;
	}
}

void SoundManager::StopMusic(const int fade_out/* = 0 */) const
{
	if (Mix_PlayingMusic())
	{
		Mix_FadeOutMusic(fade_out);
	}
}

void SoundManager::PauseMusic() const
{
	if (Mix_PlayingMusic())
	{
		Mix_PauseMusic();
	}
}

void SoundManager::ResumeMusic() const
{
	if (Mix_PausedMusic())
	{
		Mix_ResumeMusic();
	}
}

void SoundManager::PlaySound(const std::string & id, const int loop/* = 0 */, const int channel/* = -1 */)
{
	if (Mix_PlayChannel(channel, m_sfxs[id], loop) == -1)
	{
		std::cout << "Unable to play SFX: ERROR - " << Mix_GetError() << std::endl;
	}
}

void SoundManager::SetMusicVolume(const int vol) const
{
	if (vol >= 0 && vol <= 128)
	{
		Mix_VolumeMusic(vol);
	}
}

void SoundManager::SetSoundVolume(const int vol) const
{
	if (vol >= 0 && vol <= 128)
	{
		Mix_Volume(-1, vol);
	}
}

void SoundManager::SetAllVolume(const int vol) const
{
	SetMusicVolume(vol);
	SetSoundVolume(vol);
}

void SoundManager::PanLeft(const unsigned increment, const int channel)
{
	PanSet(m_pan - increment, channel);
}

void SoundManager::PanRight(const unsigned increment, const int channel)
{
	PanSet(m_pan + increment, channel);
}

void SoundManager::PanReset(const int channel)
{
	PanSet(75, channel);
}

void SoundManager::PanSet(const int amount, const int channel)
{
	std::cout << "Pan:" << amount << std::endl;
	m_pan = std::max(0, std::min(amount, 100)); // Old clamp.
	std::cout << "Pan:" << m_pan << std::endl;
	const auto left_vol = static_cast<Uint8>(255 * std::min((m_pan - 100.0) / (50.0 - 100.0), 1.0)); // z-min/max-min
	std::cout << "Left:" << left_vol << std::endl;
	const auto right_vol = static_cast<Uint8>(255 * std::min(m_pan / 50.0, 1.0));
	std::cout << "Right:" << right_vol << std::endl;
	Mix_SetPanning(channel, left_vol, right_vol);
}

void SoundManager::Quit()
{
	// Clean up sound effects.
	if (Mix_Playing(-1))
	{
		Mix_HaltChannel(-1); // Halt all channels.
	}

	for (const auto& [fst, snd] : m_sfxs)
	{
		Mix_FreeChunk(m_sfxs[fst]);
	}
	m_sfxs.clear();

	// Clean up music.
	if (Mix_PlayingMusic())
	{
		Mix_HaltMusic();
	}

	for (const auto& [fst, snd] : m_music)
	{
		Mix_FreeMusic(m_music[fst]);
	}
	m_music.clear();

	// Quit.
	Mix_CloseAudio();
	Mix_Quit();
}
