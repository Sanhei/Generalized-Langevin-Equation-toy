#include <fftw3.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include "correlation.h"
#include "matplotlibcpp.h"
#define REAL 0
#define IMAG 1
namespace plt = matplotlibcpp;
correlation_calculation::correlation_calculation(){}
void correlation_calculation::SetTime_interval(double time_interval_)
{
    time_interval_ = time_interval;
}
void correlation_calculation::velocity(std::vector<double> x){
    N = x.size() - 2;
    velocity_ = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*N);
    Cor     = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*N);
    for (unsigned int i=0; i<x.size()-2; i++){
        velocity_[i][REAL] = (x[i+2]-x[i])/(double)(2*time_interval);
        }
}
void correlation_calculation::fft(fftw_complex *in, fftw_complex *out){
    fftw_plan plan = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(plan);
    fftw_destroy_plan(plan);
    fftw_cleanup;
    std::cout<<"Fourier transform"<<std::endl;
}

void correlation_calculation::ifft(fftw_complex *in, fftw_complex *out)
{
    fftw_plan plan = fftw_plan_dft_1d(N, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);
    std::cout<<"reverse Fourier transform"<<std::endl;
    fftw_execute(plan);

    fftw_destroy_plan(plan);
    fftw_cleanup;
    for(int i = 0; i < N; i++)
    {
        out[i][REAL] /= N;
        out[i][IMAG] /= N;
    }
}
void correlation_calculation::Convolution(fftw_complex *x, fftw_complex *y)
{
    std::cout<<"Correlation calculating"<<std::endl;
    for(int i; i<N; i++)
    {
       Cor[i][REAL] = x[i][REAL]*y[i][REAL]+x[i][IMAG]*y[i][IMAG];
       Cor[i][IMAG] = -x[i][REAL]*y[i][IMAG]+x[i][IMAG]*y[i][REAL];
    }

    ifft(Cor, Cor);
    for(int i; i<N; i++)
    {
        Correlation.push_back(Cor[i][0]);
    }
    fftw_free(Cor);
    fftw_free(x);
    fftw_free(y);
    std::cout<<"Correlation calculation end, And saved in vector<double> call .Correlation"<<std::endl;
}
void correlation_calculation::Correlation_plot(std::string &Str)
{
    std::vector<double> time;
    for(int i; i<N ; i++)
    {
        time.push_back(i*time_interval);
    }
    plt::figure;
    plt::xlabel("Time");
    plt::ylabel("Correlation");
    plt::semilogx(time, Correlation);
    plt::title(Str);
    plt::show();
}

