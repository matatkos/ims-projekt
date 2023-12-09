#include <iostream>
#include "grid.h"
#include "cell.h"

int main(int argc, char** argv) {
    srand(time(NULL));
    Grid grid(100);

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
                        160000);
    }


}
