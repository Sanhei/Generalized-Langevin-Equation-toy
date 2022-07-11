#include <vector>
#include <fftw3.h>
#include <iostream>
const double time_interval = 0.001;
const double k_BT          = 1;
#define REAL 0
#define IMAG 1
using namespace std;
void velocity(fftw_complex *x, fftw_complex *v, int Number_traj){
    for (int i =0; i< Number_traj-2;i++){
        v[i][0] = (x[i+2][0]-x[i][0])/(double)(2*time_interval);
    }
}

void farward(fftw_complex *in, fftw_complex *out, int N){
    fftw_plan plan = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(plan);
    fftw_destroy_plan(plan);
}

void backward(fftw_complex *in, fftw_complex *out, int N)
{
    fftw_plan plan = fftw_plan_dft_1d(N, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);
    fftw_execute(plan);
    fftw_destroy_plan(plan);

    for(int i = 0; i < N; i++)
    {
        out[i][0] /= N;
        out[i][1] /= N;
    }
}

void Convolution(fftw_complex *x, fftw_complex *y,fftw_complex *cor, int N )
{
    farward(x, x, N);
    farward(y, y, N);
    fftw_complex convolution;
    std::cout<<"right"<<std::endl;
    for(int i; i<N; i++)
    {
       convolution[i][0] = x[i][REAL]*y[i][REAL]+x[i][IMAG]*y[i][IMAG];
       convolution[i][1] = -x[i][REAL]*y[i][IMAG]+x[i][IMAG]*y[i][REAL];
    }
    std::cout<<"after"<<std::endl;
    backward(convolution, cor);
}



