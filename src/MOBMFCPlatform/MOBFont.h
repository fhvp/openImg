
#ifndef __2016_01_06_MOBFONT_H__
#define __2016_01_06_MOBFONT_H__

/**********************************************************
* Include
**********************************************************/

/**********************************************************
* CMOBFont Class
**********************************************************/
class CMOBFont
{
private:
	static CMOBFont*				m_instance;
protected:
	CFont							m_titleFont;
	CFont							m_bodyFont;
public:
	
private:
protected:
	CMOBFont();
	virtual ~CMOBFont();

	virtual void INIT();
public:
	static CMOBFont* Instance();

	CFont* GetTitleFont();
	CFont* GetBodyFont();
};

#endif __2016_01_06_MOBFONT_H__