#include "videoextractor.h"

#include <QElapsedTimer>

#include "Handle.h"

VideoExtractor::VideoExtractor(bool dual )
    : m_stopped(true), m_dual(dual)
{
    //activer les caméras
}

void VideoExtractor::start(qint64 time, qint64 timeMax, qint64 nbMaxImage)
{
    if( m_stopped != true )
        return;
    m_time = time;
    m_timeMax = timeMax;
    m_nbMaxImage = nbMaxImage;
    m_stopped = false;
    m_nbImageHandled = 0;
    run();
}


void VideoExtractor::run(void)
{
    bool stoppedByUser = true;
    QElapsedTimer timer;
    qint64 endOfCapture;
    qint64 endOfHandle;
    qint64 begin;
    IplImage * src1, * src2;
    timer.start();
    while( ! m_stopped )
    {
        begin = timer.nsecsElapsed();

        m_videoStream[0].grab(); // a for for that ... I'm too lazy
        m_videoStream[1].grab();

        if( m_timeMax && m_timeMax > begin)
        {
            stoppedByUser = false;
            break;
        }

        src1 = m_videoStream[0].getImage();
        src2 = m_videoStream[1].getImage();

        ImageDataPtr source1, source2;

        if(src1)
            source1 = ImageDataPtr(new ImageData(*src1));
        if(src2)
            source2 = ImageDataPtr(new ImageData(*src2));

        endOfCapture = timer.nsecsElapsed();
        ImageDataPtr result = VirtualHandle::executeHandle(MainHandle, source1, source2);
        endOfHandle = timer.nsecsElapsed();


        m_nbImageHandled++;
        emit imageHandled(result, source1, source2);
        if( m_nbMaxImage && m_nbImageHandled == m_nbMaxImage )
        {
            stoppedByUser = false;
            break;
        }
        QThread::usleep( (m_time - timer.nsecsElapsed() + begin )/1000 );
    }

    emit finished(stoppedByUser);
}

//grab + wait
