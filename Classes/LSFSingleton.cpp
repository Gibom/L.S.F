#include "LSFSingleton.h"

LSFSingleton * LSFSingleton::instance = NULL;

LSFSingleton * LSFSingleton::getInstance()
{
	if (!instance)
	{
		instance = new LSFSingleton();
	}

	return instance;
}

void LSFSingleton::releaseInstance()
{
	if (instance) delete instance;
}