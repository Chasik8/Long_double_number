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
using namespace std;
typedef long long int lint;
typedef unsigned long long int ulint;
#define inf 1000000000
#define loginf 9
#define accuracy 100
class Double {
private:
    vector<lint> v;
    ulint n;
public:
    Double(string s = "") {
        n = 0;
        if (s != "") {
            convert(s);
        }
    }
    void convert(string a) {
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
        lint sdvik=(accuracy-n) / loginf;
        v.resize(v.size() + sdvik);
        for (lint i = v.size() - 1; i >= sdvik; --i) {
            v[i] = v[i - sdvik];
        }
        for (lint i = 0; i < sdvik; ++i) {
            v[i] = 0;
        }
        n += sdvik * loginf;
    }
    string convert_to_string() {
        string s;
        lint kol = to_string(v[v.size() - 1]).size();
        kol = (v[v.size() - 1] < 0 ? kol - 1 : kol)+(loginf*(v.size()-1))-n;
        for (lint i = v.size()-1; i >=0; --i) {
            lint a = v[i];
            string b="";
            while (a)
            {
                b += to_string(a % 10);
                a /= 10;
            }
            reverse(b.begin(), b.end());
            s += b;
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
        return s;
    }
    void lcin() {
        string a;
        cin >> a;
        convert(a);
    }
    void lcout() {
        if (v[0] < 0) {
            cout << '-';
        }
        int h = 0;
        if (v.size() == 1) {
            cout << v[0];
        }
        else {
            for (lint i = v.size() - 1; i >= 0; --i) {
                if (v[i] != 0) {
                    ++h;
                }
                if (h >= 1) {
                    if (h >= 2) {
                        string s = to_string(v[i]);
                        for (lint j = s.size(); j < loginf; ++j) {
                            cout << '0';
                        }
                    }
                    cout << abs(v[i]);
                    ++h;
                }
            }
        }
    }
    bool operator += (const Double& b) {
        try
        {
            if (v.size() < b.v.size()) {
                for (lint i = 0; v.size() < b.v.size(); ++i) {
                    v.push_back(0);
                }
            }
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
            bool l = true;
            for (lint i = lint(v.size() - 1); l && i > 0; --i) {
                if (v[i] == 0) {
                    v.pop_back();
                }
                else {
                    l = false;
                }
            }
            if (v.size() >= 2) {
                if (v[v.size() - 1] < 0) {
                    for (lint i = v.size() - 2; i >= 0; --i) {
                        if (v[i] > 0) {
                            v[i] -= inf;
                            ++v[i + 1];
                        }
                    }
                }
                else {
                    for (lint i = v.size() - 2; i >= 0; --i) {
                        if (v[i] < 0) {
                            v[i] += inf;
                            --v[i + 1];
                        }
                    }
                }
            }
            return true;
        }
        catch (...)
        {
            std::cout << "Error_operation+=" << std::endl;
            return false;
        }
    }
    bool operator < (const Double& b) {
        if (v.size() < b.v.size()) {
            return  true;
        }
        else if (v.size() > b.v.size()) {
            return  false;
        }
        else {
            for (lint i = v.size() - 1; i >= 0; --i) {
                if (v[i] < b.v[i]) {
                    return  true;
                }
                else if (v[i] > b.v[i]) {
                    return  false;
                }
            }
        }
        return  false;
    }
    void lswap (Double& a,Double& b) {
        swap(a.v,b.v);
        swap(a.n, b.n);
    }
    bool operator -= (Double& b) {
        try
        {
            for (lint i = 0; i < lint(b.v.size()); ++i) {
                b.v[i] *= -1;
            }
            *this += b;
            for (lint i = 0; i < lint(b.v.size()); ++i) {
                b.v[i] *= -1;
            }
            return true;
        }
        catch (...)
        {
            std::cout << "Error_operation-=" << std::endl;
            return false;
        }
    }
    bool operator *=(lint b) {
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
    bool operator << (lint kol) {
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
    ulint size() {
        return v.size();
    }
    // количество разр€ов не больше чем 10^9
    Double operator * (Double&b) {
        try
        {
            Double c("0");
            Double otw("0");
            if ((v.size() == 1 && v[0] == 0) || (b.size() == 1 && v[0] == 0)) {
                otw = c;
            }
            else {
                for (lint i = 0; i < b.size(); ++i) {
                    c.copy(*this);
                    c *= b[i];
                    c << i;
                    otw += c;
                }
            }
            otw.n = this->n + b.n;
            return otw;
        }
        catch (...)
        {
            Double otw;
            std::cout << "Error_operation+" << std::endl;
            return otw;
        }
    }
    void copy(Double& a) {
        v = a.v;
        n = a.n;
    }
    Double operator + (const Double& b) {
        try
        {
            Double c;
            c.copy(*this);
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
    Double operator - (Double& b) {
        try
        {
            Double c;
            c.copy(*this);
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
    void lpow(lint b) {
        Double c1;
        Double с2;
        c1.copy(*this);
        с2.copy(*this);
        for (lint i = 0; i < b; ++i) {
            c1 = (с2 * c1);
        }
        this->copy(c1);
    }
    lint operator [] (lint i) {
        try
        {
            return v[i];
        }
        catch (...)
        {
            std::cout << "Error_operation+" << std::endl;
            return 0;
        }
    }
    void div2() {
        for (lint i = v.size() - 1; i > 0; --i) {
            v[i - 1] += (v[i] % 2) * inf;
            v[i] /= 2;
        }
        v[0] /= 2;
    }
    void labs() {
        if (v[0] < 0) {
            for (lint i = 0; i < v.size(); ++i) {
                v[i] *= -1;
            }
        }
    }
    Double operator / (Double& b) {
        
        Double otw;
        if (v[0] != 0 || v.size() > 1) {
            Double c, l, r, rr, mid, dop, dop1, nul("0");
            l.n = 0;
            l.v.push_back(-1);
            c.n = 0;
            c.v.push_back(1);
            r.copy(*this);
            rr = r;
            while (rr[0] != 0 || rr.size() > 1) {
                mid = r;
                mid += l;
                mid.div2();
                dop = nul;
                dop = mid * b;
                dop -= *this;
                if (dop[0] >= 0) {
                    r = mid;
                }
                else {
                    l = mid;
                }
                rr = r;
                rr -= l;
                rr -= c;
            }
            dop = nul;
            dop = r * b;
            dop -= *this;
            if (dop[0] > 0) {
                otw = l;
            }
            else {
                dop.labs();
                dop1 = nul;
                dop1 = l * b;
                dop1 -= *this;
                dop1.labs();
                dop -= dop1;
                if (dop[0] >= 0) {
                    otw = l;
                }
                else {
                    otw = r;
                }
            }
        }
        return otw;
    }
    Double asin() {
        vector<Double> kef = { Double("1.0"), Double("0.166667"), Double("0.075"), Double("0.0446429"), Double("0.0303819"), Double("0.0223722"), Double("0.0173528"), Double("0.0139648"), Double("0.0115518"), Double("0.00976161"), Double("0.00839034"), Double("0.00731253"), Double("0.00644721"), Double("0.00574004"), Double("0.00515331"), Double("0.00466014"), Double("0.00424091"), Double("0.00388096"), Double("0.00356921"), Double("0.00329706"), Double("0.00305782"), Double("0.00284618"), Double("0.00265787"), Double("0.00248945"), Double("0.00233809"), Double("0.00220147"), Double("0.00207766"), Double("0.00196503"), Double("0.00186223"), Double("0.00176808"), Double("0.00168161"), Double("0.00160196"), Double("0.00152841"), Double("0.00146032"), Double("0.00139714"), Double("0.00133839"), Double("0.00128364"), Double("0.00123253"), Double("0.00118472"), Double("0.00113992"), Double("0.00109788"), Double("0.00105835"), Double("0.00102115"), Double("0.000986073"), Double("0.000952961"), Double("0.000921661"), Double("0.000892037"), Double("0.000863968"), Double("0.00083734"), Double("0.000812052"), Double("0.000788012"), Double("0.000765135"), Double("0.000743344"), Double("0.000722569"), Double("0.000702743"), Double("0.000683807"), Double("0.000665707"), Double("0.000648392"), Double("0.000631814"), Double("0.000615931"), Double("0.000600702"), Double("0.000586091"), Double("0.000572063"), Double("0.000558585"), Double("0.000545629"), Double("0.000533165"), Double("0.000521169"), Double("0.000509617"), Double("0.000498485"), Double("0.000487752"), Double("0.000477399"), Double("0.000467407"), Double("0.000457759"), Double("0.000448438"), Double("0.00043943"), Double("0.000430719"), Double("0.000422292"), Double("0.000414136"), Double("0.000406239"), Double("0.000398591"), Double("0.000391179"), Double("0.000383994"), Double("0.000377027"), Double("0.000370267"), Double("0.000363708"), Double("0.000357339"), Double("0.000351155"), Double("0.000345146"), Double("0.000339308"), Double("0.000333632"), Double("0.000328112"), Double("0.000322743"), Double("0.000317519"), Double("0.000312434"), Double("0.000307484"), Double("0.000302662"), Double("0.000297966"), Double("0.00029339"), Double("0.000288929"), Double("0.000284581"), Double("0.000280341"), Double("0.000276205"), Double("0.000272169"), Double("0.000268231"), Double("0.000264387"), Double("0.000260634"), Double("0.000256969"), Double("0.000253389"), Double("0.000249891"), Double("0.000246473"), Double("0.000243132"), Double("0.000239867"), Double("0.000236673"), Double("0.00023355"), Double("0.000230495"), Double("0.000227506"), Double("0.000224581"), Double("0.000221718"), Double("0.000218915"), Double("0.000216171"), Double("0.000213484"), Double("0.000210852"), Double("0.000208274"), Double("0.000205747"), Double("0.000203272"), Double("0.000200845"), Double("0.000198467"), Double("0.000196135"), Double("0.000193849"), Double("0.000191606"), Double("0.000189407"), Double("0.000187249"), Double("0.000185132"), Double("0.000183054"), Double("0.000181015"), Double("0.000179014"), Double("0.000177049"), Double("0.00017512"), Double("0.000173226"), Double("0.000171365"), Double("0.000169538"), Double("0.000167743"), Double("0.000165979"), Double("0.000164246"), Double("0.000162543"), Double("0.000160869"), Double("0.000159224"), Double("0.000157607"), Double("0.000156017"), Double("0.000154453"), Double("0.000152915"), Double("0.000151403"), Double("0.000149915"), Double("0.000148452"), Double("0.000147012"), Double("0.000145596"), Double("0.000144202"), Double("0.00014283"), Double("0.00014148"), Double("0.00014015"), Double("0.000138842"), Double("0.000137554"), Double("0.000136285"), Double("0.000135036"), Double("0.000133806"), Double("0.000132595"), Double("0.000131401"), Double("0.000130226"), Double("0.000129068"), Double("0.000127927"), Double("0.000126802"), Double("0.000125694"), Double("0.000124602"), Double("0.000123526"), Double("0.000122465"), Double("0.00012142"), Double("0.000120389"), Double("0.000119372"), Double("0.00011837"), Double("0.000117382"), Double("0.000116407"), Double("0.000115446"), Double("0.000114498"), Double("0.000113563"), Double("0.000112641"), Double("0.000111731"), Double("0.000110833"), Double("0.000109947"), Double("0.000109073"), Double("0.00010821"), Double("0.000107359"), Double("0.000106519"), Double("0.000105689"), Double("0.000104871"), Double("0.000104063"), Double("0.000103265"), Double("0.000102477"), Double("0.0001017"), Double("0.000100932"), Double("0.000100173"), Double("9.94247e-05"), Double("9.86852e-05"), Double("9.79548e-05"), Double("9.72333e-05"), Double("9.65207e-05"), Double("9.58168e-05"), Double("9.51213e-05"), Double("9.44343e-05"), Double("9.37554e-05"), Double("9.30847e-05"), Double("9.24219e-05"), Double("9.17669e-05"), Double("9.11197e-05"), Double("9.048e-05"), Double("8.98478e-05"), Double("8.92228e-05"), Double("8.86051e-05"), Double("8.79945e-05"), Double("8.73909e-05"), Double("8.67942e-05"), Double("8.62042e-05"), Double("8.56209e-05"), Double("8.50441e-05"), Double("8.44737e-05"), Double("8.39097e-05"), Double("8.3352e-05"), Double("8.28004e-05"), Double("8.22549e-05"), Double("8.17153e-05"), Double("8.11816e-05"), Double("8.06537e-05"), Double("8.01315e-05"), Double("7.96149e-05"), Double("7.91038e-05"), Double("7.85981e-05"), Double("7.80979e-05"), Double("7.76029e-05"), Double("7.71131e-05"), Double("7.66285e-05"), Double("7.61489e-05"), Double("7.56743e-05"), Double("7.52046e-05"), Double("7.47397e-05"), Double("7.42796e-05"), Double("7.38242e-05"), Double("7.33735e-05"), Double("7.29273e-05"), Double("7.24856e-05"), Double("7.20483e-05"), Double("7.16155e-05"), Double("7.11869e-05"), Double("7.07626e-05"), Double("7.03425e-05"), Double("6.99266e-05"), Double("6.95147e-05"), Double("6.91069e-05"), Double("6.8703e-05"), Double("6.8303e-05"), Double("6.7907e-05"), Double("6.75147e-05"), Double("6.71262e-05"), Double("6.67414e-05"), Double("6.63602e-05"), Double("6.59827e-05"), Double("6.56088e-05"), Double("6.52383e-05"), Double("6.48714e-05"), Double("6.45078e-05"), Double("6.41477e-05"), Double("6.37908e-05"), Double("6.34373e-05"), Double("6.30871e-05"), Double("6.274e-05"), Double("6.23961e-05"), Double("6.20554e-05"), Double("6.17177e-05"), Double("6.13831e-05"), Double("6.10515e-05"), Double("6.07229e-05"), Double("6.03972e-05"), Double("6.00744e-05"), Double("5.97545e-05"), Double("5.94374e-05"), Double("5.91231e-05"), Double("5.88115e-05"), Double("5.85027e-05"), Double("5.81966e-05"), Double("5.78931e-05"), Double("5.75923e-05"), Double("5.72941e-05"), Double("5.69984e-05"), Double("5.67053e-05"), Double("5.64146e-05"), Double("5.61265e-05"), Double("5.58408e-05"), Double("5.55575e-05"), Double("5.52766e-05"), Double("5.4998e-05"), Double("5.47218e-05"), Double("5.44479e-05"), Double("5.41763e-05"), Double("5.39069e-05"), Double("5.36397e-05"), Double("5.33748e-05"), Double("5.3112e-05"), Double("5.28513e-05"), Double("5.25928e-05"), Double("5.23364e-05"), Double("5.20821e-05"), Double("5.18298e-05"), Double("5.15795e-05"), Double("5.13313e-05"), Double("5.1085e-05"), Double("5.08407e-05"), Double("5.05984e-05"), Double("5.0358e-05"), Double("5.01194e-05"), Double("4.98828e-05"), Double("4.9648e-05"), Double("4.9415e-05"), Double("4.91838e-05"), Double("4.89545e-05"), Double("4.87269e-05"), Double("4.85011e-05"), Double("4.8277e-05"), Double("4.80546e-05"), Double("4.7834e-05"), Double("4.7615e-05"), Double("4.73977e-05"), Double("4.7182e-05"), Double("4.6968e-05"), Double("4.67556e-05"), Double("4.65448e-05"), Double("4.63355e-05"), Double("4.61278e-05"), Double("4.59217e-05"), Double("4.57171e-05"), Double("4.5514e-05"), Double("4.53124e-05"), Double("4.51123e-05"), Double("4.49137e-05"), Double("4.47165e-05"), Double("4.45208e-05"), Double("4.43265e-05"), Double("4.41335e-05"), Double("4.3942e-05"), Double("4.37519e-05"), Double("4.35631e-05"), Double("4.33757e-05"), Double("4.31896e-05"), Double("4.30049e-05"), Double("4.28215e-05"), Double("4.26393e-05"), Double("4.24585e-05"), Double("4.22789e-05"), Double("4.21006e-05"), Double("4.19235e-05"), Double("4.17477e-05"), Double("4.15731e-05"), Double("4.13998e-05"), Double("4.12276e-05"), Double("4.10566e-05"), Double("4.08868e-05"), Double("4.07181e-05"), Double("4.05506e-05"), Double("4.03843e-05"), Double("4.02191e-05"), Double("4.0055e-05"), Double("3.9892e-05"), Double("3.97302e-05"), Double("3.95694e-05"), Double("3.94097e-05"), Double("3.92511e-05"), Double("3.90935e-05"), Double("3.8937e-05"), Double("3.87815e-05"), Double("3.86271e-05"), Double("3.84737e-05"), Double("3.83213e-05"), Double("3.81698e-05"), Double("3.80194e-05"), Double("3.787e-05"), Double("3.77216e-05"), Double("3.75741e-05"), Double("3.74276e-05"), Double("3.7282e-05"), Double("3.71374e-05"), Double("3.69937e-05"), Double("3.68509e-05"), Double("3.67091e-05"), Double("3.65681e-05"), Double("3.64281e-05"), Double("3.62889e-05"), Double("3.61506e-05"), Double("3.60132e-05"), Double("3.58767e-05"), Double("3.5741e-05"), Double("3.56062e-05"), Double("3.54723e-05"), Double("3.53391e-05"), Double("3.52068e-05"), Double("3.50753e-05"), Double("3.49447e-05"), Double("3.48148e-05"), Double("3.46858e-05"), Double("3.45575e-05"), Double("3.44301e-05"), Double("3.43034e-05"), Double("3.41775e-05"), Double("3.40523e-05"), Double("3.39279e-05"), Double("3.38043e-05"), Double("3.36814e-05"), Double("3.35593e-05"), Double("3.34379e-05"), Double("3.33173e-05"), Double("3.31973e-05"), Double("3.30781e-05"), Double("3.29596e-05"), Double("3.28418e-05"), Double("3.27247e-05"), Double("3.26083e-05"), Double("3.24925e-05"), Double("3.23775e-05"), Double("3.22631e-05"), Double("3.21494e-05"), Double("3.20364e-05"), Double("3.1924e-05"), Double("3.18123e-05"), Double("3.17013e-05"), Double("3.15909e-05"), Double("3.14811e-05"), Double("3.13719e-05"), Double("3.12634e-05"), Double("3.11555e-05"), Double("3.10483e-05"), Double("3.09416e-05"), Double("3.08356e-05"), Double("3.07301e-05"), Double("3.06253e-05"), Double("3.0521e-05"), Double("3.04174e-05"), Double("3.03143e-05"), Double("3.02118e-05"), Double("3.01099e-05"), Double("3.00086e-05"), Double("2.99078e-05"), Double("2.98076e-05"), Double("2.97079e-05"), Double("2.96088e-05"), Double("2.95103e-05"), Double("2.94123e-05"), Double("2.93148e-05"), Double("2.92179e-05"), Double("2.91215e-05"), Double("2.90256e-05"), Double("2.89303e-05"), Double("2.88355e-05"), Double("2.87412e-05"), Double("2.86474e-05"), Double("2.85541e-05"), Double("2.84613e-05"), Double("2.83691e-05"), Double("2.82773e-05"), Double("2.8186e-05"), Double("2.80952e-05"), Double("2.80049e-05"), Double("2.79151e-05"), Double("2.78257e-05"), Double("2.77369e-05"), Double("2.76485e-05"), Double("2.75605e-05"), Double("2.74731e-05"), Double("2.73861e-05"), Double("2.72995e-05"), Double("2.72134e-05"), Double("2.71278e-05"), Double("2.70426e-05"), Double("2.69579e-05"), Double("2.68736e-05"), Double("2.67897e-05"), Double("2.67063e-05"), Double("2.66233e-05"), Double("2.65407e-05"), Double("2.64586e-05"), Double("2.63769e-05"), Double("2.62956e-05"), Double("2.62147e-05"), Double("2.61342e-05"), Double("2.60542e-05"), Double("2.59745e-05"), Double("2.58953e-05"), Double("2.58164e-05"), Double("2.5738e-05"), Double("2.56599e-05"), Double("2.55823e-05"), Double("2.5505e-05"), Double("2.54281e-05"), Double("2.53516e-05"), Double("2.52755e-05"), Double("2.51998e-05"), Double("2.51245e-05"), Double("2.50495e-05"), Double("2.49749e-05"), Double("2.49007e-05"), Double("2.48268e-05"), Double("2.47533e-05"), Double("2.46802e-05"), Double("2.46074e-05"), Double("2.4535e-05"), Double("2.44629e-05"), Double("2.43912e-05"), Double("2.43198e-05"), Double("2.42488e-05"), Double("2.41781e-05"), Double("2.41078e-05"), Double("2.40378e-05"), Double("2.39681e-05"), Double("2.38988e-05"), Double("2.38298e-05"), Double("2.37612e-05"), Double("2.36929e-05"), Double("2.36249e-05"), Double("2.35572e-05"), Double("2.34899e-05"), Double("2.34228e-05"), Double("2.33561e-05"), Double("2.32897e-05"), Double("2.32236e-05"), Double("2.31579e-05"), Double("2.30924e-05"), Double("2.30273e-05"), Double("2.29624e-05"), Double("2.28979e-05"), Double("2.28336e-05"), Double("2.27697e-05"), Double("2.27061e-05"), Double("2.26427e-05"), Double("2.25797e-05"), Double("2.25169e-05"), Double("2.24544e-05"), Double("2.23922e-05"), Double("2.23303e-05"), Double("2.22687e-05"), Double("2.22074e-05"), Double("2.21464e-05"), Double("2.20856e-05"), Double("2.20251e-05"), Double("2.19649e-05"), Double("2.1905e-05"), Double("2.18453e-05"), Double("2.17859e-05"), Double("2.17268e-05"), Double("2.16679e-05"), Double("2.16093e-05"), Double("2.1551e-05"), Double("2.14929e-05"), Double("2.14351e-05"), Double("2.13775e-05"), Double("2.13202e-05"), Double("2.12632e-05"), Double("2.12064e-05"), Double("2.11499e-05"), Double("2.10936e-05"), Double("2.10376e-05"), Double("2.09818e-05"), Double("2.09262e-05"), Double("2.08709e-05"), Double("2.08159e-05"), Double("2.07611e-05"), Double("2.07065e-05"), Double("2.06522e-05"), Double("2.05981e-05"), Double("2.05442e-05"), Double("2.04906e-05"), Double("2.04372e-05"), Double("2.0384e-05"), Double("2.03311e-05"), Double("2.02784e-05"), Double("2.02259e-05"), Double("2.01737e-05"), Double("2.01217e-05"), Double("2.00699e-05"), Double("2.00183e-05"), Double("1.99669e-05"), Double("1.99158e-05"), Double("1.98649e-05"), Double("1.98142e-05"), Double("1.97637e-05"), Double("1.97134e-05"), Double("1.96633e-05"), Double("1.96135e-05"), Double("1.95638e-05"), Double("1.95144e-05"), Double("1.94652e-05"), Double("1.94162e-05"), Double("1.93674e-05"), Double("1.93188e-05"), Double("1.92703e-05"), Double("1.92221e-05"), Double("1.91741e-05"), Double("1.91263e-05"), Double("1.90787e-05"), Double("1.90313e-05"), Double("1.89841e-05"), Double("1.89371e-05"), Double("1.88903e-05"), Double("1.88436e-05"), Double("1.87972e-05"), Double("1.8751e-05"), Double("1.87049e-05"), Double("1.8659e-05"), Double("1.86134e-05"), Double("1.85679e-05"), Double("1.85225e-05"), Double("1.84774e-05"), Double("1.84325e-05"), Double("1.83877e-05"), Double("1.83431e-05"), Double("1.82987e-05"), Double("1.82545e-05"), Double("1.82105e-05"), Double("1.81666e-05"), Double("1.81229e-05"), Double("1.80794e-05"), Double("1.8036e-05"), Double("1.79929e-05"), Double("1.79499e-05"), Double("1.7907e-05"), Double("1.78644e-05"), Double("1.78219e-05"), Double("1.77796e-05"), Double("1.77374e-05"), Double("1.76954e-05"), Double("1.76536e-05"), Double("1.76119e-05"), Double("1.75704e-05"), Double("1.75291e-05"), Double("1.74879e-05"), Double("1.74469e-05"), Double("1.74061e-05"), Double("1.73654e-05"), Double("1.73249e-05"), Double("1.72845e-05"), Double("1.72443e-05"), Double("1.72042e-05"), Double("1.71643e-05"), Double("1.71246e-05"), Double("1.7085e-05"), Double("1.70455e-05"), Double("1.70062e-05"), Double("1.69671e-05"), Double("1.69281e-05"), Double("1.68892e-05"), Double("1.68505e-05"), Double("1.6812e-05"), Double("1.67736e-05"), Double("1.67353e-05"), Double("1.66972e-05"), Double("1.66592e-05"), Double("1.66214e-05"), Double("1.65837e-05"), Double("1.65462e-05"), Double("1.65088e-05"), Double("1.64715e-05"), Double("1.64344e-05"), Double("1.63974e-05"), Double("1.63606e-05"), Double("1.63239e-05"), Double("1.62873e-05"), Double("1.62509e-05"), Double("1.62146e-05"), Double("1.61785e-05"), Double("1.61424e-05"), Double("1.61066e-05"), Double("1.60708e-05"), Double("1.60352e-05"), Double("1.59997e-05"), Double("1.59643e-05"), Double("1.59291e-05"), Double("1.5894e-05"), Double("1.5859e-05"), Double("1.58242e-05"), Double("1.57894e-05"), Double("1.57548e-05"), Double("1.57204e-05"), Double("1.5686e-05"), Double("1.56518e-05"), Double("1.56177e-05"), Double("1.55838e-05"), Double("1.55499e-05"), Double("1.55162e-05"), Double("1.54826e-05"), Double("1.54491e-05"), Double("1.54158e-05"), Double("1.53825e-05"), Double("1.53494e-05"), Double("1.53164e-05"), Double("1.52835e-05"), Double("1.52507e-05"), Double("1.52181e-05"), Double("1.51856e-05"), Double("1.51531e-05"), Double("1.51208e-05"), Double("1.50887e-05"), Double("1.50566e-05"), Double("1.50246e-05"), Double("1.49928e-05"), Double("1.4961e-05"), Double("1.49294e-05"), Double("1.48979e-05"), Double("1.48665e-05"), Double("1.48352e-05"), Double("1.4804e-05"), Double("1.4773e-05"), Double("1.4742e-05"), Double("1.47111e-05"), Double("1.46804e-05"), Double("1.46498e-05"), Double("1.46192e-05"), Double("1.45888e-05"), Double("1.45585e-05"), Double("1.45283e-05"), Double("1.44981e-05"), Double("1.44681e-05"), Double("1.44382e-05"), Double("1.44084e-05"), Double("1.43787e-05"), Double("1.43491e-05"), Double("1.43196e-05"), Double("1.42902e-05"), Double("1.42609e-05"), Double("1.42317e-05"), Double("1.42026e-05"), Double("1.41736e-05"), Double("1.41447e-05"), Double("1.41159e-05"), Double("1.40872e-05"), Double("1.40586e-05"), Double("1.40301e-05"), Double("1.40017e-05"), Double("1.39734e-05"), Double("1.39452e-05"), Double("1.3917e-05"), Double("1.3889e-05"), Double("1.38611e-05"), Double("1.38332e-05"), Double("1.38055e-05"), Double("1.37778e-05"), Double("1.37502e-05"), Double("1.37228e-05"), Double("1.36954e-05"), Double("1.36681e-05"), Double("1.36409e-05"), Double("1.36138e-05"), Double("1.35867e-05"), Double("1.35598e-05"), Double("1.3533e-05"), Double("1.35062e-05"), Double("1.34795e-05"), Double("1.3453e-05"), Double("1.34265e-05"), Double("1.34001e-05"), Double("1.33737e-05"), Double("1.33475e-05"), Double("1.33213e-05"), Double("1.32953e-05"), Double("1.32693e-05"), Double("1.32434e-05"), Double("1.32176e-05"), Double("1.31919e-05"), Double("1.31662e-05"), Double("1.31407e-05"), Double("1.31152e-05"), Double("1.30898e-05"), Double("1.30645e-05"), Double("1.30393e-05"), Double("1.30141e-05"), Double("1.2989e-05"), Double("1.2964e-05"), Double("1.29391e-05"), Double("1.29143e-05"), Double("1.28896e-05"), Double("1.28649e-05"), Double("1.28403e-05"), Double("1.28158e-05"), Double("1.27913e-05"), Double("1.2767e-05"), Double("1.27427e-05"), Double("1.27185e-05"), Double("1.26944e-05"), Double("1.26703e-05"), Double("1.26463e-05"), Double("1.26224e-05"), Double("1.25986e-05"), Double("1.25749e-05"), Double("1.25512e-05"), Double("1.25276e-05"), Double("1.2504e-05"), Double("1.24806e-05"), Double("1.24572e-05"), Double("1.24339e-05"), Double("1.24107e-05"), Double("1.23875e-05"), Double("1.23644e-05"), Double("1.23414e-05"), Double("1.23184e-05"), Double("1.22956e-05"), Double("1.22728e-05"), Double("1.225e-05"), Double("1.22274e-05"), Double("1.22048e-05"), Double("1.21822e-05"), Double("1.21598e-05"), Double("1.21374e-05"), Double("1.21151e-05"), Double("1.20928e-05"), Double("1.20706e-05"), Double("1.20485e-05"), Double("1.20265e-05"), Double("1.20045e-05"), Double("1.19826e-05"), Double("1.19607e-05"), Double("1.19389e-05"), Double("1.19172e-05"), Double("1.18956e-05"), Double("1.1874e-05"), Double("1.18525e-05"), Double("1.1831e-05"), Double("1.18096e-05"), Double("1.17883e-05"), Double("1.1767e-05"), Double("1.17458e-05"), Double("1.17247e-05"), Double("1.17036e-05"), Double("1.16826e-05"), Double("1.16617e-05"), Double("1.16408e-05"), Double("1.162e-05"), Double("1.15992e-05"), Double("1.15785e-05"), Double("1.15579e-05"), Double("1.15373e-05"), Double("1.15168e-05"), Double("1.14963e-05"), Double("1.1476e-05"), Double("1.14556e-05"), Double("1.14354e-05"), Double("1.14151e-05"), Double("1.1395e-05"), Double("1.13749e-05"), Double("1.13549e-05"), Double("1.13349e-05"), Double("1.1315e-05"), Double("1.12951e-05"), Double("1.12753e-05"), Double("1.12556e-05"), Double("1.12359e-05"), Double("1.12163e-05"), Double("1.11967e-05"), Double("1.11772e-05"), Double("1.11577e-05"), Double("1.11383e-05"), Double("1.1119e-05"), Double("1.10997e-05"), Double("1.10804e-05"), Double("1.10613e-05"), Double("1.10421e-05"), Double("1.10231e-05"), Double("1.10041e-05"), Double("1.09851e-05"), Double("1.09662e-05"), Double("1.09474e-05"), Double("1.09286e-05"), Double("1.09098e-05"), Double("1.08911e-05"), Double("1.08725e-05"), Double("1.08539e-05"), Double("1.08354e-05"), Double("1.08169e-05"), Double("1.07985e-05"), Double("1.07801e-05"), Double("1.07618e-05"), Double("1.07435e-05"), Double("1.07253e-05"), Double("1.07071e-05"), Double("1.0689e-05"), Double("1.0671e-05"), Double("1.0653e-05"), Double("1.0635e-05"), Double("1.06171e-05"), Double("1.05992e-05"), Double("1.05814e-05"), Double("1.05636e-05"), Double("1.05459e-05"), Double("1.05283e-05"), Double("1.05107e-05"), Double("1.04931e-05"), Double("1.04756e-05"), Double("1.04581e-05"), Double("1.04407e-05"), Double("1.04233e-05"), Double("1.0406e-05"), Double("1.03887e-05"), Double("1.03715e-05"), Double("1.03543e-05"), Double("1.03372e-05"), Double("1.03201e-05"), Double("1.03031e-05"), Double("1.02861e-05"), Double("1.02692e-05"), Double("1.02523e-05"), Double("1.02354e-05"), Double("1.02186e-05"), Double("1.02018e-05"), Double("1.01851e-05"), Double("1.01685e-05"), Double("1.01518e-05"), Double("1.01353e-05"), Double("1.01187e-05"), Double("1.01023e-05"), Double("1.00858e-05"), Double("1.00694e-05"), Double("1.00531e-05"), Double("1.00368e-05"), Double("1.00205e-05"), Double("1.00043e-05"), Double("9.9881e-06"), Double("9.97196e-06"), Double("9.95587e-06"), Double("9.93983e-06"), Double("9.92382e-06"), Double("9.90786e-06"), Double("9.89195e-06"), Double("9.87607e-06"), Double("9.86024e-06"), Double("9.84445e-06"), Double("9.8287e-06"), Double("9.81299e-06"), Double("9.79733e-06"), Double("9.78171e-06"), Double("9.76612e-06"), Double("9.75058e-06"), Double("9.73509e-06"), Double("9.71963e-06"), Double("9.70421e-06"), Double("9.68883e-06"), Double("9.6735e-06"), Double("9.6582e-06"), Double("9.64295e-06"), Double("9.62773e-06"), Double("9.61256e-06"), Double("9.59742e-06"), Double("9.58233e-06"), Double("9.56727e-06"), Double("9.55225e-06"), Double("9.53728e-06"), Double("9.52234e-06"), Double("9.50744e-06"), Double("9.49258e-06"), Double("9.47776e-06"), Double("9.46297e-06"), Double("9.44823e-06"), Double("9.43352e-06"), Double("9.41885e-06"), Double("9.40422e-06"), Double("9.38963e-06"), Double("9.37507e-06"), Double("9.36056e-06"), Double("9.34608e-06"), Double("9.33163e-06"), Double("9.31723e-06"), Double("9.30286e-06"), Double("9.28853e-06"), Double("9.27423e-06"), Double("9.25997e-06"), Double("9.24575e-06"), Double("9.23157e-06"), Double("9.21742e-06"), Double("9.20331e-06"), Double("9.18923e-06"), Double("9.17519e-06"), Double("9.16118e-06"), Double("9.14721e-06"), Double("9.13328e-06"), Double("9.11938e-06"), Double("9.10551e-06"), Double("9.09169e-06"), Double("9.07789e-06"), Double("9.06413e-06"), Double("9.05041e-06"), Double("9.03672e-06"), Double("9.02306e-06"), Double("9.00944e-06"), Double("8.99586e-06"), Double("8.9823e-06"), Double("8.96878e-06"), Double("8.9553e-06"), Double("8.94185e-06"), Double("8.92843e-06"),
        };
        lint kef_kol = 10;
        Double a = *this,ans("0");
        for (lint i = 1; i < kef_kol;a=a*(*this), ++i) {
            ans += (kef[i] * a);
        }
        ans += kef[0];
        return ans;
    }
};


//void mod_div_short(vector<lint>& a, vector<lint>& b, lint& l) {
//    string g1 = "1";
//    vector<lint> c = a, g;
//    convert(g, g1);
//    while (c[0] > 0 || c.size() > 1) {
//        dif(c, b);
//        ++l;
//    }
//    if (c[0] < 0) {
//        sum(c, b);
//        --l;
//    }
//    a = c;
//
//}
//void clear(vector<lint>& otw) {
//    bool l = true;
//    for (lint i = lint(otw.size() - 1); l && i > 0; --i) {
//        if (otw[i] == 0) {
//            otw.pop_back();
//        }
//        else {
//            l = false;
//        }
//    }
//}
//void mod_div(vector<lint>& a, vector<lint>& b,vector<lint>& otw){
//    vector<lint> c;
//    c.insert(c.begin(),a[a.size()-1]);
//    mod_div_short(c,b,otw[0]);
//    lint k=1;
//    if (a.size()>1){
//    for(lint i=a.size()-2;i>=0;++i){
//        c.insert(c.begin(),a[i]);
//        clear(c);
//        otw.push_back(0);
//        mod_div_short(c,b,otw[k]);
//        ++k;
//    }
//    clear(otw);
//    reverse(otw.begin(),otw.end());
//    }
//}
//void mod_short(vector<lint>& a, vector<lint>& b, vector<lint>& otw){

//}

//void mod_bin(vector<lint>& a, vector<lint>& b, vector<lint>& otw) {
//    if (a[0] != 0 || a.size() > 1) {
//        vector<lint> c = a, o;
//        div_bin(a, b, o);
//        mult(o, b, otw);
//        dif(c, otw);
//        otw = c;
//    }
//}
//void lfactorial(vector<lint>& a) {
//    vector<lint> r1, r2, r3, r4, otw;
//    string rd = "1", dop1 = "4";
//    r1.push_back(1);
//    r2.push_back(1);
//    r3.push_back(1);
//    r4.push_back(1);
//    //    convert(r1,rd);
//    //    convert(r2,rd);
//    //    convert(r3,rd);
//    //    convert(r4,rd);
//    vector<lint> s = a, dop, ss, ss1, ot, nul;
//    nul.push_back(0);
//    string ot1 = "0";
//    ot.push_back(0);
//    otw.push_back(0);
//    dop.push_back(4);
//    //    convert(dop,dop1);
//    ss1.push_back(1);
//    //    convert(ss1,rd);
//    for (; s[0] > 4 || s.size() > 1; dif(s, dop))
//    {
//        ss = s;
//        mult(r1, ss, ot);
//        r1 = ot;
//        ot = otw;
//        dif(ss, ss1);
//        mult(r4, ss, ot);
//        r4 = ot;
//        ot = otw;
//        dif(ss, ss1);
//        mult(r3, ss, ot);
//        r3 = ot;
//        ot = otw;
//        dif(ss, ss1);
//        mult(r2, ss, ot);
//        r2 = ot;
//        ot = otw;
//    }
//    vector<lint> m;
//    m.push_back(0);
//    m[0] = s[0] == 4 ? 24 : s[0] == 3 ? 6 : s[0] == 2 ? 2 : 1;
//    otw = nul;
//    mult(r1, r2, otw);
//    a = nul;
//    mult(otw, r3, a);
//    otw = nul;
//    mult(a, r4, otw);
//    a = nul;
//    mult(otw, m, a);
//}
int main()
{
    //ios_base::sync_with_stdio(false); // писать перед каждым ввобдом выводом
    //cin.tie(NULL);
    //vector<lint> a, b;
    //string c = "1";
    //lcin(a);
    //lcin(b);
    ////convert(b, c);
    //sum(a, b);
    //lcout(a);
    Double a("1");
    Double b;
    b=a.asin();
    cout << b.convert_to_string();
    return 0;
}