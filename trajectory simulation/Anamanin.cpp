#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <fftw3.h>
#include "function.cpp"

int main(int argc, char **argv){
    std::ifstream inputfile;
    inputfile.open("trajectory.txt");
    if(!inputfile){
        std::cout<<"unable to open the file";
        exit(1);
    }
    double x, y;
    std::vector<double> traj_;
    while(inputfile>>x>>y){
        traj_.push_back(y);
    }
    unsigned int Number_traj = traj_.size();
    //Here just do nothing but transfer vector type to complex
    fftw_init_threads();
    fftw_complex *traj;
    traj = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*Number_traj);
    for(int i; i<Number_traj; i++)
        traj[i][0] = traj_[i];
    std::vector<double> ().swap(traj_);
    //Clear the memory of traj_, so the traj saved in traj as a fftw_complex
    fftw_complex *velocity_in;
    velocity_in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*(Number_traj-2));
    velocity(traj, velocity_in, Number_traj);

    fftw_complex *corvv;
    corvv = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*(Number_traj-2));
    Convolution(velocity_in, velocity_in, Number_traj);
    //The above procedure for velocity convolution.
    std::ofstream file;
    file.open("Convolution.txt");
    for(int i=0; i<1000; i++){
        file<<corvv[i][0]<<std::endl;
    }
    file.close();
    fftw_free(corvv);
/*
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
    //don't need
    double sum = 0;
    for (long unsigned int i=0; i<size; i++){
        std::cout<< std::fixed<<std::setprecision(2)<<position[i]<< "   "<< binscount[i]<< std::endl;
        sum += binscount[i];
    }
    //the width of bins: 1/scale
    std::cout<<"sum is "<< std::fixed<< std::setprecision(2)<<sum/scale<< std::endl;
    //don't need
    tk::spline s;
    s.set_points(position, binscount, tk::spline::cspline);

    std::ofstream output;
    output.open("potential.txt");
    for(int i=0; i<size; i++)
    {
        x = (i+min)/(double)scale;
        y = s(x);
        output<< x<<"  "<< s(x)<< std::endl;
    }
    if(output.is_open())
        output.close();
    std::cout<<"right"<<std::endl;
    return 0;
*/
}
