#include "Double.h"
using namespace Dominus;
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
		for (lint i = l - 1; i >= 0; --i) {
			s_dop = (abs(lint(fa[i].real() + 0.5)));
				if (to_string(s_dop).size() > loginf) {
					ans.v[i + 1] += s_dop / inf;
					s_dop %= (lint)inf;
				}
				ans.v[i] = s_dop;
		}
		//Double ans(s);
		ans.clear();
		ans.n = (n + bb.n);
		ans.formatting();
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
		while ((r - l) > c) {
			mid = (r + l);
			mid.div2();
			dop_t = mid * b;
			if ((mid * b) >= a) {
				r = mid;
			}
			else {
				l = mid;
			}
		}
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
	c -= b;
	if (c == Double("0")) {
		return  true;
	}
	if (!c.sign())
		return  true;
	return  false;
}
bool Double::operator > (const Double& b) {
	Double c = *this;
	c -= b;
	if (c == Double("0")) {
		return  false;
	}
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