#ifndef SUM_H
#define SUM_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include "KahanSum.h"


double sumKahan(std::vector<double>& v)
{

    if (v.empty()) {
        return 0.0;
    }
 KahanResult init = {0.,0.};
  KahanResult result =
  std::accumulate(v.begin(), v.end(), init, KahanSum);

  return result.sum;

}

double sum0(std::vector<double>& v)
{    
    if (v.empty()) {
        return 0.0;
    }


    return std::accumulate(v.begin(), v.end(),0.);
}




double sum1(std::vector<double>& v)
{    
    if (v.empty()) {
        return 0.0;
    }
    for(size_t i = 0; i < v.size() - 1; ++i) {
        std::sort(v.begin()+i, v.end());
        v[i+1] += v[i];
    }
    return v.back();
}
 
double sum2(std::vector<double>& v)
{    
    if (v.empty()) {
        return 0.0;
    }
    for(size_t i = 0; i < v.size() - 1; ++i) {
        std::partial_sort(v.begin() + i, v.begin() + i + 2, v.end());
        v[i+1] += v[i];
    }
    return v.back();
}
 
double sum3(std::vector<double>& v)
{    
    std::multiset<double> set(v.begin(), v.end());
std::cout<<set.size()<<"\n";
    while (set.size() > 1) {
        std::multiset<double>::const_iterator itA = set.begin();
        std::multiset<double>::const_iterator itB = ++set.begin();
        double c = *itA + *itB;
//        set.erase(itA, itB);        
        set.erase(itA, ++itB);        
        set.insert(c);

    }
    return !set.empty() ? *set.begin() 
                        : 0.0;
}

#endif




