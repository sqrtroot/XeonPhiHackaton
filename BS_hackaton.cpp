// BS_hackaton.cpp : Defines the entry point for the console application.
#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>

#include "tbb/tbb.h"

#ifdef __GNUC__
#define M_SQRT1_2 0.707106781186547524401
#endif
#define M_PI 3.14159265358979323846
#define local_cores 4
#define phi_cores 272

double norm_cdf(double value)
{
    return 0.5 * erfc(-value * M_SQRT1_2);
}

double d1(double S, double K, double r, double v, double T)
{
    return (log(S / K) + r*T) / (v*(pow(T, 0.5))) + 0.5*v*(pow(T, 0.5));
}

double d2(double S, double K, double r, double v, double T)
{
    return d1(S, K, r, v, T) - v*(pow(T, 0.5));
}

// vanilla european call price based on
// underlying S, strike K, risk-free rate r, volatility of
// underlying sigma and time to maturity T
double call_price(double S, double K, double r, double v, double T) 
{
    return S * norm_cdf(d1(S, K, r, v, T)) - K*exp(-r*T) * norm_cdf(d2(S, K, r, v, T));
}

// vanilla european put price based on
// underlying S, strike K, risk-free rate r, volatility of
// underlying sigma and time to maturity T
double put_price(double S, double K, double r, double v, double T) 
{
    return -S * norm_cdf(-d1(S, K, r, v, T)) + K*exp(-r*T) * norm_cdf(-d2(S, K, r, v, T));
}

struct params{
    double S;
    double K;
    double r;
    double v;
    double T;
};

std::vector<params> calculation_queue;

int main(int argc, char **argv) 
{
    double r = 0.02; // risk-free interest rate (2%)
    double v = 0.2; // volatility of the underlying (20%)
    double T = 1.0; // 1 year to expiry


    std::ifstream fi;
    std::istringstream is;
    std::string line;
    fi.open("Sample_SPX_20151001_to_20151030.csv");
    std::array<std::string, 20> columns;
    while (getline(fi, line, '\n')) {
        is.str(line);
        for (size_t index = 0; getline(is, columns[index], ','); index++);
        is.clear();
        // if (columns[0 /* underlying */] != "SPXW") continue;
        double S = atof(columns[1 /* underlying_last */].c_str());
        double K = atof(columns[8 /* strike */].c_str());
        calculation_queue.push_back({S,K,r,v,T});
    }
    fi.close();

    // auto diff = calculation_queue.length() / local_cores + (calculation_queue.length() % local_cores == 0 ? 0 : 1);

    auto start = std::chrono::high_resolution_clock::now();
    parallel_for( blocked_range<size_t>(0,calculation_queue.length()), 
            [](const blocked_range<size_t>& r) {
                      for(size_t i=r.begin(); i!=r.end(); ++i){
                            auto values = calculation_queue[i];
                            call_price(values.S,values.K,values.r,values.v,values.T);
                            put_price(values.S,values.K,values.r,values.v,values.T);
                      }
                  }
            );

    auto end = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    std::cout << "Calculation took: " << diff << "ms" << "\n";

    // Exercise 1: read the CSV file and execute above formulas (call_price, put_price)
    //  on each listed option price. Then leverage the Xeon Phi to do it in parallel.
    //

    // Exercise 2: try to find 'v' (volatility) by reversing the call_price function.
    //  Say you start with the value for 'call', S, K, r, T, but not v. And try to 
    //  solve what the input value 'v' should be to get the value for 'call'. 
    //
    // This means you need to invoke call_price() many times (trying different
    //  values for volatility) until you find a return value that matches the
    //  call value.

    return 0;
}
