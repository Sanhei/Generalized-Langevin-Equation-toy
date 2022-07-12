#ifndef HISTOGRAM
#define HISTOGRAM
#include <vector>
#include <math.h>

class histogram_constructor
{
private:
public:
        std::vector<double> hist_plot;
        std::vector<double> hist_accum;
        std::vector<double> free_energy;
        double temperature;
        int histogram_discretize;
        int hist_nbins;
       /*
        * The algorithm is here.
        * 1. Get the maximum and minimum of the trajectory.
        * 2. Distcretize 1 into "distcretize", e.g. if "distcretize = 100";
        *    then the bins size is 1/100.
        * 3. Accumlate it into the bins.
        */
        histogram_constructor();
        void SetTemperature(double mtemperature);
        void histogram_build(int discretize, std::vector<double>& trajectory);
};

#endif
