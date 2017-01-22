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
			lastLevelPlayed = 0;
			lastLevelUnlocked = 1;

			for (int i = 0; i < MAX_PAGE * 9 ; ++i)
			{
				levelResult[i] = 0;
			}
		}

		unsigned int	lastLevelPlayed;
		unsigned int	lastLevelUnlocked;
		unsigned int	levelResult[MAX_PAGE * 9];
	};

	SaveData m_saveData;
};
