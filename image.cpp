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
    Mat img = Mat(img_size.height, img_size.width, CV_8UC3, Scalar(255, 255, 255));
    for (unsigned long i = 0; i < width; ++i) {
        for (unsigned long j = 0; j < height; ++j) {
            double state = round(grid.present_grid[grid.order_coords(i, j)].state);
            if (state == 0.0){
                this->create_pixel(img, Point(i, j), CELL_0); // Čierna - prazdna bunka
            }
            else if (state > 0.0 && state <= 0.2) {
                this->create_pixel(img, Point(i, j), CELL_1); // Svetlozelená - slaba hustota vegetacie
            } else if (state > 0.2 && state <= 0.50) {
                this->create_pixel(img, Point(i, j), CELL_2); // Zelená - silna hustota vegetacie
            } else if (state > 0.5 && state <= 0.70) {
                this->create_pixel(img, Point(i, j), CELL_3); // Svetlooranžová - slaba hustota invaznej rastliny
            } else {
                this->create_pixel(img, Point(i, j), CELL_5); // Červená - silna hustota invaznej rastliny
            }
        }
    }

    std::string monthNames[] = {"Januar", "Februar", "Marec", "April", "Maj", "Jun", "Jul", "August", "September", "Oktober", "November", "December"};
    std::string monthName = monthNames[month % 12];
    Point textOrg(10, 30); // Pozícia textu v okne
    int fontFace = FONT_HERSHEY_SIMPLEX;
    double fontScale = 1;
    int thickness = 2; // Hrúbka čiary
    Scalar color(255, 255, 255); // Farba textu, napr. červená

    putText(img, monthName, textOrg, fontFace, fontScale, color, thickness);

    if (show_window) {
        imshow("Image", img);
    }
    waitKey(wait_time);
}
