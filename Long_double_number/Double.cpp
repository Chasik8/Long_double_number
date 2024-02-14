#include "Double.h"
using namespace Dominus;

//class Double::Double {
//public:
//	void clear() {
//		while ((v.size()) * loginf > accuracy && v[v.size() - 1] == 0)
//		{
//			v.pop_back();
//		}
//	}
//
//};

Double::Double(string s) {
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
	Double c("0");
	c.v[0] = 10;
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
	if (!sign()) {
		for (lint i = 0; i < v.size(); ++i) {
			v[i] *= -1;
		}
	}
}
bool Double::operator += (const Double& b) {
	try
	{
		if (v.size() < b.v.size()) {
			for (lint i = 0; v.size() < b.v.size(); ++i) {
				v.push_back(0);
			}
		}
		if (b.v.size() > 0) {
			v[0] += b.v[0];
			for (lint i = 1; i < v.size(); ++i) {
				if (i < b.v.size()) {
					v[i] += b.v[i];
				}
				v[i] += v[i - 1] / inf;
				v[i - 1] %= inf;
			}
			if (v[v.size() - 1] / inf >= 1) {
				v.push_back(v[v.size() - 1] / inf);
				v[v.size() - 2] %= inf;
			}
			if (v.size() >= 2) {
				if (!sign()) {
					for (lint i = 0; i < v.size() - 1; ++i) {
						if (v[i] > 0) {
							v[i] -= inf;
							++v[i + 1];
						}
					}
				}
				else {
					for (lint i = v.size() - 2; i >= 0; --i) {
						v[i] += inf;
						--v[i + 1];
					}
					for (lint i = 0; i < v.size() - 1; ++i) {
						if (v[i] >= inf) {
							v[i] -= inf;
							++v[i + 1];
						}
					}
				}
			}
			clear();

			return true;
		}
	}

	catch (...)
	{
		std::cout << "Error_operation+=" << std::endl;
		return false;
	}
}
bool Double::operator -= (const Double& b) {
	try
	{
		Double c = b;
		for (lint i = 0; i < lint(b.v.size()); ++i) {
			c.v[i] *= -1;
		}
		*this += c;
		return true;
	}
	catch (...)
	{
		std::cout << "Error_operation-=" << std::endl;
		return false;
	}
}
Double Double::operator * (const Double& bb) {
	try
	{
		Double b = bb;
		Double a = *this;
		bool minus = false;
		if (!sign()) {
			minus = !minus;
			a *= -1;
		}
		if (!(b.sign())) {
			minus = !minus;
			b *= -1;
		}
		Double inp(convert_to_string());
		vector<complex<lb>> fa(a.v.size(), (0, 1, 1)), fb(b.v.size());
		for (lint i = 0; i < min(a.v.size(), b.v.size()); ++i) {
			fa[i] = (complex<lb>)(0, (lb)a.v[i]);
			fb[i] = (complex<lb>)(0, (lb)b.v[i]);
		}
		if (a.v.size() > b.v.size()) {
			for (lint i = min(a.v.size(), b.v.size()); i < a.v.size(); ++i) {
				fa[i] = (complex<lb>)(0, (lb)a.v[i]);
			}
		}
		else {
			for (lint i = min(a.v.size(), b.v.size()); i < b.v.size(); ++i) {
				fb[i] = (complex<lb>)(0, (lb)b.v[i]);
			}
		}
		size_t l = 1;
		while (l < max(a.v.size(), b.v.size()))  l <<= 1;
		l <<= 1;
		fa.resize(l), fb.resize(l);

		fft(fa, false), fft(fb, false);
		for (size_t i = 0; i < l; ++i) {
			fa[i] *= fb[i];
		}
		fft(fa, true);
		lint  s_dop;
		Double ans;
		ans.v.resize(l, 0);
	//	for (lint i = 0; i < l - 1; ++i) {
	//		ans.v[i] = ((lint(fa[i].real() + 0.5)));
	//			if (((lint(fa[i].real() + 0.5))) != 0) {
	//	cout << "YES" << endl;
	//}
	//		if (ans.v[i] > inf) {
	//			ans.v[i + 1] += ans.v[i] / (lint)inf;
	//			ans.v[i] %= (lint)inf;
	//		}
	//	}
	//	ans.v[ans.v.size() - 1] = ((lint(fa[ans.v.size() - 1].real() + 0.5)));
	//	if (ans.v[ans.v.size() - 1] > inf) {
	//		ans.v.resize(ans.v.size() + 1);
	//		ans.v[ans.v.size() - 1] += ans.v[ans.v.size() - 2] / (lint)inf;
	//		ans.v[ans.v.size() - 2] %= (lint)inf;
	//	}
		//ans.clear();
		//for (lint i = l - 1; i >= 0; --i) {
		//	s_dop = (abs(lint(fa[i].real() + 0.5)));
		//	if (s_dop != 0) {
		//		cout << "YES" << endl;
		//	}
		//	lint sdvik = ceil((double)to_string(s_dop).size() / (double)loginf)-1;
		//	for (lint j= 0;j<=sdvik;++j) {
		//		ans.v[i + j] += s_dop % (lint)inf;
		//		s_dop /= (lint)inf;
		//	}
		//	//ans.v[i] = s_dop;
		//}
		//Double ans(s);
		for (size_t i = 0; i < l; ++i)
			ans.v[i] = lint(fa[i].real() + 0.5);
		ans.clear();
		lint carry = 0;
		for (size_t i = 0; i < ans.v.size(); ++i) {
			ans.v[i] += carry;
			carry = ans.v[i] / inf;
			ans.v[i] %= inf;
		}
		if (carry != 0) {
			ans.v.resize(ans.v.size()+1);
			ans.v[ans.v.size() - 1] += carry;
		}
		//for (lint i = 0; i < ans.v.size()-1; ++i) {
		//	if (ans.v[i] > inf) {
		//		ans.v[i + 1] += ans.v[i] / (lint)inf;
		//		ans.v[i] %= (lint)inf;
		//	}
		//}
		//if (ans.v[ans.v.size() - 1] > inf) {
		//	ans.v.resize(ans.v.size()+1);
		//	ans.v[ans.v.size() - 1] += ans.v[ans.v.size() - 2] / (lint)inf;
		//	ans.v[ans.v.size() - 2] %= (lint)inf;
		//}
		ans.n = (n + bb.n);
		ans.formatting();
		ans.clear();
		if (minus) {
			ans *= -1;
		}
		return ans;
	}
	catch (...)
	{
		Double otw;
		std::cout << "Error_operation*" << std::endl;
		return otw;
	}
}
Double Double::operator / (const Double& bb) {
	Double b = bb, a = *this;
	if (b == Double("0")) {
		return Double("0");
	}
	Double a1("1");
	if (b < a1) {
		lint dop = b.v.size();
		b << ((lint)(accuracy / loginf) - dop + 1);
		a << ((lint)(accuracy / loginf) - dop + 1);
		dop = to_string(a1.v[a1.v.size() - 1]).size() - to_string(b.v[b.v.size() - 1]).size();
		for (lint i = 0; i < dop; ++i)
		{
			a *= 10;
			b *= 10;
		}
	}
	bool minus = false;
	if (!sign()) {
		minus = !minus;
		a *= -1;
	}
	if (!(b.sign())) {
		minus = !minus;
		b *= -1;
	}
	Double otw, nul("0");
	if (a != nul) {
		Double l("0"), r, mid, dopl("0"), dopr("0"), dop_t;
		Double c = min_element_abs();
		r = a;
		lint kol = 0;
		while ((r - l) > c) {
			mid = (r + l);
			mid.div2();
			if ((mid * b) >= a) {
				r = mid;
			}
			else {
				l = mid;
			}
			++kol;
		}
		cout << kol<<endl;
		l.clear();
		r.clear();
		dopr = ((r * b) - a);
		dopr.labs();
		dopl = ((l * b) - a);
		dopl.labs();
		if (dopr > dopl) {
			otw = l;
		}
		else {
			otw = r;
		}
	}
	if (minus) {
		otw *= -1;
	}
	otw.n = a.n;
	otw.clear();
	return otw;
}
bool Double::operator < (const Double& b) {
	Double c = *this;
	c -= b;
	if (c.sign())
		return  false;
	return  true;
}
bool Double::operator <= (const Double& b) {
	Double c = *this;
	if (c == b) {
		return  true;
	}
	c -= b;
	if (!c.sign())
		return  true;
	return  false;
}
bool Double::operator > (const Double& b) {
	Double c = *this;
	if (c == b) {
		return  false;
	}
	c -= b;
	if (c.sign())
		return  true;
	return  false;
}
bool Double::operator >= (const Double& b) {
	Double c = *this;
	c -= b;
	if (c.sign())
		return  true;
	return  false;

}
bool Double::operator != (const Double& b) {
	if (v.size() > b.v.size()) {
		return  true;
	}
	else if (v.size() < b.v.size()) {
		return  true;
	}
	else {
		for (lint i = v.size() - 1; i >= 0; --i) {
			if (v[i] != b.v[i]) {
				return  true;
			}
		}
	}
	return  false;
}
bool Double::operator == (const Double& b) {
	return !(*this != b);
}
void Double::operator >>(lint kol) {
	if (kol != 0) {
		for (lint i = kol; i < v.size(); ++i) {
			v[i - kol] = v[i];
			v[i] = 0;
		}
		v.resize(v.size() - kol);
	}
}
bool Double::operator << (lint kol) {
	try
	{
		v.resize(v.size() + kol);
		for (lint i = v.size() - 1; i >= kol; --i) {
			v[i] = v[i - kol];
		}
		for (lint i = 0; i < kol; ++i) {
			v[i] = 0;
		}
		return true;
	}
	catch (...)
	{
		std::cout << "Error_operation+" << std::endl;
		return false;
	}
}

Double Double::operator + (const Double& b) {
	try
	{
		Double c;
		c = *this;
		c += b;
		return c;
	}
	catch (...)
	{
		std::cout << "Error_operation+" << std::endl;
		Double c;
		return c;
	}
}
Double Double::operator - (const Double& b) {
	try
	{
		Double c;
		c = *this;
		c -= b;
		return c;
	}
	catch (...)
	{
		std::cout << "Error_operation+" << std::endl;
		Double c;
		return c;
	}
}
Double Double::reverse_number() {
	Double a = *this;
	for (lint i = 0; i < a.v.size()-1; ++i) {
		a.v[i] = 0;
	}
	if ((lint)to_string(a.v[a.v.size() - 1]).size() + 1>loginf) {
		a.v.resize(a.v.size() + 1, 0);
		a.v[a.v.size() - 2] = 0;
		a.v[a.v.size() - 1] = 1;
	}
	else {
		a.v[a.v.size() - 1] = pow(10,to_string(a.v[a.v.size() - 1]).size() + 1);
	}
	Double ans("0"),dop("1");
	lint limit = accuracy/2;
	for (lint i = 0; i < limit; ++i) {
		lint kol = 0;
		while (a>=*this)
		{
			a = a - *this; 
			++kol;
		}
		dop.v[dop.v.size() - 1] = kol;
		ans *= 10;
		ans += dop;
		a *= 10;
	}
	ans.n =n+ limit+to_string(v[v.size()-1]).size()+((v.size())-(lint)accuracy/loginf-1)*loginf;
	ans.formatting();
	return ans;
}
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

