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

	void		SetLastLevelPlayed		(int level);
	void		SetLastLevelUnlocked	(int level);
	void		SetLevelResult			(int level, int nbStars);


private:
	struct SaveData
	{
		SaveData(void)
		{
			lastLevelPlayed = 1;
			lastLevelUnlocked = 1;
			ShMemClear(levelResult, sizeof(levelResult));
		}

		unsigned int	lastLevelPlayed;
		unsigned int	lastLevelUnlocked;
		unsigned int	levelResult[1024];
	};

	SaveData m_saveData;
};
