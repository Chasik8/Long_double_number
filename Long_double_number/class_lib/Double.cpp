#include "Double.h"

using namespace Dominus;

lint Double::get_accuracy() {
    return accuracy;
}

bool Double::get_mode_fast() {
    return mode_fast;
}

Double::Double(string s) {
    loginf = 9;
    accuracy = 100;
    mode_fast = false;
    inf = pow(10, loginf);
    point = 0;
    if (s == "") {
        s = "0";
    }
    convert(s);
}

Double::Double(string s, lint inp_loginf, lint inp_accuracy, bool inp_mode_fast) {
    //if (mode_fast) {
    //	if (loginf > 4|| loginf <1) {
    //		cout << "Erorr: loginf<=4" << endl;
    //		return;
    //	}
    //}
    //else {
    //	if (loginf > 9 || loginf < 1) {
    //		cout << "Erorr: loginf<=9" << endl;
    //		return;
    //	}
    //}
    loginf = inp_loginf;
    accuracy = inp_accuracy;
    mode_fast = inp_mode_fast;
    inf = pow(10, loginf);
    point = 0;
    if (s == "") {
        s = "0";
    }
    convert(s);
}

Double::Double() {
    loginf = 9;
    accuracy = 100;
    mode_fast = false;
    inf = pow(10, loginf);
    point = 0;
    //string s = "0";
    //convert(s);
}

void Double::operator=(const Double &b) {
    loginf = b.loginf;
    accuracy = b.accuracy;
    mode_fast = b.mode_fast;
    inf = b.inf;
    mantissa = b.mantissa;
    point = b.point;
}

void Double::clear() {
    while ((mantissa.size()-1) * loginf > accuracy && mantissa[mantissa.size() - 1] == 0) {
        mantissa.pop_back();
    }
}

bool Double::sign() {
    for (lint i = mantissa.size() - 1; i >= 0; --i) {
        if (mantissa[i] != 0) {
            if (mantissa[i] > 0) {
                return true;
            } else {
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
                    mantissa.push_back(0);
                    mantissa[(k - 1) / loginf] *= -1;
                }
                mantissa[k / loginf] += (a[i] - '0') * pow(10, k % loginf);
                ++k;
                if (!flag) {
                    ++point;
                }
            } else {
                flag = true;
            }
        }
        if (!flag) {
            point = 0;
        }
        mantissa[mantissa.size() - 1] *= -1;
    } else {
        bool flag = false;
        for (lint i = a.size() - 1; i >= 0; --i) {
            if (a[i] != '.') {
                if (k % loginf == 0) {
                    mantissa.push_back(0);
                }
                mantissa[k / loginf] += (a[i] - '0') * pow(10, k % loginf);
                ++k;
                if (!flag) {
                    ++point;
                }
            } else {
                flag = true;
            }
        }
        if (!flag) {
            point = 0;
        }
    }
    formatting();
}

string Double::convert_to_string() {
    string s;
    Double nul("0", loginf, accuracy, mode_fast);
    bool minus = false;
    if (!sign()) {
        minus = true;
        *this *= -1;
    }
    lint kol = to_string(mantissa[mantissa.size() - 1]).size();
    kol = (mantissa[mantissa.size() - 1] < 0 ? kol - 1 : kol) + (loginf * (mantissa.size() - 1)) - point;
    bool flag = false;
    for (lint i = mantissa.size() - 1; i >= 0; --i) {
        string b = "", bb = "";
        bool h = false;
        b += to_string(mantissa[i]);
        if (i != mantissa.size() - 1) {
            for (lint j = 0; j < loginf - b.size(); ++j) {
                bb += "0";
            }
        }
        bb += b;
        s += bb;
    }
    if (kol > 0) {
        s.insert(kol, ".");
    } else if (kol == 0) {
        s.insert(kol, ".");
        s.insert(kol, "0");
    } else {
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

bool Double::operator*=(lint b) {
    try {
        mantissa[0] *= b;
        for (lint i = 1; i < mantissa.size(); ++i) {
            mantissa[i] *= b;
            mantissa[i] += (mantissa[i - 1] / inf);
            mantissa[i - 1] %= inf;
        }
        bool h = true;
        while (h) {
            h = false;
            if (mantissa[mantissa.size() - 1] >= inf) {
                mantissa.push_back(mantissa[mantissa.size() - 1] / inf);
                mantissa[mantissa.size() - 2] %= inf;
                h = true;
            }
        };

        return true;
    }
    catch (...) {
        std::cout << "Error_operation+" << std::endl;
        return false;
    }
}

bool Double::operator/=(lint k) {
    try {
        for (lint i = mantissa.size() - 1; i > 0; --i) {
            mantissa[i - 1] += (mantissa[i] % k) * inf;
            mantissa[i] /= k;
        }
        mantissa[0] /= k;
        return true;
    }
    catch (...) {
        std::cout << "Error_operation+" << std::endl;
        return false;
    }
}

void Double::formatting() {
    if (point <= accuracy) {
        lint sdvik = (accuracy - point) / loginf;
        mantissa.resize(mantissa.size() + sdvik);
        for (lint i = mantissa.size() - 1; i >= sdvik; --i) {
            mantissa[i] = mantissa[i - sdvik];
        }
        for (lint i = 0; i < sdvik; ++i) {
            mantissa[i] = 0;
        }
        point += sdvik * loginf;
        for (lint i = 0; i < accuracy - point; ++i) {
            *this *= 10;
        }
        point += accuracy - point;
    } else {
        lint sdvik = (point - accuracy) / loginf;
        for (lint i = sdvik; i < mantissa.size(); ++i) {
            mantissa[i - sdvik] = mantissa[i];
            mantissa[i] = 0;
        }
        for (lint i = mantissa.size() - sdvik; i < mantissa.size(); ++i) {
            mantissa[i] = 0;
        }
        point -= sdvik * loginf;
        for (lint i = 0; i < point - accuracy; ++i) {
            *this /= 10;
        }
        point -= point - accuracy;
        clear();
        //mantissa.resize(mantissa.size() - sdvik);
    }
}

void Double::div2() {
    for (lint i = mantissa.size() - 1; i > 0; --i) {
        mantissa[i - 1] += (mantissa[i] % 2) * inf;
        mantissa[i] /= 2;
    }
    mantissa[0] /= 2;
}

Double Double::min_element_abs() {
    Double c("0", loginf, accuracy, mode_fast);
    c.mantissa[0] = 10;
    return c;
}

void Double::fft(vector<complex<lb>> &a, bool invert) const {
    lint n = (lint) a.size();
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
        for (lint i = 0; i < mantissa.size(); ++i) {
            mantissa[i] *= -1;
        }
    }
}

bool Double::operator+=(const Double &b) {
    try {
        if (mantissa.size() < b.mantissa.size()) {
            for (lint i = 0; mantissa.size() < b.mantissa.size(); ++i) {
                mantissa.push_back(0);
            }
        }
        if (b.mantissa.size() > 0) {
            mantissa[0] += b.mantissa[0];
            for (lint i = 1; i < mantissa.size(); ++i) {
                if (i < b.mantissa.size()) {
                    mantissa[i] += b.mantissa[i];
                }
                mantissa[i] += mantissa[i - 1] / inf;
                mantissa[i - 1] %= inf;
            }
            if (mantissa[mantissa.size() - 1] / inf >= 1) {
                mantissa.push_back(mantissa[mantissa.size() - 1] / inf);
                mantissa[mantissa.size() - 2] %= inf;
            }
            if (mantissa.size() >= 2) {
                if (!sign()) {
                    for (lint i = 0; i < mantissa.size() - 1; ++i) {
                        if (mantissa[i] > 0) {
                            mantissa[i] -= inf;
                            ++mantissa[i + 1];
                        }
                    }
                } else {
                    for (lint i = mantissa.size() - 2; i >= 0; --i) {
                        mantissa[i] += inf;
                        --mantissa[i + 1];
                    }
                    for (lint i = 0; i < mantissa.size() - 1; ++i) {
                        if (mantissa[i] >= inf) {
                            mantissa[i] -= inf;
                            ++mantissa[i + 1];
                        }
                    }
                }
            }
            clear();

            return true;
        }
    }
    catch (...) {
        std::cout << "Error_operation+=" << std::endl;
        return false;
    }
    return true;
}

bool Double::operator-=(const Double &b) {
    try {
        Double c = b;
        for (lint i = 0; i < lint(b.mantissa.size()); ++i) {
            c.mantissa[i] *= -1;
        }
        *this += c;
        return true;
    }
    catch (...) {
        std::cout << "Error_operation-=" << std::endl;
        return false;
    }
}

Double Double::operator*(const Double &bb) const {
    try {
        if (*this == Double("0", loginf, accuracy, mode_fast) || bb == Double("0", loginf, accuracy, mode_fast)) {
            return Double("0", loginf, accuracy, mode_fast);
        }
        if (mode_fast) {
            return mov_fast(bb);
        } else {
            return mov_low(bb);
        }
    }
    catch (...) {
        Double otw;
        std::cout << "Error_operation*" << std::endl;
        return otw;
    }
}

Double Double::mov_low(const Double &bb) const {
    try {
        Double b = bb;
        Double a = *this;
        Double dop_a = a;
        bool minus = false;
        if (!a.sign()) {
            minus = !minus;
            a *= -1;
        }
        if (!(b.sign())) {
            minus = !minus;
            b *= -1;
        }
        Double ans("0", loginf, accuracy, mode_fast);
        for (lint i = b.mantissa.size() - 1; i >= 0; --i) {
            a *= b.mantissa[i];
            ans << 1;
            ans += a;
            a = dop_a;
        }
        ans.point = a.point + b.point;
        ans.formatting();
        if (minus) {
            ans *= -1;
        }
        return ans;
    }
    catch (...) {
        Double otw;
        std::cout << "Error_operation_mov_fast" << std::endl;
        return otw;
    }
}

Double Double::mov_fast(const Double &bb) const {
    try {
        Double b = bb;
        Double a = *this;
        bool minus = false;
        if (!a.sign()) {
            minus = !minus;
            a *= -1;
        }
        if (!(b.sign())) {
            minus = !minus;
            b *= -1;
        }
        Double inp(a.convert_to_string(),loginf,accuracy,mode_fast);
        vector<complex<lb>> fa(a.mantissa.size(), (0, 1, 1)), fb(b.mantissa.size());
        for (lint i = 0; i < min(a.mantissa.size(), b.mantissa.size()); ++i) {
            fa[i] = (complex<lb>) (0, (lb) a.mantissa[i]);
            fb[i] = (complex<lb>) (0, (lb) b.mantissa[i]);
        }
        if (a.mantissa.size() > b.mantissa.size()) {
            for (lint i = min(a.mantissa.size(), b.mantissa.size()); i < a.mantissa.size(); ++i) {
                fa[i] = (complex<lb>) (0, (lb) a.mantissa[i]);
            }
        } else {
            for (lint i = min(a.mantissa.size(), b.mantissa.size()); i < b.mantissa.size(); ++i) {
                fb[i] = (complex<lb>) (0, (lb) b.mantissa[i]);
            }
        }
        size_t l = 1;
        while (l < max(a.mantissa.size(), b.mantissa.size())) l <<= 1;
        l <<= 1;
        fa.resize(l), fb.resize(l);
        fft(fa, false), fft(fb, false);
        for (size_t i = 0; i < l; ++i) {
            fa[i] *= fb[i];
        }
        fft(fa, true);
        lint s_dop;
        Double ans("0",loginf,accuracy,mode_fast);
        ans.mantissa.resize(l, 0);
        for (size_t i = 0; i < l; ++i)
            ans.mantissa[i] = lint(fa[i].real() + 0.5);
        ans.clear();
        lint carry = 0;
        for (size_t i = 0; i < ans.mantissa.size(); ++i) {
            ans.mantissa[i] += carry;
            carry = ans.mantissa[i] / inf;
            ans.mantissa[i] %= inf;
        }
        if (carry != 0) {
            ans.mantissa.resize(ans.mantissa.size() + 1);
            ans.mantissa[ans.mantissa.size() - 1] += carry;
        }
        ans.point = (point + bb.point);
        ans.formatting();
        //ans.clear();
        if (minus) {
            ans *= -1;
        }
        return ans;
    }
    catch (...) {
        Double otw("0", loginf, accuracy, mode_fast);
        std::cout << "Error_operation_mov_fast" << std::endl;
        return otw;
    }
}

Double Double::operator/(const Double &bb) const {
    Double b = bb, a = *this;
    if (b == Double("0",b.loginf,b.accuracy,b.mode_fast)) {
        return Double("0", b.loginf, b.accuracy, b.mode_fast);
    }
    bool minus = false;
    if (!a.sign()) {
        minus = !minus;
        a *= -1;
    }
    if (!(b.sign())) {
        minus = !minus;
        b *= -1;
    }
    Double otw("0", loginf, accuracy, mode_fast), nul("0", loginf, accuracy, mode_fast);
    if (a != nul) {
        otw = a * b.reverse_number();
    }
    if (minus) {
        otw *= -1;
    }
    return otw;
}

bool Double::operator<(const Double &b) const {
    Double c = *this;
    c -= b;
    if (c.sign())
        return false;
    return true;
}

bool Double::operator<=(const Double &b) const {
    Double c = *this;
    if (c == b) {
        return true;
    }
    c -= b;
    if (!c.sign())
        return true;
    return false;
}

bool Double::operator>(const Double &b) const {
    Double c = *this;
    if (c == b) {
        return false;
    }
    c -= b;
    if (c.sign())
        return true;
    return false;
}

bool Double::operator>=(const Double &b) const {
    Double c = *this;
    c -= b;
    if (c.sign())
        return true;
    return false;

}

bool Double::operator!=(const Double &b) const {
    if (mantissa.size() > b.mantissa.size()) {
        return true;
    } else if (mantissa.size() < b.mantissa.size()) {
        return true;
    } else {
        for (lint i = mantissa.size() - 1; i >= 0; --i) {
            if (mantissa[i] != b.mantissa[i]) {
                return true;
            }
        }
    }
    return false;
}

bool Double::operator==(const Double &b) const {
    return !(*this != b);
}

void Double::operator>>(lint kol) {
    if (kol != 0) {
        for (lint i = kol; i < mantissa.size(); ++i) {
            mantissa[i - kol] = mantissa[i];
            mantissa[i] = 0;
        }
        mantissa.resize(mantissa.size() - kol);
    }
}

bool Double::operator<<(lint kol) {
    try {
        mantissa.resize(mantissa.size() + kol);
        for (lint i = mantissa.size() - 1; i >= kol; --i) {
            mantissa[i] = mantissa[i - kol];
        }
        for (lint i = 0; i < kol; ++i) {
            mantissa[i] = 0;
        }
        return true;
    }
    catch (...) {
        std::cout << "Error_operation+" << std::endl;
        return false;
    }
}

Double Double::operator+(const Double &b) const {
    try {
        Double c;
        c = *this;
        c += b;
        return c;
    }
    catch (...) {
        std::cout << "Error_operation+" << std::endl;
        Double c("0", loginf, accuracy, mode_fast);
        return c;
    }
}

Double Double::operator-(const Double &b) const {
    try {
        Double c;
        c = *this;
        c -= b;
        return c;
    }
    catch (...) {
        std::cout << "Error_operation+" << std::endl;
        Double c("0", loginf, accuracy, mode_fast);
        return c;
    }
}

Double Double::reverse_number() {
    Double a = *this;
    for (lint i = 0; i < a.mantissa.size() - 1; ++i) {
        a.mantissa[i] = 0;
    }
    lint flag = 0;
    if ((lint) to_string(a.mantissa[a.mantissa.size() - 1]).size() + 1 > loginf) {
        a.mantissa.resize(a.mantissa.size() + 1, 0);
        a.mantissa[a.mantissa.size() - 2] = 0;
        a.mantissa[a.mantissa.size() - 1] = 1;
    } else {
        a.mantissa[a.mantissa.size() - 1] = pow(10, to_string(a.mantissa[a.mantissa.size() - 1]).size());
    }
    Double ans("0", loginf, accuracy, mode_fast), dop("1", loginf, accuracy, mode_fast);
    lint limit = accuracy;
    for (lint i = 0; i < limit; ++i) {
        lint kol = 0;
        while (a >= *this) {
            a = a - *this;
            ++kol;
        }
        dop.mantissa[dop.mantissa.size() - 1] = kol;
        ans *= 10;
        ans += dop;
        a *= 10;
    }
    Double dop1("1", loginf, accuracy, mode_fast);
    ans.point += limit;
    ans.point += to_string(mantissa[mantissa.size() - 1]).size() - to_string(dop1.mantissa[dop1.mantissa.size() - 1]).size();
    if (((mantissa.size()) - (ceil)((double) accuracy / (double) loginf)) > 0) {
        ans.point += ((mantissa.size()) - (ceil)((double) accuracy / (double) loginf)) * loginf;
    }
    ans.point -= 1;
    ans.formatting();
    return ans;
}

void Double::N(lint inp) {
    point += inp;
    formatting();
}
