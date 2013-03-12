#ifndef VIDEOREADER_H
#define VIDEOREADER_H

#include <opencv2/opencv.hpp>

class VideoReader
{
public:
    VideoReader();
    virtual ~VideoReader();
    VideoReader( const VideoReader & ) = delete;
    VideoReader & operator=( const VideoReader & ) = delete;


    /** @brief Return true if the reading cursor can be moved
        @brief bool : true if the reading cursor can be moved else false */
    virtual bool acceptSeek(void);


    /** @brief get the last image grabbed
        @return IplImage * : last image grabbed */
    virtual IplImage * getImage(void);

    /** @brief grab the current image from the video stream.<br/>
        There is no copy so it's faster so we can get several image from several video stream at the same time
        with more accuracy. */
    virtual void grab(void); // N.B. the "inline" as no effect when we call grab on a pointer or a references.

     virtual int nbFrame(void);
     virtual void r_grab(void);


    virtual void slid(int);

    virtual void useCamera(int idCamera = 0);
private :
    /** @brief video stream */
    CvCapture * m_video;
};

#endif // VIDEOREADER_H
