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


#define CELL_0 Scalar(0, 0, 0)         // Čierna farba: prázdná/neaktívna bunka
#define CELL_1 Scalar(0, 128, 0)       // Svetlozelená: nízka hustota vegetácie
#define CELL_2 Scalar(0, 255, 0)       // Zelená: stredná hustota vegetácie
#define CELL_3 Scalar(0, 140, 255)     // Svetlooranžová: nízka hustota inváznej rastliny
#define CELL_4 Scalar(0, 69, 255)      // Oranžová: stredná hustota inváznej rastliny
#define CELL_5 Scalar(0, 0, 255)       // Červená: vysoká hustota inváznej rastliny
#define CELL_6 Scalar(0, 0, 139)       // Tmavočervená: veľmi vysoká hustota inváznej rastliny
#define CELL_7 Scalar(0, 0, 255)       // Červená: maximálna hustota inváznej rastliny


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
