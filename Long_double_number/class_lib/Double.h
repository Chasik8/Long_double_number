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
//#include "Double.cpp"
namespace Dominus {
	class Double
	{

	private:
		lint loginf;
		lint inf;
		lint accuracy;
		bool mode_fast;
		const double pi = 3.141592653589793;
		vector<lint> mantissa;
		ulint point;
		bool sign();
		void formatting();
		void div2();
		Double min_element_abs();
		void labs();
		void fft(vector<complex<lb>>& a, bool invert)const;
		Double reverse_number();
	public:
		explicit Double(string s);
		explicit Double(string s, lint loginf, lint accuracy, bool mode_fast);
		Double();
		//-----------------------------------------------------
		void operator = (const Double& b);
		bool operator += (const Double& b);
		Double operator + (const Double& b) const;
		bool operator -= (const Double& b);
		Double operator - (const Double& b) const;
		Double operator * (const Double& bbconst) const;
		bool operator /= (lint k);
		bool operator *=(lint b);
		Double operator / (const Double& bb)const;
		bool operator < (const Double& b)const;
		bool operator <= (const Double& b)const;
		bool operator > (const Double& b)const;
		bool operator >= (const Double& b)const;
		bool operator != (const Double& b)const;
		bool operator == (const Double& b)const;
		bool operator << (lint kol);
		void operator >>(lint kol);
		Double mov_fast(const Double& bb)const;
		Double mov_low(const Double& bb)const;
		//-----------------------------------------------------
		void clear();
		string convert_to_string();
		void convert(string a);
		void N(lint inp);
		lint get_accuracy();
		bool get_mode_fast();
	};
	Double pi_16(lint li, lint acc, bool mode);
}