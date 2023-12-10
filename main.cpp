#include <iostream>
#include "grid.h"
#include "cell.h"
#include "image.h"

void display();

int main(int argc, char** argv) {
    srand(time(NULL));
    Grid grid(100);
    /*
    if(argc != 7){
        std::cerr << "Usage: " << argv[0] << " <moisture> <temperature> <ph> <biomass> <salinity> <vegetation_density>" << std::endl;
    }
    else{
        grid.set_params(atof(argv[1]),
                        atof(argv[2]),
                        atof(argv[3]),
                        atof(argv[4]),
                        atof(argv[5]),
                        atoi(argv[6]),
                        1600000);
    }*/
    grid.init_present_grid();
    Image image(grid.width, grid.width);

    int month = 0;
    for(int i = 0; i < 12; ++i){
        month = i % 12;

        grid.get_future_grid(month);
        image.create_image(grid, 150, month, true);
    }
    return 0;
}
