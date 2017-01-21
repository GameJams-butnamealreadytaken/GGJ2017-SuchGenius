#pragma once

#include "ShSDK/ShSDK.h"
#include "ShEngineExt/ShEngineExt.h"

#include "Box2D/Box2D.h"

class Block
{
public:
	enum EBlockType
	{
		STATIC,
		DYNAMYC,
		PLAYER,
		SENSOR,
	};

						Block		(void);
	virtual				~Block		(void);

	void				Initialize	(b2Body * pBody, ShObject * pObject, EBlockType type);
	void				Release		(void);

	EBlockType			GetType		(void);
	b2Body *			GetBody		(void);
	ShObject *			GetSprite	(void);

private:

	ShObject * m_pSprite;
	b2Body * m_pBody;
	EBlockType m_type;
	
};
