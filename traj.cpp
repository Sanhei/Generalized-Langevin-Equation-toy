#include <iostream>
#include "parameter.h"
//#include "potential.hpp"
#include "v_verlet.cpp"
#include <fstream>
using namespace std;

int main(int argc, char **argv)
{
    double x = -1.0; // initial position
    double temp=0;
    double xp = x;
    double y  = 0;
    ofstream file;
    file.open("trajectory.txt");
    file << "# time   position"<< std::endl;
    file << "#" << std::endl;
    for(size_t i=0; i<length; i++){
        temp = x;
        x = x_update(x, xp, y);
        y = y_update(y, temp);
        xp = temp;
        file << i*h << " " << x << std::endl;
    }
    file.close();
} 
