#include "ImageOperations.h"
#include "QDebug"
#include "MainWindow.h"
#include <iostream>
#include <cstdint>

static void generateGaussian2D(int size, float sigma, float *filter) {
    int radius = size/2;
    float  sum = 0.0;
    for (int i = -radius; i <= radius; ++i) {
        for (int j = -radius; j <= radius; ++j) {
            // *(filter + i*col + j)
            int     x = i + radius;
            int     y = j + radius;
            float val = exp(-(i * i + j * j) / (2 * sigma * sigma));

            filter[y+x*size] = val;
            sum += val;
        }
    }

    //normalize filter
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            filter[y+x*size] /= sum;
        }
    }

#if 1
    float eval = 0;
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            std::cout<<filter[y+x*size]<<" ";
            eval += filter[y+x*size];
        }
        std::cout<< std::endl<< std::flush;
    }

    qDebug()<<eval;
#endif
}

void gaussianBlur(QImage *inputImage, QImage *outputImage)
{
    const OperationParameters *params = MainWindow::getInstance()->getParams();
    int    size = params->filterSize;
    float sigma = params->sigma;
    int       w = outputImage->width();
    int       h = outputImage->height();
    float filter[51*51];//allocate for the maximum size, as one dimensional array for better memory accesses

    qDebug()<<"gaussian blur filter with size and sigma:"<<size<<sigma;

    generateGaussian2D(size, sigma, filter);

    //Naive 2d convolution

    int radius = size/2;
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            float rBlured = 0;
            float gBlured = 0;
            float bBlured = 0;

            QRgb colorOut;
            for (int i = -radius; i <= radius; ++i) {
                for (int j = -radius; j <= radius; ++j) {
                    int xx = x + j;
                    int yy = y + i;

                    //mirror pixels out of range
                    if ( xx < 0 ) {
                        xx *= -1;
                    }

                    if ( yy < 0 ) {
                        yy *= -1;
                    }

                    if ( xx >= w ) {
                        xx = w - (xx-w) - 1;
                    }

                    if ( yy >= h ) {
                        yy = h - (yy-h) - 1;
                    }

                    QRgb colorIn = inputImage->pixel(xx, yy);

                    int r = qRed(colorIn);
                    int g = qGreen(colorIn);
                    int b = qBlue(colorIn);

                    int x_filt = i + radius;
                    int y_filt = j + radius;

                    rBlured += (r*filter[x_filt*size + y_filt]);
                    gBlured += (g*filter[x_filt*size + y_filt]);
                    bBlured += (b*filter[x_filt*size + y_filt]);

                    colorOut = qRgb(rBlured, gBlured, bBlured);
                    outputImage->setPixel(x, y, colorOut);
#if 0
                    //Print the values involved in the calculation of the red channel of the first pixel
                    if ( (x==0) && (y==0) ) {
                        qDebug()<<r<<filter[x_filt*size + y_filt];
                    }
#endif
                }
            }

        }
    }



}
