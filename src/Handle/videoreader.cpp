#include "videoreader.h"
#include "../exception.h"

VideoReader::VideoReader()
    : m_video(nullptr)
{
}


/*---------------------------------------------------------------------------------------------------
------------------------------------------------PUBLIC-----------------------------------------------
---------------------------------------------------------------------------------------------------*/

bool VideoReader::acceptSeek(void)
{
    return false;
}


IplImage * VideoReader::getImage(void)
{
    return cvQueryFrame(m_video);
}


void VideoReader::grab(void)
{
    if(m_video)
       cvGrabFrame(m_video);
}


int VideoReader::nbFrame(void)
{
    return 0;
}


void VideoReader::r_grab(void)
{
}


void VideoReader::useCamera(int idCamera)
{
    auto tmp = cvCreateCameraCapture(idCamera);
    if( ! tmp )
        throw Exception::buildException("Can't use this camera as source", "VideoReader", "useCamera", EPC);
    m_video = tmp;
}

VideoReader::~VideoReader()
{
    cvReleaseCapture(&m_video);
}

//fin video cvReleaseCapture

void VideoReader::slid(int)
{

}
