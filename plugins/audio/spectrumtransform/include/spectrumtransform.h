#ifndef SPECTRUMTRANSFORM_H
#define SPECTRUMTRANSFORM_H

#include "elementbase.h"
#include "spectrumframe.h"
#include <QtCore/qglobal.h>

#if defined(SPECTRUMTRANSFORM_LIBRARY)
#  define SPECTRUMTRANSFORMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SPECTRUMTRANSFORMSHARED_EXPORT Q_DECL_IMPORT
#endif

namespace media {

class SPECTRUMTRANSFORMSHARED_EXPORT SpectrumTransform : public ElementBase
    {
    Q_OBJECT

public:
    explicit SpectrumTransform(ElementFactory *aFactory, const QString &aObjectName);

    int getFramesNo() const { return 1; }
    const FrameBase *getFrame(int) const { return &mSpectrumFrame; }

//    ParamList getParams() const;

public slots:
//    void setParamValue(const QString& aName, const QVariant& aValue);

private slots:
    void setResolution(int aResolution);

private:
    void process();
    SpectrumFrame mSpectrumFrame;
    };

class SPECTRUMTRANSFORMSHARED_EXPORT SpectrumTransformFactory : public ElementFactory
    {
    Q_OBJECT
    Q_INTERFACES(media::ElementFactory)
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QCustomPlugin")

protected:
    const char* getElementName() const { return "SpectrumTransform"; }
    ElementBase* createElement(const QString &aObjectName) { return new SpectrumTransform(this, aObjectName); }
    };

} // namespace media

#endif // SPECTRUMTRANSFORM_H
