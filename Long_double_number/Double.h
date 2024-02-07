#pragma once
#define _CRT_DISABLE_PERFCRIT_LOCKS
#include <iostream>
#define _CRT_DISABLE_PERFCRIT_LOCKS
#include <string>
#define _CRT_DISABLE_PERFCRIT_LOCKS
#include <algorithm>
#define _CRT_DISABLE_PERFCRIT_LOCKS
#include <vector>
#define _CRT_DISABLE_PERFCRIT_LOCKS
#include <cmath>
#define _CRT_DISABLE_PERFCRIT_LOCKS
#include <ctime>
#define _CRT_DISABLE_PERFCRIT_LOCKS
#include <complex>
using namespace std;
typedef long long int lint;
typedef unsigned long long int ulint;
typedef double lb;
#define inf 100000
#define loginf 5
#define accuracy 1000
#define pi 3.14159265358979323846264338327950288419716939937510
//#include "Double.cpp"
namespace Dominus {
    class Double
    {
    private:
        vector<lint> v;
        ulint n;
    public:
        Double(string s);
        Double();
        //-----------------------------------------------------
        bool operator += (const Double& b);
        Double operator + (const Double& b);
        bool operator -= (const Double& b);
        Double operator - (const Double& b);
        Double operator * (const Double& bb);
        bool operator /= (lint k);
        bool operator *=(lint b);
        Double operator / (const Double& bb);
        bool operator < (const Double& b);
        bool operator <= (const Double& b);
        bool operator > (const Double& b);
        bool operator >= (const Double& b);
        bool operator != (const Double& b);
        bool operator == (const Double& b);
        bool operator << (lint kol);
        void operator >>(lint kol);
        //-----------------------------------------------------
        void clear();
        bool sign();
        void convert(string a);
        void formatting();
        string convert_to_string();
        void div2();
        Double min_element_abs();
        void labs();
        void fft(vector<complex<lb>>& a, bool invert);
        //-----------------------------------------------------
        void exp();
        Double asin();
        Double pi_16();
        Double pi_1_div();
    };
}