#include <fftw3.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include "spline.h"
#include <cstdio>
#include "function.cpp"
#include <iomanip>
#include <math.h>
const int scale = 50;
int main(int argc, char **argv){
    std::vector<int> trajectory;
    std::vector<double> traj;
    double x, y;
    //Because my trajectory file have two column, and only read the second one;
    //Read data from file and put it into vector trajectory
    //
    std::ifstream inputfile;
    inputfile.open("trajectory.txt");
    if(!inputfile)
    {
        std::cout<< "Unable to open file ";
        exit(1);
    }
    //change the location of your file;
    //ignore the string type, which normally header.
    while (inputfile >> x >> y)
    {
        trajectory.push_back(static_cast <int> (std::floor(y*scale)));
        traj.push_back(y);
        //Since floor will return to double type, so static_cast <int> get a int type
    }
    //find the mindest value of array
    int min = *std::min_element(trajectory.begin(), trajectory.end());
    int max = *std::max_element(trajectory.begin(), trajectory.end());
    std::cout<<"minist is "<< min<<std::endl;
    int size = max - min;
    std::cout<<"size is "<< size << std::endl;
    //initial a size of (max-min) vector as Y
    std::vector<double> binscount(size);
    //initalize a size of (max-min) vector as X
    std::vector<double> position(size);
    //for rescale
    static double rescale = 1*scale/(double)trajectory.size();
    double temp = 0.;
    for(int i=0; i<size; i++){
            temp = (min+i)/(double)scale;
            position[i]=temp;
    }
    //

    for(long unsigned int i=0; i< trajectory.size(); i++)
    {
        binscount[trajectory[i]-min] += 1*rescale;//shift the trajectory
    }
    //from here we got the probability stored in binscount
    //we transfer the probability to potential energy by U= -k_B T log(P) 
    //and k_BT we put into the file function.cpp
    //Here for convinience and memory we set binscount to save potential.
    for( unsigned int i = 0; i < size; i++)
    {
        binscount[i] = -k_BT*log(binscount[i]);
    }



    tk::spline potential;
    potential.set_points(position, binscount, tk::spline::cspline);
    // Now we need to clear our memory and
    binscount.clear();
    position.clear();
    //velocity saved in fft_complex v
    fftw_complex v;
    veloctiy(traj, v);
    fftw_complex corvv;
    Convolution(v, v, corvv);
    //Free the memory of v
    fftw_free(v);
    //Get potential
    fftw_complex g_p;
    for(int i=1; i < N-1; i++)
    {
        g_p[i-1][REAL] = potential(traj[i]);
        g_p[i-1][IMAG] = 0
    }
    fftw_complex trajf;
    //Transfter traj into complex space type to prepare
    for(int i=1; i< N-1;
    return 0;
}
