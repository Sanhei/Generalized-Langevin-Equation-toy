#include <fftw3.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
int main(int argc, char **argv){
    std::ifstream inputfile;
    inputfile.open("trajectory.txt");
    if(!inputfile)
    {
        std::cout<<"unable to openfile";
        exit(1);
    }
    double x, y;
    std::vector<double> traj;
    while (inputfile>> x>> y){
        traj.push_back(y);
    }
    fftw_init_threads();
    fftw_complex *out;
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*traj.size());
    fftw_plan plan = fftw_plan_dft_r2c_1d(traj.size(), traj.data(), out, FFTW_ESTIMATE);
    fftw_execute(plan);
    fftw_destroy_plan(plan);
    std::cout<<"right"<<std::endl;
    std::ofstream file;
    file.open("FFT.txt");
    for(int i=0; i<1000; i++){
        file<<out[i][0]<<std::endl;
    }
    file.close();
    fftw_free(out);
}
