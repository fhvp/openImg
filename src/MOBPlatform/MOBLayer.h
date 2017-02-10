/*
* MOBLayer.h
*
*  Created on: 2015. 9. 17.
*      Author: jghan
*/

#ifndef __2015_09_17_MOBLAYER_H__
#define __2015_09_17_MOBLAYER_H__

/**********************************************************
* Layer Information
**********************************************************/
enum LAYER
{
	MOB_LAYER_NONE			= 0,
	MOB_LAYER_GUI			= 1,
	MOB_LAYER_PHY			= 3,
	MOB_LAYER_MAC			= 4,
	MOB_LAYER_RLC			= 5,
	MOB_LAYER_RRC			= 6,

	MOB_LAYER_DM			= 11,
	MOB_LAYER_LOG			= 12,
	MOB_LAYER_SOCKET		= 13,

	MOB_LAYER_TIME			= 14,
	MOB_LAYER_PLATFORM		= 15,
	MOB_LAYER_TEST			= 16
};

#endif __2015_09_17_MOBLAYER_H__
