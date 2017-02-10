
/**********************************************************
* include
**********************************************************/
#include "MOBSocket.h"
#include "MOBLayer.h"
#include "MOBLogger.h"

/**********************************************************
* Global Variable
**********************************************************/

/**********************************************************
* Static Variable & Function
**********************************************************/
CMOBSocket* CMOBSocket::m_instance = 0x00;

CMOBSocket* CMOBSocket::Instance()
{
	if (CMOBSocket::m_instance == 0x00)
		CMOBSocket::m_instance = new CMOBSocket();
	return CMOBSocket::m_instance;
}

/**********************************************************
* Sock Information List Item
**********************************************************/
SocketInformation::SocketInformation()
{
	this->m_sock = 0x00;
	this->m_srcAddr = 0x00;
	this->m_dstAddr = 0x00;
}

SocketInformation::~SocketInformation()
{
	this->m_sock = 0x00;
	this->m_srcAddr = 0x00;
	this->m_dstAddr = 0x00;
}

/**********************************************************
* Default CMOBSocket Function
**********************************************************/
CMOBSocket::CMOBSocket()
{
	this->INIT();
}

CMOBSocket::~CMOBSocket()
{

}

STATE CMOBSocket::INIT()
{
	WORD wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD(2, 0);// Request WinSock v2.0

	if (WSAStartup(wVersionRequested, &wsaData) != 0)
	{
		return MOB_FAILED;
	}

	return MOB_SUCCEED;
}

/**********************************************************
* CMOBSock Function
**********************************************************/
MOB_SOCK_ADDR* CMOBSocket::InitSockAddr(u16 _port)
{
	MOB_SOCK_ADDR* addr = new MOB_SOCK_ADDR();
	if (addr == MOB_FAILURE)
		return MOB_FAILURE;

	memset(addr, 0, sizeof(MOB_SOCK_ADDR));
	addr->sin_family = AF_INET;
	addr->sin_addr.s_addr = htonl(INADDR_ANY);
	addr->sin_port = htons(_port);

	return addr;
}

MOB_SOCK_ADDR* CMOBSocket::InitSockAddr(u8* _ip, u16 _port)
{
	MOB_SOCK_ADDR* addr = new MOB_SOCK_ADDR();
	if (addr == MOB_FAILURE)
		return MOB_FAILURE;

	memset(addr, 0, sizeof(MOB_SOCK_ADDR));
	addr->sin_family = AF_INET;
	addr->sin_addr.s_addr = inet_addr((char*)_ip);
	addr->sin_port = htons(_port);

	return addr;
}

MOB_SOCK CMOBSocket::InitUDPSock()
{
	MOB_SOCK sock;

	sock = ::socket(AF_INET, MOB_SOCK_DGRAM, MOB_SOCK_UDP);

	if (sock == INVALID_SOCKET)
	{
		MOB_DEBUG(MOB_LAYER_PLATFORM, "Socket Initialize is Failed!!\n");
		return MOB_FAILED;
	}

	MOB_DEBUG(MOB_LAYER_PLATFORM, "Init Socket!! ID : %d\n", sock);

	SocketInformation* sockInfo = new SocketInformation();
	sockInfo->m_sock = sock;

	this->Insert(sockInfo);

	return sock;
}

STATE CMOBSocket::Bind(MOB_SOCK _sock, MOB_SOCK_ADDR* _addr)
{
	SocketInformation* sockInfo = (SocketInformation*)this->Find(_sock);
	if (sockInfo == MOB_FAILURE)
	{
		MOB_DEBUG(MOB_LAYER_PLATFORM, "Can not Find Socket Information!! Sock ID : %d\n", _sock);
		return MOB_FAILED;
	}

	MOB_SOCK_ADDR addr = *_addr;
	if (::bind(_sock, (SOCKADDR*)&addr, sizeof(MOB_SOCK_ADDR)) == SOCKET_ERROR)
	{
		MOB_DEBUG(MOB_LAYER_PLATFORM, "Socket Bind is Failed!! IP : %s(%d)\n", inet_ntoa(_addr->sin_addr), ntohs(_addr->sin_port));
		closesocket(_sock);
		SAFE_DELETE(_addr);
		return MOB_FAILED;
	}

	MOB_DEBUG(MOB_LAYER_PLATFORM, "Bind Socket!! IP : %s(%d)\n", inet_ntoa(_addr->sin_addr), ntohs(_addr->sin_port));

	sockInfo->m_srcAddr = _addr;

	return MOB_SUCCEED;
}

STATE CMOBSocket::SetDestination(MOB_SOCK _sock, MOB_SOCK_ADDR* _addr)
{
	SocketInformation* sockInfo = (SocketInformation*)this->Find(_sock);
	if (sockInfo == MOB_FAILURE)
	{
		MOB_DEBUG(MOB_LAYER_PLATFORM, "Can not Find Socket Information!! Sock ID : %d\n", _sock);
		return MOB_FAILED;
	}

	sockInfo->m_dstAddr = _addr;

	return MOB_SUCCEED;
}

STATE CMOBSocket::SetNonBlockingMode(MOB_SOCK _sock)
{
	unsigned long mode = 1;
	if (::ioctlsocket(_sock, FIONBIO, &mode))
	{
		MOB_DEBUG(MOB_LAYER_PLATFORM, "Failed Non Blocking Mode Setting!!\n");
		return MOB_FAILED;
	}

	return MOB_SUCCEED;
}

u16 CMOBSocket::RecvData(MOB_SOCK _sock, char* _buf, int _bufLen)
{
	if (_sock == 0x00)
		return MOB_FAILED;
	SocketInformation* sockInfo = (SocketInformation*)this->Find(_sock);
	if (sockInfo == MOB_FAILURE)
	{
		MOB_DEBUG(MOB_LAYER_PLATFORM, "Can not Find Socket Information!! Sock ID : %d\n", _sock);
		return MOB_FAILED;
	}

	MOB_SOCK_ADDR addr;
	int size = sizeof(MOB_SOCK_ADDR);

	int result = ::recvfrom(sockInfo->m_sock, _buf, _bufLen, 0, (sockaddr*)&addr, &size);

	if (result == MOB_SOCK_FAILED)
	{
		return MOB_FAILED;
	}

	return size;
}

STATE CMOBSocket::SendData(MOB_SOCK _sock, char* _buf, int _bufLen)
{
	SocketInformation* sockInfo = (SocketInformation*)this->Find(_sock);
	if (sockInfo == MOB_FAILURE)
	{
		MOB_DEBUG(MOB_LAYER_PLATFORM, "Can not Find Socket Information!! Sock ID : %d\n", _sock);
		return MOB_FAILED;
	}

	if (sockInfo->m_dstAddr == 0x00)
	{
		MOB_DEBUG(MOB_LAYER_PLATFORM, "Failed to Send Data!! Destination Address is Empty!\n");
		return MOB_FAILED;
	}

	MOB_SOCK_ADDR addr = *sockInfo->m_dstAddr;
	if (::sendto(sockInfo->m_sock, _buf, _bufLen, 0, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		MOB_DEBUG(MOB_LAYER_PLATFORM, "Failed to Send Data!! Destination Info : %s(%d)\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
		return MOB_FAILED;
	}

	return MOB_SUCCEED;
}

SocketInformation* CMOBSocket::Find(MOB_SOCK _sock)
{
	std::list<SocketInformation*>::iterator iter;
	SocketInformation* item;
	for (iter = this->m_sockList.begin(); iter != this->m_sockList.end(); ++iter)
	{
		item = *iter;

		if (item->m_sock == _sock)
		{
			return item;
		}
	}
	return MOB_FAILURE;
}

void CMOBSocket::Insert(SocketInformation* _data)
{
	this->m_sockList.push_back(_data);
}

STATE CMOBSocket::Delete(MOB_SOCK _sock)
{
	SocketInformation* sockInfo = (SocketInformation*)this->Find(_sock);
	if (sockInfo == MOB_FAILURE)
	{
		MOB_DEBUG(MOB_LAYER_PLATFORM, "Can not Find Socket Information!! Sock ID : %d\n", _sock);
		return MOB_FAILED;
	}

	closesocket(_sock);
	this->m_sockList.remove(sockInfo);

	SAFE_DELETE(sockInfo->m_srcAddr);
	SAFE_DELETE(sockInfo->m_dstAddr);
	delete sockInfo;

	return MOB_SUCCEED;
}
