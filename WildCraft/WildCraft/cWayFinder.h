#pragma once

class cAction;
class cWayFinder
{
private:
	SINGLETONE(cWayFinder);
public:
	cAction* FindWay(/* From, To, NodeList */) { return nullptr; };
};
#define FIND_WAY cWayFinder::GetInstance()

