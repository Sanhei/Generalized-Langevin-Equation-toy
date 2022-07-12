#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include "potential.h"
#include "spline.h"
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;
histogram_constructor :: histogram_constructor(){}
void histogram_constructor::SetTemperature(double mtemperature)
{
    temperature = mtemperature;
}
void histogram_constructor::histogram_build(int discretize, std::vector<double>& trajectory)
{
    histogram_discretize = discretize;
    std::vector<int> histogram_init;
    for(unsigned int i = 0; i < trajectory.size();i++ )
    {
        histogram_init.push_back(static_cast<int>(std::floor(trajectory[i]*histogram_discretize)));
    }
    int hist_min = *std::min_element(histogram_init.begin(), histogram_init.end());
    int hist_max = *std::max_element(histogram_init.begin(), histogram_init.end());
    hist_nbins = hist_max - hist_min;
    for(unsigned int i=0; i<hist_nbins; i++)
    {
        hist_accum.push_back(0);
    }
    std::cout<<"The histogram maximum:"<<hist_max/(double)histogram_discretize<<std::endl;
    std::cout<<"The number of bins is "<<hist_nbins<<std::endl;
    std::cout<<"The bins' size is "<<1/(double)discretize<<std::endl;
    static double rescale =  1*histogram_discretize/(double)trajectory.size();

    for(unsigned int i = 0; i<hist_nbins; i++)
        hist_plot.push_back(0);
    for(int i = 0; i<hist_nbins; i++)
    {
        hist_plot[i]=(hist_min+i)/(double)histogram_discretize;
        if(i==0)
        {
            std::cout<<"Test: the minmum edge of histogram is "<<hist_min/(double)histogram_discretize<<std::endl;
        }
    }
    //This gives each point probability weight.
    int hist_index = 0;
    for(unsigned int i= 0; i < histogram_init.size(); i++)
    {
        hist_accum[histogram_init[i]-hist_min] +=  1*rescale;
    }
    histogram_init.clear();
    //Test out:
    double sum = 0;
    for( unsigned int i = 0; i<hist_accum.size(); i++)
    {
        sum += hist_accum[i]/histogram_discretize;
    }
    std::cout<<"Integrate over the histogram is "<<sum<<std::endl;
    //Free energy calculation: F = -k_BTlog(p);
    for(int j = 0; j<hist_nbins; j++)
    {
        free_energy.push_back(0);
    }
    std::cout<<"Temperature is "<<temperature<<std::endl;
    for(int j=0; j<hist_nbins; j++)
    {
        if(hist_accum[j]==0)
        {
            free_energy[j] = 0.0;
        }
        else
        {
            free_energy[j] = -temperature*log(hist_accum[j]);
        }
    }
    std::cout<<"size is "<<hist_plot.size()<<std::endl;
    }

