// ProxyServer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "../YYSocketProxy/ProxyCore.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CProxyCore proxy;
	if(!proxy.Start(6002,1000))
	{
		printf("server start err\n");
	}
	else
	{
		printf("server running\n");
	}

	char buf[32];
	gets(buf);
	while (buf[0]!='q')
	{
		gets(buf);
	}

	return 0;
}

