#include "pictureboxplotdestination.h"
#include <QDebug>
#include <QTimer>
#include <QWidget>
#include <QList>
#include <QProgressBar>
#include <QHBoxLayout>
#include "src/boxplot.h"

namespace media {

PictureBoxPlotDestination::PictureBoxPlotDestination(ElementFactory *aFactory, const QString &aObjectName) :
    ElementBase(aFactory, aObjectName),
    mBoxPlot(new BoxPlot())
    {
    mBoxPlot->setMaxValue(1);
    mBoxPlot->show();
    }

PictureBoxPlotDestination::~PictureBoxPlotDestination()
    {
    delete mBoxPlot;
    }

ElementBase::ParamList PictureBoxPlotDestination::getParams() const
    {
    ParamList ret;
    ret["Max"] =  mBoxPlot->maxValue();
    return ret;
    }

void PictureBoxPlotDestination::setParamValue(const QString& aName, const QVariant& aValue)
    {
    Q_UNUSED(aName);
    mBoxPlot->setMaxValue(aValue.toDouble());
    }

void PictureBoxPlotDestination::process()
    {
    foreach (const ElementBase *source, mSourceElementsReadySet)
        for (int i = 0; i < source->getFramesNo(); ++i)
            {
            const FrameBase *frame = source->getFrame(i);
            int point[2] = {0, 0};
            if (frame->getMaxDimension() == 1)
                {
                mBoxPlot->setBoxNo(frame->getDimension(0).mResolution);
                for (; point[0] < frame->getDimension(0).mResolution; ++point[0])
                    mBoxPlot->setValue(point[0], frame->getSample(point));
                }
            else if ((frame->getMaxDimension() == 2) && (frame->getDimension(0).mResolution == 1))
                {
                mBoxPlot->setBoxNo(frame->getDimension(1).mResolution);
                for (; point[1] < frame->getDimension(1).mResolution; ++point[1])
                    mBoxPlot->setValue(point[1], frame->getSample(point));
                }
            }
    emit framesProcessed();
    }

} // namespace media
