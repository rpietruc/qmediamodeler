#ifndef MEDIA_PICTURESMOOTHINGTRANSFORM_H
#define MEDIA_PICTURESMOOTHINGTRANSFORM_H

#include "pictureframes.h"
#include "elementbase.h"
#include <opencv/cv.h>
#include <string>
#include <QtCore/qglobal.h>

#if defined(picturesmoothing_EXPORTS)
#  define PICTURESMOOTHINGSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PICTURESMOOTHINGSHARED_EXPORT Q_DECL_IMPORT
#endif

namespace media {

/*! smoothing the colors of the image
 */
class PICTURESMOOTHINGSHARED_EXPORT PictureSmoothingTransform : public ElementBase
    {
    Q_OBJECT

public:
    explicit PictureSmoothingTransform(ElementFactory *aFactory, const QString &aObjectName);

    int getFramesNo() const { return 1; }
    const FrameBase *getFrame(int) const { return &mPictureFrame; }

private:
    void process();

    PictureRGBFrame mPictureFrame;
    };

class PICTURESMOOTHINGSHARED_EXPORT PictureSmoothingTransformFactory : public ElementFactory
    {
    Q_OBJECT
    Q_INTERFACES(media::ElementFactory)
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QCustomPlugin")

protected:
    const char* getElementName() const { return "PictureSmoothingTransform"; }
    ElementBase* createElement(const QString &aObjectName) { return new PictureSmoothingTransform(this, aObjectName); }
    };

} // namespace media

#endif // MEDIA_PICTURESMOOTHINGTRANSFORM_H
