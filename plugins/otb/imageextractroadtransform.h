#ifndef MEDIA_IMAGEEXTRACTROADTRANSFORM_H
#define MEDIA_IMAGEEXTRACTROADTRANSFORM_H

#include "otbframes.h"
#include "imageframes.h"
#include "elementbase.h"
#include <QtCore/qglobal.h>

#if defined(imagedenoising_EXPORTS)
#  define IMAGEEXTRACTROADSHARED_EXPORT Q_DECL_EXPORT
#else
#  define IMAGEEXTRACTROADSHARED_EXPORT Q_DECL_IMPORT
#endif

namespace media {

class IMAGEEXTRACTROADSHARED_EXPORT ImageExtractRoadTransform : public ElementBase
    {
    Q_OBJECT

public:
    explicit ImageExtractRoadTransform(ElementFactory *aFactory, const QString &aObjectName);

    int getFramesNo() const { return mPointsFrameSet.size(); }
    const FrameBase *getFrame(int aIndex) const { return &mPointsFrameSet.at(aIndex); }

private:
    void process();

private:
    QVector<PointsFrame> mPointsFrameSet;
    };

class IMAGEEXTRACTROADSHARED_EXPORT ImageExtractRoadTransformFactory : public ElementFactory
    {
    Q_OBJECT
    Q_INTERFACES(media::ElementFactory)
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QCustomPlugin")

protected:
    const char* getElementName() const { return "ImageExtractRoadTransform"; }
    ElementBase* createElement(const QString &aObjectName) { return new ImageExtractRoadTransform(this, aObjectName); }
    };

} // namespace media

#endif // MEDIA_IMAGEEXTRACTROADTRANSFORM_H
