/*
* MOBLayer.h
*
*  Created on: 2015. 9. 17.
*      Author: jghan
*/

#ifndef __2015_09_17_MOBDEFS_H__
#define __2015_09_17_MOBDEFS_H__


/**********************************************************
* Global Define
**********************************************************/
typedef unsigned char					u_8;
typedef unsigned short					u_16;
typedef unsigned int					u_32;

//typedef unsigned char					STATE;

#define u8								u_8
#define u16								u_16
#define u32								u_32

#define MOB_FAILURE						0
#define MOB_SUCCESS						1

#define MOB_NULL						0

#define BYTE1							1
#define BYTE2							2
#define BYTE3							3
#define BYTE4							4
#define BYTE8							8
#define BYTE16							16
#define BYTE32							32
/**********************************************************
* Enumeration
**********************************************************/
enum STATE
{
	MOB_FAILED,
	MOB_SUCCEED
};

enum PROPOSITION
{
	MOB_FALSE,
	MOB_TRUE
};

/**********************************************************
* Define
**********************************************************/
//#define __CONSOLE_PRINT__

#endif __2015_09_17_MOBDEFS_H__