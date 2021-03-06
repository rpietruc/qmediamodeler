#ifndef VIDEOFILESOURCE_H
#define VIDEOFILESOURCE_H

#include "elementbase.h"
#include "pictureframes.h"
#include <QString>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <QtCore/qglobal.h>

#if defined(videofilesource_EXPORTS)
#  define VIDEOFILESOURCESHARED_EXPORT Q_DECL_EXPORT
#else
#  define VIDEOFILESOURCESHARED_EXPORT Q_DECL_IMPORT
#endif

namespace media {

class VIDEOFILESOURCESHARED_EXPORT VideoFileSource : public ElementBase
    {
    Q_OBJECT

public:
    explicit VideoFileSource(ElementFactory *aFactory, const QString &aObjectName);
    ~VideoFileSource();

    int getFramesNo() const { return 1; }
    const FrameBase *getFrame(int) const { return &mPictureFrame; }

    bool event(QEvent *aEvent);

private:
    void process();
    void open();

private:
    PictureRGBFrame mPictureFrame;
    CvCapture* mCapture;
    };

class VideoFileSourceFactory : public ElementFactory
    {
    Q_OBJECT
    Q_INTERFACES(media::ElementFactory)
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QCustomPlugin")

protected:
    const char* getElementName() const { return "VideoFileSource"; }
    ElementBase* createElement(const QString &aObjectName) { return new VideoFileSource(this, aObjectName); }
    };

} // namespace media


#endif // VIDEOFILESOURCE_H
