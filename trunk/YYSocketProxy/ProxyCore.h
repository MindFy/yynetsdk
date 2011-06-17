
/*

	YYNetSDK 
	��MicroPop����
	��ѭcode.google��ԴЭ�飬��������ת����ʹ��
	https://yynetsdk.googlecode.com/svn/trunk

	TCP���������
	1.client->N*server,��one client ���Ա��ֺ�N��server������
	2.��Ϣ��ת
	3.��Ϣ����

	v1.0.0.1
	2011-06-14
	micropop@163.com
*/

#pragma once
#include "export.h"
#include "CClientContext.h"
#include "CIOBuffer.h"
#include "lock.h"
#include <list>
#include <map>
using namespace std;
#include "msg.h"
#include "myMsg.h"
#include <algorithm>

typedef list<CClientContext*> ClientContextList;
typedef ClientContextList::iterator ClientContextListIt;

typedef list<CIOBuffer*> IOBufferList;
typedef IOBufferList::iterator IOBufferListIt;

class _DLL CProxyCore
{
public:
	CProxyCore(void);
	~CProxyCore(void);
public:
	bool Start(UINT port,UINT maxOL);
	bool Stop();

	static DWORD WINAPI Listen(LPVOID param);
	static DWORD WINAPI Worker(LPVOID param);

	CClientContext	* AllocateClient(SOCKET sock);
	CIOBuffer		* AllocateBuffer(IOType type);
	void	ReleaseClient(CClientContext*pClient);
	void	ReleaseBuffer(CIOBuffer*pBuffer);

	void	ProcessIO(CClientContext*pClient,CIOBuffer*pBuffer,DWORD dwSize);

	void	OnHandleMsg(CClientContext* pClient,BYTE *data,int dataLen);

	bool	CreateSocket(CClientContext*pClient,char*ip,char*port);

	void	SendMsg(CClientContext*pClient,BYTE *data,int dataLen);
	void	SendMsg(CClientContext*pClient,CMsg*msg);

public:
	virtual void OnProxyMsg(LPVOID client,CMsg *msg) 
	{
		printf("recv msg len=%d\n",msg->GetMsgHead().len);
	}
public:
	//lock
	CLock				m_clientLock;
	ClientContextList	m_clientListFree;
	ClientContextList	m_clientListBusy;
	//lock
	CLock				m_bufferLock;
	IOBufferList		m_bufferListFree;
	IOBufferList		m_bufferListBusy;

	UINT				m_maxOnlineUser;
	UINT				m_port;

	HANDLE				m_hIOCP;
	SOCKET				m_listenSock;

	HANDLE				m_svrStopEvent;
};
