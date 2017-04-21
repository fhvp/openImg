

#include "stdafx.h"
#include "ImageManager.h"
#include "BitmapManager.h"

CImageManager* CImageManager::m_instance = 0x00;

CImageManager* CImageManager::Instance()
{
	if (CImageManager::m_instance == NULL)
		CImageManager::m_instance = new CImageManager();
	return CImageManager::m_instance;
}


CImageManager::CImageManager()
{

}

CImageManager::~CImageManager()
{

}


