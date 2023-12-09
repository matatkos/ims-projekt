//
// Created by matus on 9.12.2023.
//

#ifndef CELL_H
#define CELL_H

class Cell {

public:
    Cell(int x, int y, double state){
        setCell(x, y, state);
    }
    Cell(void){
        setCell(0, 0, 0);
    }
    void setCell(int x, int y, double state);
    double state;
    int x;
    int y;
};

#endif
