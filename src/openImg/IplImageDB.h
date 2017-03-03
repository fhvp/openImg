
#ifndef __IPL_IMAGE_DB_H__
#define __IPL_IMAGE_DB_H__

/**********************************************************
* Include
**********************************************************/
#include "MOBCommon.h"
#ifdef OPENCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
#endif /*OPENCV*/

/**********************************************************
* Definetion
**********************************************************/
#define MAX_FILE_PATH			2048
#define MAX_FILE_NAME			1024

/**********************************************************
* CIplImageDB class
**********************************************************/
class CIplImageDB
{
private:
protected:
	int					m_contrast;		//밝기
	double				m_brightness;	//명도
	int					m_saturation;	//채도
	bool				m_isChanged;
public:
	IplImage*			m_inImgIpl;
	IplImage*			m_outImgIpl;

	//Image Mat
	Mat					m_inMat;
	Mat					m_midMat;	//Auto Control
	Mat					m_outMat;

	//Text Mat
	Mat					m_textMat;

	//file name & path
	String				m_path;
	String				m_name;

	//resize
	double				m_resize;
	Mat					m_resizeMat;
public:
	CIplImageDB();
	virtual ~CIplImageDB();

	void SetResize(int _width, int _height);
	void Clear();
	void Delete();

	void setChanged() { this->m_isChanged = true; }
	bool getChanged() { return this->m_isChanged; }
	int addContrast(int _contrast) { this->m_isChanged = true; this->m_contrast += _contrast; return this->m_contrast; }
	int subContrast(int _contrast) { this->m_isChanged = true; this->m_contrast -= _contrast; return this->m_contrast; }
	int getContrast() { return this->m_contrast; }
	double addBrightness(double _brightness) { this->m_isChanged = true; this->m_brightness += _brightness; return this->m_brightness; }
	double subBrightness(double _brightness) { this->m_isChanged = true; this->m_brightness -= _brightness; return this->m_brightness; }
	double getBrightness() { return this->m_brightness; }
	int addSaturation(int _saturation) { this->m_isChanged = true; this->m_saturation += _saturation; return this->m_saturation; }
	int subSaturation(int _saturation) { this->m_isChanged = true; this->m_saturation -= _saturation; return this->m_saturation; }
	int getSaturation() { return this->m_saturation; }
};

#endif /*__IPL_IMAGE_DB_H__*/
