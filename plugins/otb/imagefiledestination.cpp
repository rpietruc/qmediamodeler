#include "imagefiledestination.h"
#include <otbImageFileWriter.h>
#include "otbframes.h"
#include <QDebug>

//using namespace otb;
//using namespace itk;
using namespace std;

namespace media {

ImageFileDestination::ImageFileDestination(ElementFactory *aFactory, const QString &aObjectName) :
    FileDestination(aFactory, aObjectName)
    {
    }

void ImageFileDestination::process()
    {
    foreach (const ElementBase *source, mSourceElementsReadySet)
        for (int i = 0; i < source->getFramesNo(); ++i)
            {
            const FrameBase *frame = source->getFrame(i);
            ImageOtbFrame rgbImg;
            if (rgbImg.isCopyable(*frame))
                {
                rgbImg.resizeAndCopyFrame(*frame);
                typedef otb::ImageFileWriter<ImageOtbFrame::ImageType> WriterType;
                WriterType::Pointer writer = WriterType::New();
                writer->SetFileName(getNextFilePath().toStdString());
                writer->SetInput(rgbImg.operator ImageType::Pointer());
                try
                    {
                    writer->Update();
                    }
                catch (itk::ExceptionObject & exp)
                    {
                    qWarning() << "ITK::Exception catched : " << exp.what();
                    }
                emit framesProcessed();
                }
            }
    }

} // namespace media
