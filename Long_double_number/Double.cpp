#include "Double.h"
using namespace Dominus;
//    void lswap (Double& a,Double& b) {
//        swap(a.v,b.v);
//        swap(a.n, b.n);
//    }
//    ulint size() {
//        return v.size();
//    }
//    // количество разр€ов не больше чем 10^9
//    void copy(Double& a) {
//        v = a.v;
//        n = a.n;
//    }
//    Double lpow(lint b) {
//        Double c1=*this;
//        Double c2 = *this;
//        for (lint i = 0; i < b; ++i) {
//            c1 =c1*c2;
//        }
//        return c1;
//    }
//    lint operator [] (lint i) {
//        try
//        {
//            return v[i];
//        }
//        catch (...)
//        {
//            std::cout << "Error_operation+" << std::endl;
//            return 0;
//        }
//    }
//    Double max_element_abs() {
//        string str_c = "";
//        for (lint i = 0; i < 10; ++i) {
//            str_c += "0";
//        }
//        str_c += "1";
//        reverse(str_c.begin(), str_c.end());
//        Double c(str_c);
//        return c;
//    }
//    Double reverse_number_newton() {
//        lint kol = accuracy / loginf;
//        Double c = *this;
//        c >> (v.size()- kol-1);
//        for (lint i = 0; i < accuracy - loginf * kol; ++i) {
//            c /= 10;
//        }
//        Double a1("1"),x=c;
//        for (lint i = 0; i < accuracy; ++i) {
//            x += (a1 - c * x);
//        }
//        x >> (v.size() - kol - 1);
//        for (lint i = 0; i < accuracy - loginf * kol; ++i) {
//            x /= 10;
//        }
//        return x;
//    }

Double::Double(string s="") {
	n = 0;
	if (s == "") {
		s = "0";
	}
	convert(s);
}
Double::Double() {
	n = 0;
	string s = "0";
	convert(s);
}