#include "pch.h"
#include "CoreGlobal.h"

class CoreGlobal
{
public:
	CoreGlobal()
	{
		SocketUtils::startUp();
	}

	~CoreGlobal()
	{
		SocketUtils::cleanUp();
	}
} gCoreGlobal;