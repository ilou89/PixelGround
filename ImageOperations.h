#ifndef IMAGEOPERATIONS_H
#define IMAGEOPERATIONS_H
#include <QImage>
#include <QProgressDialog>

void gaussianBlur(QImage *inputImage, QImage *outputImage, QProgressDialog *progress);

#endif // IMAGEOPERATIONS_H
