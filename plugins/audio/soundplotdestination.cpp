#include "soundplotdestination.h"
#include <QDebug>
#include "soundframe.h"
#include <cmath>
#include "plotdialog.h"

namespace media {

SoundPlotDestination::SoundPlotDestination(ElementFactory *aFactory, const QString &aObjectName) :
    ElementBase(aFactory, aObjectName),
    mPlot(new PlotDialog)
    {
    mPlot->show();
    QObject::connect(this, SIGNAL(sampleReceived(double, double, int)), mPlot, SLOT(appendSample(double, double, int)), Qt::QueuedConnection);
    }

SoundPlotDestination::~SoundPlotDestination()
    {
    delete mPlot;
    }

void SoundPlotDestination::process()
    {
    Q_ASSERT(mPlot);
    foreach (const ElementBase *source, mSourceElementsReadySet)
        for (int i = 0; i < source->getFramesNo(); ++i)
            {
            const FrameBase *frame = source->getFrame(i);
            if ((frame->getMaxDimension() == SoundFrame::Dimensions) &&
                (frame->getDimensionT(SoundFrame::Channels).mResolution <= 2) &&
                (frame->getDimensionT(SoundFrame::Channels).mResolution > 0))
                {
                Q_ASSERT(frame->getDimensionT(SoundFrame::Time).mDelta);
                mPlot->setGraphNo(frame->getDimensionT(SoundFrame::Channels).mResolution);

                int point[SoundFrame::Dimensions];
                double timeStamp = frame->getDimensionT(SoundFrame::Time).mStartLocation;
                double lastTime = 0;

                // plot every 5ms
                const int timeStep = (frame->getDimensionT(SoundFrame::Time).mDelta < 0.005 ? 0.005/frame->getDimensionT(SoundFrame::Time).mDelta : 1);
                for (point[SoundFrame::Time] = 0;
                     point[SoundFrame::Time] < frame->getDimensionT(SoundFrame::Time).mResolution;
                     point[SoundFrame::Time] += timeStep)
                    {
                    for (point[SoundFrame::Channels] = 0; point[SoundFrame::Channels] < frame->getDimensionT(SoundFrame::Channels).mResolution; ++point[SoundFrame::Channels])
                        emit sampleReceived(timeStamp, frame->getSampleT(point), point[SoundFrame::Channels]);
                    lastTime = timeStamp;
                    timeStamp += timeStep*frame->getDimensionT(SoundFrame::Time).mDelta;
                    }
                mPlot->initTimeRange(lastTime, 5); //5s plot
                mPlot->setTitle(frame->getSourceName());
                emit framesProcessed();
                }
            }
    }

} // namespace media
