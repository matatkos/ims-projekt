#include <cstdlib>
#include <valarray>
#include <iostream>
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
    double optimal_moisture = 40;
    double optimal_temperature = 20;
    double optimal_ph = 7.0;
    double optimal_biomass = 2;
    double optimal_salinity = 0.7;
    double optimal_vegetation_density = 4;

    double koef = 4*(1- (vegetation_density)/10);
    printf("Koef: %f\n", koef);
    double reproduction = koef * (moisture / optimal_moisture) *
                            (temperature / optimal_temperature) *
                            (ph / optimal_ph) *
                            (biomass / optimal_biomass) *
                            (salinity / optimal_salinity) *
                            (vegetation_density / optimal_vegetation_density);
    printf("reproduction: %f\n", reproduction);
    return reproduction;
}

void Grid::init_present_grid() {
    // Inicializácia vegetácie
    for(int i = 0; i < this->width; i++){
        for(int j = 0; j < this->width; j++){
            double vegetation_density = rand_double(0.1, 0.5); // Náhodná hustota vegetácie
            this->present_grid.emplace_back(i, j, vegetation_density);
        }
    }

    // Pridanie invazívnej rastliny
    int num_invasive_plants = 100; // Počet invazívnych rastlín, ktoré sa majú pridať
    for(int n = 0; n < num_invasive_plants; n++) {
        int randx = rand() % this->width;
        int randy = rand() % this->width;
        int index = order_coords(randx, randy);
        if (index >= 0 && index < this->present_grid.size()) {
            this->present_grid[index].state = rand_double(0.51, 1); // Náhodná hustota invazívnej rastliny
        }
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
        double moisture_spring = rand_double(45, 50);
        double temperature_spring;
        if(month % 12 == 3){
            printf("Marec\n");
            temperature_spring = rand_double(5, 10);
        }
        else if (month % 12 == 4){
            printf("April\n");
            temperature_spring = rand_double(10, 15);
        }
        else{
            printf("Maj\n");
            temperature_spring = rand_double(15, 20);
        }
        set_params(moisture_spring, temperature_spring,
                   ph, biomass, salinity, vegetation_density, max_population);
    }
    else if(month % 12 == 6 || month % 12 == 7 || month % 12 == 8){
        double moisture_summer = rand_double(30, 35);
        double temperature_summer;
        if(month % 12 == 6){
            printf("Jun\n");    
            temperature_summer = rand_double(20, 23);
        }
        else if (month % 12 == 7){
            printf("Jul\n");
            temperature_summer = rand_double(24, 27);
        }
        else{
            printf("Aug\n");
            temperature_summer = rand_double(28, 30);
        }
        set_params(moisture_summer, temperature_summer,
                   ph, biomass, salinity, vegetation_density, max_population);
    }
    else if(month % 12 == 9 || month % 12 == 10 || month % 12 == 11){
        double moisture_autumn = rand_double(45, 50);
        double temperature_autumn;
        if(month % 12 == 9){
            printf("Sep\n");
            temperature_autumn = rand_double(15, 25);
        }
        else if (month % 12 == 10){
            printf("Okt\n");
            temperature_autumn = rand_double(10, 15);
        }
        else{
            printf("Nov\n");
            temperature_autumn = rand_double(5, 10);
        }
        set_params(moisture_autumn, temperature_autumn,
                   ph, biomass, salinity, vegetation_density, max_population);
    }
    else if(month % 12 == 0 || month % 12 == 1 || month % 12 == 2){
        double moisture_winter = rand_double(30, 35);
        double temperature_winter;
        if(month % 12 == 0){
            printf("Dec\n");
            temperature_winter = rand_double(1, 5);
        }
        else if (month % 12 == 1){
            printf("Jan\n");
            temperature_winter = rand_double(1, 5);
        }
        else{
            printf("Feb\n");
            temperature_winter = rand_double(1, 5);
        }
        set_params(moisture_winter, temperature_winter,
                   ph, biomass, salinity, vegetation_density, max_population);
    }

    for(int i = 0; i < this->width; i++){
        for(int j = 0; j < this->width; j++){
            order = this->order_coords(i,j);
            state = present_grid[order].state;

            if (state > 0.5) { // Invazívna rastlina
                new_state = state + fertility * (1 - state) + mortality * pow(state, 2) + diffusion_operator(i, j);
                if (new_state < 0.5) new_state = 0.0; // Invazívna rastlina zomrela, nastavte na mŕtvu/nakazenú vegetáciu
            } else { // Vegetácia
                double infection_chance = 0.0;
                int infected_neighbors = 0;
                int total_neighbors = 0;

                // Prechádzajte susedné bunky
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (dx == 0 && dy == 0) continue; // Preskočte aktuálnu bunku
                        int nx = i + dx;
                        int ny = j + dy;
                        if (nx >= 0 && nx < this->width && ny >= 0 && ny < this->width) {
                            total_neighbors++;
                            if (present_grid[order_coords(nx, ny)].state > 0.5) {
                                infected_neighbors++;
                            }
                        }
                    }
                }

                if (total_neighbors > 0) {
                    infection_chance = (double)infected_neighbors / total_neighbors;
                }

                // Aktualizujte stav bunky na základe šance na infekciu
                new_state = state - infection_chance * fertility;
                //if (new_state < 0.2) new_state = rand_double(0.6, 0.8); // Ak vegetácia zomrie, nahraďte ju invazívnou rastlinou
            }

            if (new_state < 0) new_state = 0;
            if (new_state > 1) new_state = 1;
            this->future_grid[order].state = new_state;
        }
    }

    copy_future_to_present();
}

double Grid::diffusion_operator(int x, int y) {
    double diffusion = 0;
    int count = 0;
    if(x > 0){
        diffusion += this->present_grid[order_coords(x-1, y)].state;
        count++;
    }

    if(x < this->width - 1){
        diffusion += this->present_grid[order_coords(x+1, y)].state;
        count++;
    }

    if(y > 0){
        diffusion += this->present_grid[order_coords(x, y-1)].state;
        count++;
    }

    if(y < this->width - 1){
        diffusion += this->present_grid[order_coords(x, y+1)].state;
        count++;
    }
    diffusion -= count * this->present_grid[order_coords(x, y)].state;
    return diffusion;
}

void Grid::copy_future_to_present() {
    for(int i = 0; i < this->width; i++){
        for(int j = 0; j < this->width; j++){
            this->present_grid[order_coords(i,j)].state = this->future_grid[order_coords(i,j)].state;
        }
    }
}

void Grid::print_present_grid() {
    for(int i = 0; i < this->width; i++){
        for(int j = 0; j < this->width; j++){
            cout << this->present_grid[order_coords(i,j)].state << " ";
        }
        cout << std::endl;
    }
}