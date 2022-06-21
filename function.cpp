#include <vector>
#include <fftw3.h>
#include <stdio.h>
const double time_interval = 0.001;
const double k_BT          = 1;
#define REAL 0
#define IMAG 1
using namespace std;
void velocity(std::vector<double> x, fftw_complex *v){
public:
    const int N = x.size()-2;
private:
    for (unsigned int i =0; i< x.size()-2;i++){
        v[i] = (x[i+2]-x[i])/(double)(2*time_interval);
    }
}

void accelaration(std::vector<double> x, fftw_complex *a){
    for (unsigned int i=0; i<x.size()-2){
        a[i] = (a[i]+a[i+2]-2*x[i+1])/(double)(pow(time_interval, 2));
    }
}
void fft(fftw_complex *in, fftw_complex *out){
    fftw_plan plan = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTMATE);
    fftw_execute(plan);
    fftw_destory_plan(plan);
    fftw_cleanup;
}

void ifft(fftw_complex *in, fftw_complex *out)
{
    fftw_plan plan = fftw_plan_dft_1d(N, in, out, FFTW_BACKWARD, FFTW_ESTMATE);
    fftw_execute(plan);
    fftw_destory_plan(plan);
    fftw_cleanup();
    for(int i = 0; i < N; i++)
    {
        out[i][REAL] /= N;
        out[i][IMAG] /= N;
    }
}

void Convolution(fftw_complex *x, fftw_complex *y, fftw_complex *convolution )
{
    fft(x, x);
    fft(y, y);
    fftw_complex convolution(N);
    for(int i; i<N; i++)
    {
       convolution[i][REAL] = x[i][REAL]*y[i][REAL]+x[i][IMAG]*y[i][IMAG];
       convolution[i][IMAG] = -x[i][REAL]*y[i][IMAG]+x[i][IMAG]*y[i][REAL];
    }
    ifft(convolution, convolution);
    return convolution;
}



