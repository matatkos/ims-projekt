//
// Created by matus on 9.12.2023.
//

#ifndef IMAGE_H
#define IMAGE_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "cell.h"
#include "grid.h"


#define CELL_0 Scalar (0, 0, 0)
#define CELL_1 Scalar (105,105,105)
#define CELL_2 Scalar (128,128,128)
#define CELL_3 Scalar (169,169,169)
#define CELL_4 Scalar (224, 224, 224)
#define CELL_5 Scalar (255, 255, 255)
#define CELL_6 Scalar (255, 128,0)
#define CELL_7 Scalar (255,110,0)

using namespace cv;

class Image {
public:
    Image(unsigned long width, unsigned long height);
    void create_image(Grid grid, int wait_time, int month, bool show_window);
private:
    Size2d img_size;
    unsigned long width;
    unsigned long height;

    void create_pixel(Mat img, Point pixel, Scalar color);
    double round(double var);
};


#endif
