//
// Created by matus on 9.12.2023.
//

#include "image.h"


Image::Image(unsigned long width, unsigned long height) {
    this->width = width;
    this->height = height;
    this->img_size = Size2d(width*6 + 6, height*6 + 6);
}

void Image::create_pixel(Mat img, Point pixel, Scalar color) {
    int x = pixel.x*6;
    int y = pixel.y*6;
    for(int i = 0; i<6;++i){
        line(img, Point(x,y+i), Point(x+6,y+i), color);
    }
}

double Image::round(double var) {
    double value = (int)(var * 100 + .5);
    return (double)value / 100;
}

void Image::create_image(Grid grid, int wait_time, int month, bool show_window) {
    Mat img = Mat(img_size.height, img_size.width, CV_8UC3, Scalar(255,255,255));
    for(int i = 0; i<width; ++i){
        for(int j = 0; j<height; ++j){
            double state = round(grid.present_grid[grid.order_coords(i,j)].state);
            if(state <= 0.02){
                this->create_pixel(img, Point(i,j), CELL_0);
            }
            else if(state <= 0.05){
                this->create_pixel(img, Point(i,j), CELL_1);
            }
            else if(state <= 0.10){
                this->create_pixel(img, Point(i,j), CELL_2);
            }
            else if(state <= 0.20){
                this->create_pixel(img, Point(i,j), CELL_3);
            }
            else if(state <= 0.30){
                this->create_pixel(img, Point(i,j), CELL_4);
            }
            else if(state <= 0.40){
                this->create_pixel(img, Point(i,j), CELL_5);
            }
            else if(state <= 0.50){
                this->create_pixel(img, Point(i,j), CELL_6);
            }
            else{
                this->create_pixel(img, Point(i,j), CELL_7);
            }
        }
    }
    if(show_window){
        imshow("Image", img);
    }
    waitKey(wait_time);
}