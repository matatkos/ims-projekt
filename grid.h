//
// Created by matus on 9.12.2023.
//

#ifndef IMS_GRID_H
#define IMS_GRID_H

#include <vector>
#include "cell.h"

using namespace std;

class Grid {
public:
    Grid(int width){
        int size = width * width;
        this->width = width;

    }
    void init_present_grid();
    void print_present_grid();
    void get_future_grid();
    void copy_future_to_present();

    vector<Cell> present_grid;

    void set_params(
            double moisture,
            double temperature,
            double ph,
            double biomass,
            double salinity,
            int vegetation_density);
    void set_conditions();


    int width;

private:
    Cell get_present_cell(int x, int y);
    Cell get_future_cell(int x, int y);
    void fill_present_grid(int xmin, int ymin, int width, double value);

    double moisture;
    double temperature;
    double ph;
    double biomass;
    double salinity;
    int vegetation_density;
    vector<Cell> future_grid;
};


#endif //IMS_GRID_H
