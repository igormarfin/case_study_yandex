#ifndef KAHANSUM_H
#define KAHANSUM_H

#include <iostream>
#include <algorithm>



struct KahanResult
{
    double sum;
    double corr;
};


KahanResult KahanSum(KahanResult accumul, double val)
{
    KahanResult result;
    double input = val - accumul.corr;
    double sum = accumul.sum + input;
    result.corr = (sum - accumul.sum) - input;
    result.sum = sum;
    return result;
}


#endif




