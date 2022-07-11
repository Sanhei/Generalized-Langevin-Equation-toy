#include "func.cpp"
#include <cmath>
#include <vector>
#include "spline.h"
const int scale = 100;

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
    int N = traj.size() - 2;
    fftw_init_threads();
    fftw_complex *velocity_in;
    velocity_in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*(traj.size()-2));
    fftw_complex *velocity_out;
    velocity_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*(traj.size()-2));
    velocity(traj, velocity_in);
    fft(velocity_in,velocity_out, N);
    ifft(velocity_out, velocity_in, N);
    fftw_free(velocity_in);
    fftw_complex *cor;    
    cor = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*(traj.size()-2));

    Convolution(velocity_out, velocity_out, cor, N);



    std::ofstream file;
    file.open("corvv.txt");
    for(int i=0; i<1000; i++){
        file<<cor[i][0]<<std::endl;
    }
    file.close();
    fftw_free(cor);
        //
    std::vector<int> trajectory;
    std::ifstream data;
    data.open("trajectory.txt");
    if(!data)
    {
        std::cerr << "Unable to open file ";
        exit(1);
    }
    //change the location of your file;
    //ignore the string type, which normally header.
    while(data >> x >> y)
    {
        trajectory.push_back(static_cast <int> (std::floor(y*scale)));
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
        if(trajectory[i]-min<1)
        {
             cout<<"something wrong"<<endl;
        }
        if(trajectory[i]-min>327)
        {
             cout<<"something beyond"<<endl;
        }
        binscount[trajectory[i]-min] += 1*rescale;//shift the trajectory
    }
    for(long unsigned int i=0; i< 10; i++)
    {
       // cout << trajectory[i] << " " << binscount[i] << " " << trajectory[i] - binscount[i] << " " << min <<  endl;
    }
    double sum;
 
    /*
    double sum = 0;
    for (long unsigned int i=0; i<size; i++){
        std::cout<< std::fixed<<std::setprecision(2)<<position[i]<< "   "<< binscount[i]<< std::endl;
        sum += binscount[i];
    }
    //the width of bins: 1/scale
    std::cout<<"sum is "<< std::fixed<< std::setprecision(2)<<sum/scale<< std::endl;
    */
    /*
    tk::spline s;
    s.set_points(position, binscount, tk::spline::cspline);
    std::cout<<"potential "<<std::endl;
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
        */
    std::cout<<"last"<<std::endl;
    return 0;
}
