#include <fftw3.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#define REAL 0
#define IMAG 1
const double time_interval = 0.001;

using namespace std;
void velocity(std::vector<double> x, fftw_complex *v){
    int N = x.size() - 2;
    for (unsigned int i=0; i<x.size()-2; i++){
        v[i][0] = (x[i+2]-x[i])/(double)(2*time_interval);
        }
}
void fft(fftw_complex *in, fftw_complex *out, int N){
    fftw_plan plan = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(plan);
    fftw_destroy_plan(plan);
    fftw_cleanup;
    std::cout<<"right"<<std::endl;
}

void ifft(fftw_complex *in, fftw_complex *out, int N)
{
    fftw_plan plan = fftw_plan_dft_1d(N, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);
    std::cout<<"right"<<std::endl;
    fftw_execute(plan);

    fftw_destroy_plan(plan);
    fftw_cleanup;
    for(int i = 0; i < N; i++)
    {
        out[i][REAL] /= N;
        out[i][IMAG] /= N;
    }
}
void Convolution(fftw_complex *x, fftw_complex *y,fftw_complex *cor, int N)
{
    std::cout<<"before"<<std::endl;
    for(int i; i<N; i++)
    {
       cor[i][REAL] = x[i][REAL]*y[i][REAL]+x[i][IMAG]*y[i][IMAG];
       cor[i][IMAG] = -x[i][REAL]*y[i][IMAG]+x[i][IMAG]*y[i][REAL];
    }
    std::cout<<"after"<<std::endl;

    ifft(cor, cor,  N);
}



