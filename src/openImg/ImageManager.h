
#ifndef __IMAGE_MANAGER_H__
#define __IMAGE_MANAGER_H__

class CImageManager
{
private:
	static CImageManager*			m_instance;
protected:
public:



private:
protected:
	CImageManager();
public:
	static CImageManager* Instance();
	
	virtual ~CImageManager();


};

#endif /*__IMAGE_MANAGER_H__*/