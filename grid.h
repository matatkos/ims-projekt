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
        present_grid.reserve(size);
        future_grid.reserve(size);
    }
    void init_present_grid();
    void print_present_grid();
    void get_future_grid(int month);
    void copy_future_to_present();

    double calculate_reproduction_rate(int vegetation_density, double moisture,
                                       double temperature, double ph,
                                       double biomass, double salinity);

    vector<Cell> present_grid;

    void set_params(
            double moisture,
            double temperature,
            double ph,
            double biomass,
            double salinity,
            int vegetation_density,
            int max_population);

    void set_conditions();
    int order_coords(int x, int y);;

    int width;

private:
    Cell get_present_cell(int x, int y);
    Cell get_future_cell(int x, int y);
    double diffusion_operator(int x, int y);
    void fill_present_grid(int xmin, int ymin, int width, double value);
    double rand_double(double min, double max);


    double moisture;
    double temperature;
    double ph;
    double biomass;
    double salinity;
    int vegetation_density;
    int max_population;
    double reproduction_rate;
    double fertility;
    double mortality;

    vector<Cell> future_grid;
};


#endif //IMS_GRID_H
