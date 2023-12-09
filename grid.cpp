#include <cstdlib>
#include "grid.h"

void Grid::set_params(double moisture, double temperature, double ph,
                      double biomass, double salinity,int vegetation_density,
                      int max_population) {
    this->moisture = moisture;
    this->temperature = temperature;
    this->ph = ph;
    this->biomass = biomass;
    this->salinity = salinity;
    this->vegetation_density = vegetation_density;
    this->max_population = max_population;
    this->reproduction_rate = calculate_reproduction_rate(vegetation_density,
                                                          moisture,
                                                          temperature,
                                                          ph,
                                                          biomass,
                                                          salinity);
    this->fertility = (1 - reproduction_rate);
    this->mortality = (-reproduction_rate/max_population);
}

double Grid::calculate_reproduction_rate(int vegetation_density, double moisture,
                                         double temperature, double ph,
                                         double biomass, double salinity) {
    double optimal_moisture = 0.4;
    double optimal_temperature = 20;
    double optimal_ph = 7.0;
    double optimal_biomass = 0.02;
    double optimal_salinity = 0.7;
    double optimal_vegetation_density = 4;

    double koef = 4*(1- (vegetation_density)/5);

    double reproduction = koef * (moisture * optimal_moisture) *
                            (temperature / optimal_temperature) *
                            (ph / optimal_ph) *
                            (biomass * optimal_biomass) *
                            (salinity / optimal_salinity) *
                            (vegetation_density / optimal_vegetation_density);
    return reproduction;
}

void Grid::init_present_grid() {
    for(int i = 0; i < this->width; i++){
        for(int j = 0; j < this->width; j++){
            this->present_grid.emplace_back(i,j,0);
        }
    }
    int randx = 0;
    int randy = 0;
    int randcnt = 0;
    double rand_dens;
    for(int i = 0; i < 20; i++){
        randcnt = rand() % 20;
        randx = rand() % (this->width - randcnt);
        randy = rand() % (this->width - randcnt);
        rand_dens = rand_double(0.07, 0.1);
        this->fill_present_grid(randx, randy, randcnt, rand_dens);
    }
}

double Grid::rand_double(double min, double max) {
    return (double)rand() / RAND_MAX * (max - min) + min;
}

void Grid::fill_present_grid(int xmin, int ymin, int width, double value) {
    for(int i = xmin; i < xmin + width; i++){
        for(int j = ymin; j < ymin + width; j++){
            this->present_grid[this->order_coords(i,j)].state = value;
        }
    }
}

int Grid::order_coords(int x, int y) {
    return x + (y * this->width);
}

void Grid::get_future_grid(int month) {
    double order;
    double state;
    double new_state;

    if(month % 12 == 3 || month % 12 == 4 || month % 12 == 5){
        double moisture_spring = rand_double(0.45, 0.50);
        double temperature_spring;
        if(month % 12 == 3){
            temperature_spring = rand_double(5, 10);
        }
        else if (month % 12 == 4){
            temperature_spring = rand_double(10, 15);
        }
        else{
            temperature_spring = rand_double(15, 20);
        }
        set_params(moisture_spring, temperature_spring,
                   ph, biomass, salinity, vegetation_density, max_population);
    }
    else if(month % 12 == 6 || month % 12 == 7 || month % 12 == 8){
        double moisture_summer = rand_double(0.30, 0.35);
        double temperature_summer;
        if(month % 12 == 6){
            temperature_summer = rand_double(20, 23);
        }
        else if (month % 12 == 7){
            temperature_summer = rand_double(24, 27);
        }
        else{
            temperature_summer = rand_double(28, 30);
        }
        set_params(moisture_summer, temperature_summer,
                   ph, biomass, salinity, vegetation_density, max_population);
    }
    else if(month % 12 == 9 || month % 12 == 10 || month % 12 == 11){
        double moisture_autumn = rand_double(0.45, 0.50);
        double temperature_autumn;
        if(month % 12 == 9){
            temperature_autumn = rand_double(15, 25);
        }
        else if (month % 12 == 10){
            temperature_autumn = rand_double(10, 15);
        }
        else{
            temperature_autumn = rand_double(5, 10);
        }
        set_params(moisture_autumn, temperature_autumn,
                   ph, biomass, salinity, vegetation_density, max_population);
    }
    else if(month % 12 == 0 || month % 12 == 1 || month % 12 == 2){
        double moisture_winter = rand_double(0.30, 0.35);
        double temperature_winter;
        if(month % 12 == 0){
            temperature_winter = rand_double(0, 5);
        }
        else if (month % 12 == 1){
            temperature_winter = rand_double(0, 5);
        }
        else{
            temperature_winter = rand_double(0, 5);
        }
        set_params(moisture_winter, temperature_winter,
                   ph, biomass, salinity, vegetation_density, max_population);
    }

    for(int i = 0; i < this->width; i++){
        for(int j = 0; j < this->width; j++){
            order = this->order_coords(i,j);
            state = present_grid[order].state;
            
        }
    }
}
