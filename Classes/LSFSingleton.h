#ifndef __LSFSINGLETON_H__
#define __LSFSINGLETON_H__

#include "cocos2d.h"

class LSFSingleton {
private:
	static LSFSingleton * instance;
	~LSFSingleton() {/*empty*/ };
	LSFSingleton() {
		value = 10;
	};
public:
	static LSFSingleton * getInstance();
	static void releaseInstance();

	int value;

};
#endif