#pragma once

#include "ShSDK/ShSDK.h"

class State
{

protected:

	State(void);
	virtual ~State(void);

public:

	virtual void init		(const CShIdentifier & levelIdentifier) = 0;
	virtual void release	(void) = 0;

	virtual void entered	(void) = 0;
	virtual void exiting	(void) = 0;

	virtual void obscuring	(void) = 0;
	virtual void revealed	(void) = 0;

	virtual void update		(float dt) = 0;

	virtual void touchBegin	(const CShVector2 & pos);
	virtual void touchEnd	(const CShVector2 & pos);
	virtual void touchMove	(const CShVector2 & pos);

};
