#ifndef __SOUND_HPP__
#define __SOUND_HPP__

#include <SFML/Audio.hpp>
#include <iostream>
#include "Global.hpp"

class Sound
{
	public:
		static void loadResources();
		static void playEnemyDownSound(int enemyType);
		static void playUfoSound(UfoType ufoType);
		static void playBulletSound();
		static void playGameMusicSound();
		static void stopGameMusicSound();
		static void playGameOverSound();
		static void playUseBombSound();
		static void switchBgm();
		static void switchSfx();
		static bool getBgmSwitch();
		static bool getSfxSwitch();
	private:
		static sf::SoundBuffer m_enemyDownSoundBuffer[3];
		static sf::SoundBuffer m_ufoSoundBuffer[2];
		static sf::SoundBuffer m_bulletSoundBuffer;
		static sf::SoundBuffer m_gameMusicSoundBuffer;
		static sf::SoundBuffer m_gameOverSoundBuffer;
		static sf::SoundBuffer m_useBombSoundBuffer;
		static sf::Sound m_enemyDownSound[3];
		static sf::Sound m_ufoSound[2];
		static sf::Sound m_bulletSound;
		static sf::Sound m_gameMusicSound;
		static sf::Sound m_gameOverSound;
		static sf::Sound m_useBombSound;
		static bool m_bgmSwitch;
		static bool m_sfxSwitch;
};

#endif // __SOUND_HPP__
