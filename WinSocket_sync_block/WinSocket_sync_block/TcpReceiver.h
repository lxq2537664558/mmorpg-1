#pragma once
#include "GUGPackage.h"
#include "StreamFix.h"
#include "IOComplatePort.h"

using namespace GUGGAME;
int recvSize(LPPER_IO_DATA perIOData, int recvLen, LEUD::StreamFix &stream);
int recvSizeNormal(LPPER_IO_DATA perIOData, int bytesTransferred);
unsigned int BreakMessageID(LEUD::StreamFix &stream);
short BreakMessage(LEUD::StreamFix &stream);
void OnAccept(SOCKET client, LEUD::StreamFix &stream);
int recvProcess(LPPER_IO_DATA perIOData, int recvLen);
static int sendNum = 0, sendNumFailed = 0, recvNum = 0;

template<typename T>
void SendStruct(SOCKET client, const T &sendObj, int Num = 1)
{
	char buf[1024];
	ZeroMemory(buf, 1024);
	LEUD::StreamFix sendStream(buf, 1024, 0);
	sendStream << (short)0 << (short)0;
	sendStream << sendObj;
	MakeHeadEx(sendStream.m_Buffer, (unsigned short)sendStream.size());

	if (sendNum%10000==0)
		printf("msgid:%d sendNum %d\n",sendObj.no,sendNum);

	for (int i = 0; i < Num; ++i)
	{
		LPPER_IO_DATA SendperIOData = (LPPER_IO_DATA)GlobalAlloc(GPTR, sizeof(PER_IO_DATA));
		SendperIOData->client = client;
		if (sizeof(T) + 4 < sendStream.size())
		{
			printf("send length %d:%d:%d", sendObj.no, sendStream.size(), sizeof(T));
			break;
		}
		memcpy(SendperIOData->buf, sendStream.m_Buffer, sendStream.size());
		send_post(SendperIOData, sendStream.size());
		sendNum++;
	}
	//printf("send num %d:%d,%f\n", sendNum, sendNumFailed, (float)sendNum / (float)(sendNumFailed + sendNum));
}

/*

}


*/