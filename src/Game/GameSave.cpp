#include "Game.h"

#include "GameSave.h"

/**
 * @brief GameSave
 */
GameSave::GameSave(void)
{
	// ...
}

/**
 * @brief ~GameSave
 */
GameSave::~GameSave(void)
{
	// ...
}

/**
* @brief Save
*/
void GameSave::Save(void)
{
	if (shNULL != g_pCurrentUser)
	{
		bool bSaved = ShUser::Save(g_pCurrentUser, "ShockWave", ((SaveData *) &(this->m_saveData)), 2048);
		if (!bSaved)
		{
			Reset();
		}
	}

	if (m_saveData.mute)
	{
		ShSound::SetGlobalVolume(0.0f);
	}
	else
	{
		ShSound::SetGlobalVolume(1.0f);
	}
}

/**
* @brief Load
*/
void GameSave::Load(void)
{
	if (shNULL != g_pCurrentUser)
	{
		bool bLoaded = ShUser::Load(g_pCurrentUser, "ShockWave", (SaveData *) &(this->m_saveData), sizeof(SaveData));
		if (!bLoaded)
		{
			SH_TRACE("Load failed !");
		}
	}
}

/**
* @brief Reset
*/
void GameSave::Reset(void)
{
	m_saveData = SaveData();
}

/**
* @brief GetLastLevelPlayed
*/
int GameSave::GetLastLevelPlayed(void)
{
	return(m_saveData.lastLevelPlayed);
}

/**
* @brief GetLastLevelUnlocked
*/
int GameSave::GetLastLevelUnlocked(void)
{
	return(m_saveData.lastLevelUnlocked);
}

/**
* @brief Reset
* @param page
* @param level
*/
int GameSave::GetLevelResult(int level)
{
	return(m_saveData.levelResult[level]);
}

/**
* @brief GetIsMuted
*/
bool GameSave::GetIsMuted(void)
{
	return(m_saveData.mute);
}

/**
* @brief Reset
* @param level
*/
void GameSave::SetLastLevelPlayed(int level)
{
	m_saveData.lastLevelPlayed = level;
}

/**
* @brief Reset
* @param level
*/
void GameSave::SetLastLevelUnlocked(int level)
{
	if (m_saveData.lastLevelUnlocked < level)
	{
		m_saveData.lastLevelUnlocked = level;
	}
}

/**
* @brief Reset
* @param page
* @param level
* @param nbStars
*/
void GameSave::SetLevelResult(int level, int nbStars)
{
	if (m_saveData.levelResult[level] < nbStars)
	{
		m_saveData.levelResult[level] = nbStars;
	}
}

/**
* @brief SetMute
* @param mute
*/
void GameSave::SetMute(bool mute)
{
	m_saveData.mute = mute;
	Save();
}
