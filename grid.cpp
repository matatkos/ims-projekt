#include <cstdlib>
#include <valarray>
#include <iostream>
#include "grid.h"

void Grid::set_params(double soil_moisture, double humidity, double temperature,int vegetation_density,
                      int max_population, double sunlight) {
    this->soil_moisture = soil_moisture;
    this->temperature = temperature;
    this->vegetation_density = vegetation_density;
    this->max_population = max_population;
    this->sunlight = sunlight;	
    this->humidity = humidity;
    this->reproduction_rate = calculate_reproduction_rate(vegetation_density,
                                                          soil_moisture,
                                                          temperature,
                                                          humidity, 
                                                          sunlight);
    this->fertility = (1 - reproduction_rate);
    this->mortality = (-reproduction_rate/max_population);


}

double Grid::calculate_reproduction_rate(int vegetation_density, double soil_moisture,
                                         double temperature, double humidity ,double sunlight) {
    double optimal_soil_moisture = 40;
    double optimal_temperature = 20;
    double optimal_vegetation_density = 4;
    double optimal_sunlight = 6;
    double optimal_humidity = 60;

    double koef = 4*(1- (vegetation_density)/10);
    double reproduction = koef * (soil_moisture / optimal_soil_moisture) *
                            (temperature / optimal_temperature) *
                            (vegetation_density / optimal_vegetation_density) * 
                            (sunlight / optimal_sunlight) *
                            (humidity / optimal_humidity);
    return reproduction;
}


void Grid::init_present_grid() {
    // Inicializácia vegetácie
    this->max_population = (this->width * this->width) * 4;
    this->vegetation_density = 4;
    for(int i = 0; i < this->width; i++){
        for(int j = 0; j < this->width; j++){
            double vegetation_density = rand_double(0.1, 0.5); // Náhodná hustota vegetácie
            this->present_grid.emplace_back(i, j, vegetation_density);
        }
    }

    // Pridanie invazívnej rastliny
    int num_invasive_plants = (this->width * this->width) / 2000; // Počet invazívnych rastlín, ktoré sa majú pridať
    for(int n = 0; n < num_invasive_plants; n++) {
        int randx = rand() % this->width;
        int randy = rand() % this->width;
        std::vector<Cell>::size_type index = order_coords(randx, randy);
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
        double soil_moisture_spring = rand_double(45, 50);
        double temperature_spring;
        double sunlight_spring;
        double humidity_spring;
        if(month % 12 == 3){
            printf("Marec\n");
            temperature_spring = rand_double(-1, 8);
            if (temperature_spring == 0) {
                temperature_spring = 0.1;
            }
            sunlight_spring = rand_double(4.3, 5.6);
            humidity_spring = rand_double(69, 75);
        }
        else if (month % 12 == 4){
            printf("April\n");
            temperature_spring = rand_double(3, 15);
            sunlight_spring = rand_double(5.6, 6.6);
            humidity_spring = rand_double(69, 70);
        }
        else{
            printf("Maj\n");
            temperature_spring = rand_double(8, 20);
            sunlight_spring = rand_double(6.6, 7);
            humidity_spring = rand_double(70, 72);
        }
        set_params(soil_moisture_spring, humidity_spring, temperature_spring,
                   vegetation_density, max_population, sunlight_spring);
    }
    else if(month % 12 == 6 || month % 12 == 7 || month % 12 == 8){
        double soil_moisture_summer = rand_double(30, 35);
        double temperature_summer;
        double sunlight_summer;
        double humidity_summer;
        if(month % 12 == 6){
            printf("Jun\n");    
            temperature_summer = rand_double(11, 23);
            sunlight_summer = rand_double(7, 7.3);
            humidity_summer = rand_double(70, 72);
        }
        else if (month % 12 == 7){
            printf("Jul\n");
            temperature_summer = rand_double(13, 25);
            sunlight_summer = rand_double(7, 7.3);
            humidity_summer = rand_double(70, 72);
        }
        else{
            printf("Aug\n");
            temperature_summer = rand_double(12, 25);
            sunlight_summer = rand_double(6.9, 7.3);
            humidity_summer = rand_double(72, 75);
        }
        set_params(soil_moisture_summer, humidity_summer, temperature_summer,
                   vegetation_density, max_population, sunlight_summer);
    }
    else if(month % 12 == 9 || month % 12 == 10 || month % 12 == 11){
        double soil_moisture_autumn = rand_double(45, 50);
        double temperature_autumn;
        double sunlight_autumn;
        double humidity_autumn;
        if(month % 12 == 9){
            printf("Sep\n");
            temperature_autumn = rand_double(8, 20);
            sunlight_autumn = rand_double(4.7, 5.7);
            humidity_autumn = rand_double(75, 77);
        }
        else if (month % 12 == 10){
            printf("Okt\n");
            temperature_autumn = rand_double(4, 14);
            sunlight_autumn = rand_double(2.3, 4.7);
            humidity_autumn = rand_double(77, 83);
        }
        else{
            printf("Nov\n");
            temperature_autumn = rand_double(0, 10);
            if (temperature_autumn == 0) {
                temperature_autumn = 0.1;
            }
            sunlight_autumn = rand_double(1.8, 2.3);
            humidity_autumn = rand_double(83, 84);
        }
        set_params(soil_moisture_autumn, humidity_autumn, temperature_autumn,
                   vegetation_density, max_population, sunlight_autumn);
    }
    else if(month % 12 == 0 || month % 12 == 1 || month % 12 == 2){
        double soil_moisture_winter = rand_double(30, 35);
        double temperature_winter;
        double sunlight_winter;
        double humidity_winter;
        if(month % 12 == 0){
            printf("Dec\n");
            temperature_winter = rand_double(-4, 2);
            if (temperature_winter == 0) {
                temperature_winter = 0.1;
            }
            sunlight_winter = rand_double(1.8, 2.2);
            humidity_winter = rand_double(83, 84);
        }
        else if (month % 12 == 1){
            printf("Jan\n");
            temperature_winter = rand_double(-5, 2);
            if (temperature_winter == 0) {
                temperature_winter = 0.1;
            }
            sunlight_winter = rand_double(2.2, 3.2);
            humidity_winter = rand_double(80, 83);
        }
        else{
            printf("Feb\n");
            temperature_winter = rand_double(-5, 3);
            if (temperature_winter == 0) {
                temperature_winter = 0.1;
            }
            sunlight_winter = rand_double(3.2, 4.3);
            humidity_winter = rand_double(75, 80);
        }
        set_params(soil_moisture_winter, humidity_winter, temperature_winter,
                   vegetation_density, max_population, sunlight_winter);
    }

    for(int i = 0; i < this->width; i++){
        for(int j = 0; j < this->width; j++){
            order = this->order_coords(i,j);
            state = present_grid[order].state;

            if (state > 0.5) { // Invazívna rastlina
                new_state = state + fertility * (1 - state) + mortality * pow(state, 2);
                printf("VIAC new state: %f\n", new_state);
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
                printf("MENEJ new state: %f\n", new_state);
                if (new_state == 0) new_state = rand_double(0.51, 0.69); // Ak vegetácia zomrie, nahraďte ju invazívnou rastlinou
            }

            if (new_state < 0) new_state = 0.1;
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