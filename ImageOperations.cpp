#include "ImageOperations.h"
#include "QDebug"
#include "MainWindow.h"

void gaussianBlur(QImage *inputImage, QImage *outputImage)
{
    const OperationParameters *params = MainWindow::getInstance()->getParams();
    int    size = params->filterSize;
    float sigma = params->sigma;

    qDebug()<<"gaussian blur filter with size and sigma:"<<size<<sigma;
}
