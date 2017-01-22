#pragma once

#include "State.h"

class GameSave
{

public:

	explicit	GameSave				(void);
	virtual		~GameSave				(void);

	void		Save					(void);
	void		Load					(void);
	void		Reset					(void);

	int			GetLastLevelPlayed		(void);
	int			GetLastLevelUnlocked	(void);
	int			GetLevelResult			(int level);
	bool		GetIsMuted				(void);

	void		SetLastLevelPlayed		(int level);
	void		SetLastLevelUnlocked	(int level);
	void		SetLevelResult			(int level, int nbStars);
	void		SetMute					(bool mute);

private:
	struct SaveData
	{
		SaveData(void)
		{
			lastLevelPlayed = 1;
			lastLevelUnlocked = 1;

			for (int i = 0; i < MAX_PAGE * 9 ; ++i)
			{
				levelResult[i] = 0;
			}

			mute = false;

			ShMemClear(levelResult, sizeof(levelResult));
		}

		unsigned int	lastLevelPlayed;
		unsigned int	lastLevelUnlocked;

		bool			mute;

		unsigned int	levelResult[1024];
	};

	SaveData m_saveData;
};
