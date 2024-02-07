#include "Double.h"
using namespace Dominus;
void Double::clear() {
	while ((v.size()) * loginf > accuracy && v[v.size() - 1] == 0)
	{
		v.pop_back();
	}
}
bool Double::sign() {
	for (lint i = v.size() - 1; i >= 0; --i) {
		if (v[i] != 0) {
			if (v[i] > 0) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	return true;
}
void Double::convert(string a) {
	lint k = 0;
	if (a[0] == '-') {
		bool flag = false;
		for (lint i = a.size() - 1; i >= 1; --i) {
			if (a[i] != '.') {
				if (k % loginf == 0) {
					v.push_back(0);
					v[(k - 1) / loginf] *= -1;
				}
				v[k / loginf] += (a[i] - '0') * pow(10, k % loginf);
				++k;
				if (!flag) {
					++n;
				}
			}
			else {
				flag = true;
			}
		}
		if (!flag) {
			n = 0;
		}
		v[v.size() - 1] *= -1;
	}
	else {
		bool flag = false;
		for (lint i = a.size() - 1; i >= 0; --i) {
			if (a[i] != '.') {
				if (k % loginf == 0) {
					v.push_back(0);
				}
				v[k / loginf] += (a[i] - '0') * pow(10, k % loginf);
				++k;
				if (!flag) {
					++n;
				}
			}
			else {
				flag = true;
			}
		}
		if (!flag) {
			n = 0;
		}
	}
	formatting();
}
string Double::convert_to_string() {
	string s;
	Double nul("0");
	bool minus = false;
	if (!sign()) {
		minus = true;
		*this *= -1;
	}
	lint kol = to_string(v[v.size() - 1]).size();
	kol = (v[v.size() - 1] < 0 ? kol - 1 : kol) + (loginf * (v.size() - 1)) - n;
	bool flag = false;
	for (lint i = v.size() - 1; i >= 0; --i) {
		string b = "", bb = "";
		bool h = false;
		b += to_string(v[i]);
		if (i != v.size() - 1) {
			for (lint j = 0; j < loginf - b.size(); ++j) {
				bb += "0";
			}
		}
		bb += b;
		s += bb;
	}
	if (kol > 0) {
		s.insert(kol, ".");
	}
	else if (kol == 0) {
		s.insert(kol, ".");
		s.insert(kol, "0");
	}
	else {
		string dop = "";
		for (lint i = 0; i < abs(kol); ++i) {
			dop += "0";
		}
		s.insert(0, dop);
		s.insert(0, ".");
		s.insert(0, "0");
	}
	if (minus) {
		s.insert(0, "-");
	}
	return s;
}
bool Double::operator *=(lint b) {
	try
	{
		v[0] *= b;
		for (lint i = 1; i < v.size(); ++i) {
			v[i] *= b;
			v[i] += (v[i - 1] / inf);
			v[i - 1] %= inf;
		}
		bool h = true;
		while (h) {
			h = false;
			if (v[v.size() - 1] >= inf) {
				v.push_back(v[v.size() - 1] / inf);
				v[v.size() - 2] %= inf;
				h = true;
			}
		};

		return true;
	}
	catch (...)
	{
		std::cout << "Error_operation+" << std::endl;
		return false;
	}
}
bool Double::operator /= (lint k) {
	try
	{
		for (lint i = v.size() - 1; i > 0; --i) {
			v[i - 1] += (v[i] % k) * inf;
			v[i] /= k;
		}
		v[0] /= k;
		return true;
	}
	catch (...)
	{
		std::cout << "Error_operation+" << std::endl;
		return false;
	}
}
void Double::formatting() {
	if (n <= accuracy) {
		lint sdvik = (accuracy - n) / loginf;
		v.resize(v.size() + sdvik);
		for (lint i = v.size() - 1; i >= sdvik; --i) {
			v[i] = v[i - sdvik];
		}
		for (lint i = 0; i < sdvik; ++i) {
			v[i] = 0;
		}
		n += sdvik * loginf;
		for (lint i = 0; i < accuracy - n; ++i) {
			*this *= 10;
		}
		n += accuracy - n;
	}
	else {
		lint sdvik = (n - accuracy) / loginf;
		//for (lint i = v.size() - 1; i > v.size() - sdvik; --i) {
		//	if (i - sdvik >= 0) {
		//		v[i - sdvik] = v[i];
		//	}
		//	v[i] = 0;
		//}
		//for (lint i = v.size() - sdvik + 1; i < v.size(); ++i) {
		//	v[i] = 0;
		//}
		for (lint i = sdvik; i < v.size(); ++i) {
		    v[i - sdvik] = v[i];
		    v[i] = 0;
		}
		n -= sdvik * loginf;
		for (lint i = 0; i < n - accuracy; ++i) {
			*this /= 10;
		}
		n -= n - accuracy;
		v.resize(v.size() - sdvik);
	}
}
void Double::div2() {
	for (lint i = v.size() - 1; i > 0; --i) {
		v[i - 1] += (v[i] % 2) * inf;
		v[i] /= 2;
	}
	v[0] /= 2;
}
Double Double::min_element_abs() {
	string str_c = "0";
	for (lint i = 0; i < accuracy - 2; ++i) {
		str_c += "0";
	}
	str_c += "1";
	Double c(str_c);
	return c;
}
void Double::fft(vector<complex<lb>>& a, bool invert) {
	lint n = (lint)a.size();
	for (lint i = 1, j = 0; i < n; ++i) {
		lint bit = n >> 1;
		for (; j >= bit; bit >>= 1)
			j -= bit;
		j += bit;
		if (i < j)
			swap(a[i], a[j]);
	}
	for (lint l = 2; l <= n; l <<= 1) {
		lb ang = 2 * pi / l * (invert ? -1 : 1);
		complex<lb> wl(cos(ang), sin(ang));
		for (lint i = 0; i < n; i += l) {
			complex<lb> w(1);
			for (lint j = 0; j < l / 2; ++j) {
				complex<lb> u = a[i + j], v = a[i + j + l / 2] * w;
				a[i + j] = u + v;
				a[i + j + l / 2] = u - v;
				w *= wl;
			}
		}
	}
	if (invert) {
		for (lint i = 0; i < n; ++i) {
			a[i] /= n;
		}
	}
}
    void Double::labs() {
        if (v[0] < 0) {
            for (lint i = 0; i < v.size(); ++i) {
                v[i] *= -1;
            }
        }
    }