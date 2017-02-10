/*
* MOBLayer.h
*
*  Created on: 2015. 10. 21.
*      Author: jghan
*/

#ifndef __2015_10_21_MOBSOCKET_H__
#define __2015_10_21_MOBSOCKET_H__

/**********************************************************
* Include
**********************************************************/
#include "MOBList.h"

#ifdef GNUCC

#else if WIN32
	#include <windows.h>
	//#include <WinSock2.h>
#endif

/**********************************************************
* Define Variable
**********************************************************/
#ifdef GNUCC

#else if WIN32
	#define MOB_SOCK				SOCKET
	#define MOB_SOCK_ADDR			SOCKADDR_IN
#endif

//DGRAM
// * Fast Translate
// * Translate Trouble
#define	MOB_SOCK_DGRAM				SOCK_DGRAM

//STREAM
// * Ordering Translate
// * No Translate Trouble
#define MOB_SOCK_STREAM				SOCK_STREAM

#define MOB_SOCK_UDP				IPPROTO_UDP
#define MOB_SOCK_TCP				IPPROTO_TCP

#define MOB_SOCK_FAILED				-1
#define MOB_SOCK_SUCCESS			MOB_SUCCEED

/**********************************************************
* List Item
**********************************************************/
class SocketInformation : public ListItem
{
	//Variable
private:
protected:
public:
	MOB_SOCK						m_sock;
	MOB_SOCK_ADDR*					m_srcAddr;
	MOB_SOCK_ADDR*					m_dstAddr;

	//Function
private:
protected:
public:
	SocketInformation();
	virtual ~SocketInformation();
};

/**********************************************************
* Class
**********************************************************/
class CMOBSocket : public CMOBList
{
	//Variable
private:
	static CMOBSocket*					m_instance;
protected:
	std::list<SocketInformation*>		m_sockList;
public:

	//Function
private:
protected:
	CMOBSocket();
	virtual ~CMOBSocket();
public:
	virtual STATE INIT();
	static CMOBSocket* Instance();

	MOB_SOCK_ADDR* InitSockAddr(u16 _port);					//Local Socket Address
	MOB_SOCK_ADDR* InitSockAddr(u8* _ip, u16 _port);
	
	MOB_SOCK InitUDPSock();
	
	STATE Bind(MOB_SOCK _sock, MOB_SOCK_ADDR* _addr);
	STATE SetNonBlockingMode(MOB_SOCK _sock);
	STATE SetDestination(MOB_SOCK _sock, MOB_SOCK_ADDR* _addr);

	u16 RecvData(MOB_SOCK _sock, char* _buf, int _bufLen);
	STATE SendData(MOB_SOCK _sock, char* _buf, int _bufLen);

	SocketInformation* Find(MOB_SOCK _sock);
	void Insert(SocketInformation* _data);
	STATE Delete(MOB_SOCK _sock);
};

#endif __2015_10_21_MOBSOCKET_H__