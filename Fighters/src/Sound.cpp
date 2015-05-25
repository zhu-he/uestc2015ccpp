#include "Sound.hpp"

sf::SoundBuffer Sound::m_enemyDownSoundBuffer[3];
sf::SoundBuffer Sound::m_ufoSoundBuffer[2];
sf::SoundBuffer Sound::m_bulletSoundBuffer;
sf::SoundBuffer Sound::m_gameMusicSoundBuffer;
sf::SoundBuffer Sound::m_gameOverSoundBuffer;
sf::SoundBuffer Sound::m_useBombSoundBuffer;
sf::Sound Sound::m_enemyDownSound[3];
sf::Sound Sound::m_ufoSound[2];
sf::Sound Sound::m_bulletSound;
sf::Sound Sound::m_gameMusicSound;
sf::Sound Sound::m_gameOverSound;
sf::Sound Sound::m_useBombSound;
bool Sound::m_bgmSwitch = true;
bool Sound::m_sfxSwitch = true;

void Sound::loadResources()
{
	for (int i = 0; i < 3; ++i)
	{
		m_enemyDownSoundBuffer[i].loadFromFile(enemyDownSoundPath[i]);
		m_enemyDownSound[i].setBuffer(m_enemyDownSoundBuffer[i]);
	}
	for (int i = 0; i < 2; ++i)
	{
		m_ufoSoundBuffer[i].loadFromFile(ufoSoundPath[i]);
		m_ufoSound[i].setBuffer(m_ufoSoundBuffer[i]);
	}
	m_bulletSoundBuffer.loadFromFile(bulletSoundPath);
	m_gameMusicSoundBuffer.loadFromFile(gameMusicPath);
	m_gameOverSoundBuffer.loadFromFile(gameOverPath);
	m_useBombSoundBuffer.loadFromFile(useBombSoundPath);
	m_bulletSound.setBuffer(m_bulletSoundBuffer);
	m_gameMusicSound.setBuffer(m_gameMusicSoundBuffer);
	m_gameOverSound.setBuffer(m_gameOverSoundBuffer);
	m_useBombSound.setBuffer(m_useBombSoundBuffer);
	m_gameMusicSound.setLoop(true);
}

void Sound::playEnemyDownSound(int enemyType)
{
	if (m_sfxSwitch)
	{
		m_enemyDownSound[enemyType].play();
	}
}

void Sound::playUfoSound(UfoType ufoType)
{
	if (m_sfxSwitch)
	{
		m_ufoSound[(int)ufoType].play();
	}
}

void Sound::playBulletSound()
{
	if (m_sfxSwitch)
	{
		m_bulletSound.play();
	}
}

void Sound::playGameMusicSound()
{
	if (m_bgmSwitch)
	{
		m_gameMusicSound.play();
	}
}

void Sound::stopGameMusicSound()
{
	m_gameMusicSound.stop();
}

void Sound::playGameOverSound()
{
	if (m_sfxSwitch)
	{
		m_gameOverSound.play();
	}
}

void Sound::playUseBombSound()
{
	if (m_sfxSwitch)
	{
		m_useBombSound.play();
	}
}

void Sound::switchBgm()
{
	m_bgmSwitch = !m_bgmSwitch;
	if (m_bgmSwitch)
	{
		if (m_gameMusicSound.getStatus() == sf::Sound::Stopped)
		{
			m_gameMusicSound.play();
		}
	}
	else
	{
		if (m_gameMusicSound.getStatus() == sf::Sound::Playing)
		{
			m_gameMusicSound.stop();
		}
	}
}

void Sound::switchSfx()
{
	m_sfxSwitch = !m_sfxSwitch;
}

bool Sound::getBgmSwitch()
{
	return m_bgmSwitch;
}

bool Sound::getSfxSwitch()
{
	return m_sfxSwitch;
}
