#include "KahanSum.h"
#include "Sum.h"
#include "CpuTime.h"
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{

    vector<double> input={0.01, 0.001, 0.0001, 0.000001, 0.00000000001};

  ///
  cout<<"Test of Kahan Sum\n";
  KahanResult init = {0.,0.};
  KahanResult result =
  std::accumulate(input.begin(), input.end(), init, KahanSum);

  std::cout << "Kahan Sum: " << result.sum << std::endl;
  std::cout << "Kahan Error: " << result.corr << std::endl;
    


   ///
    cout<<"Test of the fastest and robust algorithm for summation\n";
    for (size_t i =0; i<input.size()-1; i++) {
        input[i+1] += input[i];
    }
    double sum_v2 = input.back();
    std::cout << "Result of the robust algorithm: " << sum_v2 << std::endl;

    ///
    cout<<"Test of the std::accumulate for summation\n";
    input={0.01, 0.001, 0.0001, 0.000001, 0.00000000001};
    double sum_v3 = std::accumulate(input.begin(), input.end(),0.);
    cout << "Result of the std::accumulate algorithm: " << sum_v3 << "\n";


    cout<<"CPU Timings\n";


//    unsigned int numEvt=1000000L; // 1M is enough
    unsigned int numEvt=10000L; // 10K is enough
    std::vector<double> records_maxi(numEvt,0.33);
    std::vector<double> records_maxi2(numEvt,0.33);
    std::vector<double> records_maxi3(numEvt,0.33);

    cout<<"KahanSum:\n";    



//  Start/Stop Timers
    double wall01 = get_wall_time();
    double cpu01  = get_cpu_time();

    double sum_v4 = sumKahan(records_maxi);

    double wall02 = get_wall_time();
    double cpu02  = get_cpu_time();

    cout<<"Result = "<<sum_v4<<"\n";
    cout<<"Delta Wall Time = "<<wall02-wall01<<"\n";
    cout<<"Delta CPU Time = "<<cpu02-cpu01<<"\n";

    cout<<"Robust Sum:\n";    

    double wall11 = get_wall_time();
    double cpu11  = get_cpu_time();

    double sum_v5 = sum0(records_maxi);

    double wall12 = get_wall_time();
    double cpu12  = get_cpu_time();

    cout<<"Result = "<<sum_v5<<"\n";
    cout<<"Delta Wall Time = "<<wall12-wall11<<"\n";
    cout<<"Delta CPU Time = "<<cpu12-cpu11<<"\n";
    

    cout<<"sum2:\n";    

    double wall21 = get_wall_time();
    double cpu21  = get_cpu_time();

    double sum_v6 = sum2(records_maxi);

    double wall22 = get_wall_time();
    double cpu22  = get_cpu_time();

    cout<<"Result = "<<sum_v6<<"\n";
    cout<<"Delta Wall Time = "<<wall22-wall21<<"\n";
    cout<<"Delta CPU Time = "<<cpu22-cpu21<<"\n";


    cout<<"sum3:\n";    

    double wall31 = get_wall_time();
    double cpu31  = get_cpu_time();

    double sum_v7 = sum3(records_maxi2);

    double wall32 = get_wall_time();
    double cpu32  = get_cpu_time();

    cout<<"Result = "<<sum_v7<<"\n";
    cout<<"Delta Wall Time = "<<wall32-wall31<<"\n";
    cout<<"Delta CPU Time = "<<cpu32-cpu31<<"\n";


    cout<<"sum1:\n";    

    double wall41 = get_wall_time();
    double cpu41  = get_cpu_time();

    double sum_v8 = sum1(records_maxi3);

    double wall42 = get_wall_time();
    double cpu42  = get_cpu_time();

    cout<<"Result = "<<sum_v8<<"\n";
    cout<<"Delta Wall Time = "<<wall42-wall41<<"\n";
    cout<<"Delta CPU Time = "<<cpu42-cpu31<<"\n";




    cout<<"Tests\n";

    cout<<"test: std::accumulate sum == Robust sum\n";
    assert(sum_v3 == sum_v2 );

    cout<<"test: Kahan sum == Robust sum\n";
    assert(result.sum == sum_v2 );





    return 0;
}

