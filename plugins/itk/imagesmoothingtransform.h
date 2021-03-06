#ifndef MEDIA_IMAGESMOOTHINGTRANSFORM_H
#define MEDIA_IMAGESMOOTHINGTRANSFORM_H

#include "imageframes.h"
#include "elementbase.h"
#include <QtCore/qglobal.h>

#if defined(imagesmoothing_EXPORTS)
#  define IMAGESMOOTHINGSHARED_EXPORT Q_DECL_EXPORT
#else
#  define IMAGESMOOTHINGSHARED_EXPORT Q_DECL_IMPORT
#endif

namespace media {

class IMAGESMOOTHINGSHARED_EXPORT ImageSmoothingTransform : public ElementBase
    {
    Q_OBJECT

public:
    explicit ImageSmoothingTransform(ElementFactory *aFactory, const QString &aObjectName);

    int getFramesNo() const { return 1; }
    const FrameBase *getFrame(int) const { return &mImageFrame; }

private:
    void process();

private:
    GrayImageFrame mSrcFrame;
    GrayImageFrame mImageFrame;
    };

class IMAGESMOOTHINGSHARED_EXPORT ImageSmoothingTransformFactory : public ElementFactory
    {
    Q_OBJECT
    Q_INTERFACES(media::ElementFactory)
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QCustomPlugin")

protected:
    const char* getElementName() const { return "ImageSmoothingTransform"; }
    ElementBase* createElement(const QString &aObjectName) { return new ImageSmoothingTransform(this, aObjectName); }
    };

} // namespace media

#endif // MEDIA_IMAGESMOOTHINGTRANSFORM_H
