#pragma  once

//////////////////////////////////////////////////////////////////////////
//1: 地图数据管理
//2: mapobject管理
//3：消息分发替代viewListTTT.h/cpp
//////////////////////////////////////////////////////////////////////////
class MapMgr
{
public:
	static int generateID(int type);
	static bool isPlayer(int id);
	static bool isMaster(int id);
};


class Map
{

};
