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
        formatting();
    }
    void formatting() {
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
            for (lint i = 0; i<accuracy - n; ++i) {
                *this *= 10;
            }
            n += accuracy - n;
        }
        else {
            lint sdvik = (n-accuracy) / loginf;
            for (lint i = v.size() - 1; i > sdvik; --i) {
                v[i - sdvik]=v[i];
                v[i]=0;
            }
            n -= sdvik * loginf;
            for (lint i = 0;i< n - accuracy; ++i) {
                *this /= 10;
            }
            n -= n - accuracy;
            v.resize(v.size() - sdvik);
        }
    }
    bool sng() {
        for (lint i = 0; i < v.size(); ++i) {
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
    string convert_to_string() {
        string s;
        Double nul("0");
        bool minus = false;
        if (!sng()) {
            minus = true;
            *this *= -1;
        }
        lint kol = to_string(v[v.size() - 1]).size();
        kol = (v[v.size() - 1] < 0 ? kol - 1 : kol)+(loginf*(v.size()-1))-n;
        bool flag = false;
        lint point = 0;
        for (lint i = v.size()-1; i >=0; --i) {
            lint a = v[i];
            string b="",bb="";
            point = 0;
            bool h = false;
            while (a)
            {
                b += to_string(a % 10);
                a /= 10;
                ++point;
                h = true;
            }
            if (flag) {
                for (lint i = 0; i < loginf - point; ++i) {
                    bb += "0";
                }
            }
            flag = h;
            b += bb;
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
        if (minus) {
            s.insert(0, "-");
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
            //bool l = true;
            //for (lint i = lint(v.size() - 1); l && i > 0; --i) {
            //    if (v[i] == 0) {
            //        v.pop_back();
            //    }
            //    else {
            //        l = false;
            //    }
            //}
            //Double nul("0");
            if (v.size() >= 2) {
                //if (*this < nul) {
                if (v[v.size()-1]<0){
                    for (lint i = 0; i < v.size()-1; ++i) {
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
                    for (lint i = 0; i < v.size()-1; ++i) {
                        if (v[i] >= inf) {
                            v[i] -= inf;
                            ++v[i + 1];
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
    bool operator <= (const Double& b) {
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
        return  true;
    }
    bool operator > (const Double& b) {
        if (v.size() > b.v.size()) {
            return  true;
        }
        else if (v.size() < b.v.size()) {
            return  false;
        }
        else {
            for (lint i = v.size() - 1; i >= 0; --i) {
                if (v[i] > b.v[i]) {
                    return  true;
                }
                else if (v[i] < b.v[i]) {
                    return  false;
                }
            }
        }
        return  false;
    }
    bool operator >= (const Double& b) {
        if (v.size() > b.v.size()) {
            return  true;
        }
        else if (v.size() < b.v.size()) {
            return  false;
        }
        else {
            for (lint i = v.size() - 1; i >= 0; --i) {
                if (v[i] > b.v[i]) {
                    return  true;
                }
                else if (v[i] < b.v[i]) {
                    return  false;
                }
            }
        }
        return  true;
    }
    bool operator != (const Double& b) {
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
            otw.formatting();
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
    bool operator /= (lint k) {
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
    void labs() {
        if (v[0] < 0) {
            for (lint i = 0; i < v.size(); ++i) {
                v[i] *= -1;
            }
        }
    }
    Double min_element_abs() {
        string str_c = "0.";
        for (lint i = 0; i < accuracy - 2; ++i) {
            str_c += "0";
        }
        str_c += "1";
        Double c(str_c);
        return c;
    }
    Double max_element_abs() {
        string str_c = "";
        for (lint i = 0; i < 4; ++i) {
            str_c += "0";
        }
        str_c += "1";
        reverse(str_c.begin(), str_c.end());
        Double c(str_c);
        return c;
    }
    Double operator / (Double& b) {
        
        Double otw,nul("0");
        if (*this != nul) {
            Double l("-1"), r, mid,dopl("0"), dopr("0");
            Double c = min_element_abs();
            r = max_element_abs();
            while ((r-l)>c) {
                mid = (r+l);
                mid.div2();
                if ((mid * b) >= *this) {
                    r = mid;
                }
                else {
                    l = mid;
                }
            }
            dopr = ((r * b)-*this);
            dopr.labs();
            dopl = ((l * b) - *this);
            dopl.labs();
            if (dopr >dopl) {
                otw = l;
            }
            else {
                otw = r;
            }
        }
        otw.n = this->n;
        return otw;
    }
    Double asin() {
        vector<Double> kef = { Double("1.0000000000"), Double("0.1666666667"), Double("0.0750000000"), Double("0.0446428571"), Double("0.0303819444"), Double("0.0223721591"), Double("0.0173527644"), Double("0.0139648438"), Double("0.0115518009"), Double("0.0097616095"), Double("0.0083903358"), Double("0.0073125259"), Double("0.0064472103"), Double("0.0057400377"), Double("0.0051533097"), Double("0.0046601435"), Double("0.0042409071"), Double("0.0038809646"), Double("0.0035692054"), Double("0.0032970595"), Double("0.0030578216"), Double("0.0028461784"), Double("0.0026578706"), Double("0.0024894487"), Double("0.0023380919"), Double("0.0022014740"), Double("0.0020776610"), Double("0.0019650336"), Double("0.0018622264"), Double("0.0017680811"), Double("0.0016816094"), Double("0.0016019633"), Double("0.0015284116"), Double("0.0014603209"), Double("0.0013971399"), Double("0.0013383870"), Double("0.0012836394"), Double("0.0012325251"), Double("0.0011847153"), Double("0.0011399183"), Double("0.0010978750"), Double("0.0010583541"), Double("0.0010211487"), Double("0.0009860731"), Double("0.0009529606"), Double("0.0009216607"), Double("0.0008920374"), Double("0.0008639677"), Double("0.0008373398"), Double("0.0008120522"), Double("0.0007880123"), Double("0.0007651354"), Double("0.0007433445"), Double("0.0007225686"), Double("0.0007027428"), Double("0.0006838073"), Double("0.0006657071"), Double("0.0006483916"), Double("0.0006318140"), Double("0.0006159309"), Double("0.0006007023"), Double("0.0005860911"), Double("0.0005720627"), Double("0.0005585851"), Double("0.0005456286"), Double("0.0005331653"), Double("0.0005211694"), Double("0.0005096167"), Double("0.0004984846"), Double("0.0004877519"), Double("0.0004773989"), Double("0.0004674070"), Double("0.0004577589"), Double("0.0004484383"), Double("0.0004394296"), Double("0.0004307186"), Double("0.0004222917"), Double("0.0004141360"), Double("0.0004062395"), Double("0.0003985908"), Double("0.0003911791"), Double("0.0003839943"), Double("0.0003770267"), Double("0.0003702674"), Double("0.0003637077"), Double("0.0003573393"), Double("0.0003511547"), Double("0.0003451464"), Double("0.0003393076"), Double("0.0003336315"), Double("0.0003281120"), Double("0.0003227429"), Double("0.0003175187"), Double("0.0003124340"), Double("0.0003074835"), Double("0.0003026624"), Double("0.0002979660"), Double("0.0002933897"), Double("0.0002889295"), Double("0.0002845811"), Double("0.0002803407"), Double("0.0002762046"), Double("0.0002721691"), Double("0.0002682311"), Double("0.0002643870"), Double("0.0002606339"), Double("0.0002569688"), Double("0.0002533888"), Double("0.0002498911"), Double("0.0002464732"), Double("0.0002431325"), Double("0.0002398665"), Double("0.0002366731"), Double("0.0002335498"), Double("0.0002304947"), Double("0.0002275056"), Double("0.0002245806"), Double("0.0002217177"), Double("0.0002189151"), Double("0.0002161710"), Double("0.0002134838"), Double("0.0002108519"), Double("0.0002082735"), Double("0.0002057473"), Double("0.0002032718"), Double("0.0002008455"), Double("0.0001984671"), Double("0.0001961352"), Double("0.0001938487"), Double("0.0001916062"), Double("0.0001894067"), Double("0.0001872489"), Double("0.0001851318"), Double("0.0001830542"), Double("0.0001810153"), Double("0.0001790139"), Double("0.0001770491"), Double("0.0001751200"), Double("0.0001732257"), Double("0.0001713653"), Double("0.0001695380"), Double("0.0001677429"), Double("0.0001659792"), Double("0.0001642463"), Double("0.0001625433"), Double("0.0001608695"), Double("0.0001592242"), Double("0.0001576068"), Double("0.0001560167"), Double("0.0001544530"), Double("0.0001529153"), Double("0.0001514030"), Double("0.0001499154"), Double("0.0001484520"), Double("0.0001470123"), Double("0.0001455957"), Double("0.0001442017"), Double("0.0001428298"), Double("0.0001414796"), Double("0.0001401504"), Double("0.0001388420"), Double("0.0001375537"), Double("0.0001362853"), Double("0.0001350363"), Double("0.0001338062"), Double("0.0001325947"), Double("0.0001314013"), Double("0.0001302258"), Double("0.0001290676"), Double("0.0001279266"), Double("0.0001268022"), Double("0.0001256943"), Double("0.0001246023"), Double("0.0001235261"), Double("0.0001224653"), Double("0.0001214196"), Double("0.0001203887"), Double("0.0001193722"), Double("0.0001183701"), Double("0.0001173818"), Double("0.0001164072"), Double("0.0001154461"), Double("0.0001144981"), Double("0.0001135630"), Double("0.0001126405"), Double("0.0001117305"), Double("0.0001108327"), Double("0.0001099468"), Double("0.0001090727"), Double("0.0001082101"), Double("0.0001073588"), Double("0.0001065186"), Double("0.0001056893"), Double("0.0001048707"), Double("0.0001040626"), Double("0.0001032649"), Double("0.0001024773"), Double("0.0001016996"), Double("0.0001009317"), Double("0.0001001735"), Double("0.0000994247"), Double("0.0000986852"), Double("0.0000979548"), Double("0.0000972333"), Double("0.0000965207"), Double("0.0000958168"), Double("0.0000951213"), Double("0.0000944343"), Double("0.0000937554"), Double("0.0000930847"), Double("0.0000924219"), Double("0.0000917669"), Double("0.0000911197"), Double("0.0000904800"), Double("0.0000898478"), Double("0.0000892228"), Double("0.0000886051"), Double("0.0000879945"), Double("0.0000873909"), Double("0.0000867942"), Double("0.0000862042"), Double("0.0000856209"), Double("0.0000850441"), Double("0.0000844737"), Double("0.0000839097"), Double("0.0000833520"), Double("0.0000828004"), Double("0.0000822549"), Double("0.0000817153"), Double("0.0000811816"), Double("0.0000806537"), Double("0.0000801315"), Double("0.0000796149"), Double("0.0000791038"), Double("0.0000785981"), Double("0.0000780979"), Double("0.0000776029"), Double("0.0000771131"), Double("0.0000766285"), Double("0.0000761489"), Double("0.0000756743"), Double("0.0000752046"), Double("0.0000747397"), Double("0.0000742796"), Double("0.0000738242"), Double("0.0000733735"), Double("0.0000729273"), Double("0.0000724856"), Double("0.0000720483"), Double("0.0000716155"), Double("0.0000711869"), Double("0.0000707626"), Double("0.0000703425"), Double("0.0000699266"), Double("0.0000695147"), Double("0.0000691069"), Double("0.0000687030"), Double("0.0000683030"), Double("0.0000679070"), Double("0.0000675147"), Double("0.0000671262"), Double("0.0000667414"), Double("0.0000663602"), Double("0.0000659827"), Double("0.0000656088"), Double("0.0000652383"), Double("0.0000648714"), Double("0.0000645078"), Double("0.0000641477"), Double("0.0000637908"), Double("0.0000634373"), Double("0.0000630871"), Double("0.0000627400"), Double("0.0000623961"), Double("0.0000620554"), Double("0.0000617177"), Double("0.0000613831"), Double("0.0000610515"), Double("0.0000607229"), Double("0.0000603972"), Double("0.0000600744"), Double("0.0000597545"), Double("0.0000594374"), Double("0.0000591231"), Double("0.0000588115"), Double("0.0000585027"), Double("0.0000581966"), Double("0.0000578931"), Double("0.0000575923"), Double("0.0000572941"), Double("0.0000569984"), Double("0.0000567053"), Double("0.0000564146"), Double("0.0000561265"), Double("0.0000558408"), Double("0.0000555575"), Double("0.0000552766"), Double("0.0000549980"), Double("0.0000547218"), Double("0.0000544479"), Double("0.0000541763"), Double("0.0000539069"), Double("0.0000536397"), Double("0.0000533748"), Double("0.0000531120"), Double("0.0000528513"), Double("0.0000525928"), Double("0.0000523364"), Double("0.0000520821"), Double("0.0000518298"), Double("0.0000515795"), Double("0.0000513313"), Double("0.0000510850"), Double("0.0000508407"), Double("0.0000505984"), Double("0.0000503580"), Double("0.0000501194"), Double("0.0000498828"), Double("0.0000496480"), Double("0.0000494150"), Double("0.0000491838"), Double("0.0000489545"), Double("0.0000487269"), Double("0.0000485011"), Double("0.0000482770"), Double("0.0000480546"), Double("0.0000478340"), Double("0.0000476150"), Double("0.0000473977"), Double("0.0000471820"), Double("0.0000469680"), Double("0.0000467556"), Double("0.0000465448"), Double("0.0000463355"), Double("0.0000461278"), Double("0.0000459217"), Double("0.0000457171"), Double("0.0000455140"), Double("0.0000453124"), Double("0.0000451123"), Double("0.0000449137"), Double("0.0000447165"), Double("0.0000445208"), Double("0.0000443265"), Double("0.0000441335"), Double("0.0000439420"), Double("0.0000437519"), Double("0.0000435631"), Double("0.0000433757"), Double("0.0000431896"), Double("0.0000430049"), Double("0.0000428215"), Double("0.0000426393"), Double("0.0000424585"), Double("0.0000422789"), Double("0.0000421006"), Double("0.0000419235"), Double("0.0000417477"), Double("0.0000415731"), Double("0.0000413998"), Double("0.0000412276"), Double("0.0000410566"), Double("0.0000408868"), Double("0.0000407181"), Double("0.0000405506"), Double("0.0000403843"), Double("0.0000402191"), Double("0.0000400550"), Double("0.0000398920"), Double("0.0000397302"), Double("0.0000395694"), Double("0.0000394097"), Double("0.0000392511"), Double("0.0000390935"), Double("0.0000389370"), Double("0.0000387815"), Double("0.0000386271"), Double("0.0000384737"), Double("0.0000383213"), Double("0.0000381698"), Double("0.0000380194"), Double("0.0000378700"), Double("0.0000377216"), Double("0.0000375741"), Double("0.0000374276"), Double("0.0000372820"), Double("0.0000371374"), Double("0.0000369937"), Double("0.0000368509"), Double("0.0000367091"), Double("0.0000365681"), Double("0.0000364281"), Double("0.0000362889"), Double("0.0000361506"), Double("0.0000360132"), Double("0.0000358767"), Double("0.0000357410"), Double("0.0000356062"), Double("0.0000354723"), Double("0.0000353391"), Double("0.0000352068"), Double("0.0000350753"), Double("0.0000349447"), Double("0.0000348148"), Double("0.0000346858"), Double("0.0000345575"), Double("0.0000344301"), Double("0.0000343034"), Double("0.0000341775"), Double("0.0000340523"), Double("0.0000339279"), Double("0.0000338043"), Double("0.0000336814"), Double("0.0000335593"), Double("0.0000334379"), Double("0.0000333173"), Double("0.0000331973"), Double("0.0000330781"), Double("0.0000329596"), Double("0.0000328418"), Double("0.0000327247"), Double("0.0000326083"), Double("0.0000324925"), Double("0.0000323775"), Double("0.0000322631"), Double("0.0000321494"), Double("0.0000320364"), Double("0.0000319240"), Double("0.0000318123"), Double("0.0000317013"), Double("0.0000315909"), Double("0.0000314811"), Double("0.0000313719"), Double("0.0000312634"), Double("0.0000311555"), Double("0.0000310483"), Double("0.0000309416"), Double("0.0000308356"), Double("0.0000307301"), Double("0.0000306253"), Double("0.0000305210"), Double("0.0000304174"), Double("0.0000303143"), Double("0.0000302118"), Double("0.0000301099"), Double("0.0000300086"), Double("0.0000299078"), Double("0.0000298076"), Double("0.0000297079"), Double("0.0000296088"), Double("0.0000295103"), Double("0.0000294123"), Double("0.0000293148"), Double("0.0000292179"), Double("0.0000291215"), Double("0.0000290256"), Double("0.0000289303"), Double("0.0000288355"), Double("0.0000287412"), Double("0.0000286474"), Double("0.0000285541"), Double("0.0000284613"), Double("0.0000283691"), Double("0.0000282773"), Double("0.0000281860"), Double("0.0000280952"), Double("0.0000280049"), Double("0.0000279151"), Double("0.0000278257"), Double("0.0000277369"), Double("0.0000276485"), Double("0.0000275605"), Double("0.0000274731"), Double("0.0000273861"), Double("0.0000272995"), Double("0.0000272134"), Double("0.0000271278"), Double("0.0000270426"), Double("0.0000269579"), Double("0.0000268736"), Double("0.0000267897"), Double("0.0000267063"), Double("0.0000266233"), Double("0.0000265407"), Double("0.0000264586"), Double("0.0000263769"), Double("0.0000262956"), Double("0.0000262147"), Double("0.0000261342"), Double("0.0000260542"), Double("0.0000259745"), Double("0.0000258953"), Double("0.0000258164"), Double("0.0000257380"), Double("0.0000256599"), Double("0.0000255823"), Double("0.0000255050"), Double("0.0000254281"), Double("0.0000253516"), Double("0.0000252755"), Double("0.0000251998"), Double("0.0000251245"), Double("0.0000250495"), Double("0.0000249749"), Double("0.0000249007"), Double("0.0000248268"), Double("0.0000247533"), Double("0.0000246802"), Double("0.0000246074"), Double("0.0000245350"), Double("0.0000244629"), Double("0.0000243912"), Double("0.0000243198"), Double("0.0000242488"), Double("0.0000241781"), Double("0.0000241078"), Double("0.0000240378"), Double("0.0000239681"), Double("0.0000238988"), Double("0.0000238298"), Double("0.0000237612"), Double("0.0000236929"), Double("0.0000236249"), Double("0.0000235572"), Double("0.0000234899"), Double("0.0000234228"), Double("0.0000233561"), Double("0.0000232897"), Double("0.0000232236"), Double("0.0000231579"), Double("0.0000230924"), Double("0.0000230273"), Double("0.0000229624"), Double("0.0000228979"), Double("0.0000228336"), Double("0.0000227697"), Double("0.0000227061"), Double("0.0000226427"), Double("0.0000225797"), Double("0.0000225169"), Double("0.0000224544"), Double("0.0000223922"), Double("0.0000223303"), Double("0.0000222687"), Double("0.0000222074"), Double("0.0000221464"), Double("0.0000220856"), Double("0.0000220251"), Double("0.0000219649"), Double("0.0000219050"), Double("0.0000218453"), Double("0.0000217859"), Double("0.0000217268"), Double("0.0000216679"), Double("0.0000216093"), Double("0.0000215510"), Double("0.0000214929"), Double("0.0000214351"), Double("0.0000213775"), Double("0.0000213202"), Double("0.0000212632"), Double("0.0000212064"), Double("0.0000211499"), Double("0.0000210936"), Double("0.0000210376"), Double("0.0000209818"), Double("0.0000209262"), Double("0.0000208709"), Double("0.0000208159"), Double("0.0000207611"), Double("0.0000207065"), Double("0.0000206522"), Double("0.0000205981"), Double("0.0000205442"), Double("0.0000204906"), Double("0.0000204372"), Double("0.0000203840"), Double("0.0000203311"), Double("0.0000202784"), Double("0.0000202259"), Double("0.0000201737"), Double("0.0000201217"), Double("0.0000200699"), Double("0.0000200183"), Double("0.0000199669"), Double("0.0000199158"), Double("0.0000198649"), Double("0.0000198142"), Double("0.0000197637"), Double("0.0000197134"), Double("0.0000196633"), Double("0.0000196135"), Double("0.0000195638"), Double("0.0000195144"), Double("0.0000194652"), Double("0.0000194162"), Double("0.0000193674"), Double("0.0000193188"), Double("0.0000192703"), Double("0.0000192221"), Double("0.0000191741"), Double("0.0000191263"), Double("0.0000190787"), Double("0.0000190313"), Double("0.0000189841"), Double("0.0000189371"), Double("0.0000188903"), Double("0.0000188436"), Double("0.0000187972"), Double("0.0000187510"), Double("0.0000187049"), Double("0.0000186590"), Double("0.0000186134"), Double("0.0000185679"), Double("0.0000185225"), Double("0.0000184774"), Double("0.0000184325"), Double("0.0000183877"), Double("0.0000183431"), Double("0.0000182987"), Double("0.0000182545"), Double("0.0000182105"), Double("0.0000181666"), Double("0.0000181229"), Double("0.0000180794"), Double("0.0000180360"), Double("0.0000179929"), Double("0.0000179499"), Double("0.0000179070"), Double("0.0000178644"), Double("0.0000178219"), Double("0.0000177796"), Double("0.0000177374"), Double("0.0000176954"), Double("0.0000176536"), Double("0.0000176119"), Double("0.0000175704"), Double("0.0000175291"), Double("0.0000174879"), Double("0.0000174469"), Double("0.0000174061"), Double("0.0000173654"), Double("0.0000173249"), Double("0.0000172845"), Double("0.0000172443"), Double("0.0000172042"), Double("0.0000171643"), Double("0.0000171246"), Double("0.0000170850"), Double("0.0000170455"), Double("0.0000170062"), Double("0.0000169671"), Double("0.0000169281"), Double("0.0000168892"), Double("0.0000168505"), Double("0.0000168120"), Double("0.0000167736"), Double("0.0000167353"), Double("0.0000166972"), Double("0.0000166592"), Double("0.0000166214"), Double("0.0000165837"), Double("0.0000165462"), Double("0.0000165088"), Double("0.0000164715"), Double("0.0000164344"), Double("0.0000163974"), Double("0.0000163606"), Double("0.0000163239"), Double("0.0000162873"), Double("0.0000162509"), Double("0.0000162146"), Double("0.0000161785"), Double("0.0000161424"), Double("0.0000161066"), Double("0.0000160708"), Double("0.0000160352"), Double("0.0000159997"), Double("0.0000159643"), Double("0.0000159291"), Double("0.0000158940"), Double("0.0000158590"), Double("0.0000158242"), Double("0.0000157894"), Double("0.0000157548"), Double("0.0000157204"), Double("0.0000156860"), Double("0.0000156518"), Double("0.0000156177"), Double("0.0000155838"), Double("0.0000155499"), Double("0.0000155162"), Double("0.0000154826"), Double("0.0000154491"), Double("0.0000154158"), Double("0.0000153825"), Double("0.0000153494"), Double("0.0000153164"), Double("0.0000152835"), Double("0.0000152507"), Double("0.0000152181"), Double("0.0000151856"), Double("0.0000151531"), Double("0.0000151208"), Double("0.0000150887"), Double("0.0000150566"), Double("0.0000150246"), Double("0.0000149928"), Double("0.0000149610"), Double("0.0000149294"), Double("0.0000148979"), Double("0.0000148665"), Double("0.0000148352"), Double("0.0000148040"), Double("0.0000147730"), Double("0.0000147420"), Double("0.0000147111"), Double("0.0000146804"), Double("0.0000146498"), Double("0.0000146192"), Double("0.0000145888"), Double("0.0000145585"), Double("0.0000145283"), Double("0.0000144981"), Double("0.0000144681"), Double("0.0000144382"), Double("0.0000144084"), Double("0.0000143787"), Double("0.0000143491"), Double("0.0000143196"), Double("0.0000142902"), Double("0.0000142609"), Double("0.0000142317"), Double("0.0000142026"), Double("0.0000141736"), Double("0.0000141447"), Double("0.0000141159"), Double("0.0000140872"), Double("0.0000140586"), Double("0.0000140301"), Double("0.0000140017"), Double("0.0000139734"), Double("0.0000139452"), Double("0.0000139170"), Double("0.0000138890"), Double("0.0000138611"), Double("0.0000138332"), Double("0.0000138055"), Double("0.0000137778"), Double("0.0000137502"), Double("0.0000137228"), Double("0.0000136954"), Double("0.0000136681"), Double("0.0000136409"), Double("0.0000136138"), Double("0.0000135867"), Double("0.0000135598"), Double("0.0000135330"), Double("0.0000135062"), Double("0.0000134795"), Double("0.0000134530"), Double("0.0000134265"), Double("0.0000134001"), Double("0.0000133737"), Double("0.0000133475"), Double("0.0000133213"), Double("0.0000132953"), Double("0.0000132693"), Double("0.0000132434"), Double("0.0000132176"), Double("0.0000131919"), Double("0.0000131662"), Double("0.0000131407"), Double("0.0000131152"), Double("0.0000130898"), Double("0.0000130645"), Double("0.0000130393"), Double("0.0000130141"), Double("0.0000129890"), Double("0.0000129640"), Double("0.0000129391"), Double("0.0000129143"), Double("0.0000128896"), Double("0.0000128649"), Double("0.0000128403"), Double("0.0000128158"), Double("0.0000127913"), Double("0.0000127670"), Double("0.0000127427"), Double("0.0000127185"), Double("0.0000126944"), Double("0.0000126703"), Double("0.0000126463"), Double("0.0000126224"), Double("0.0000125986"), Double("0.0000125749"), Double("0.0000125512"), Double("0.0000125276"), Double("0.0000125040"), Double("0.0000124806"), Double("0.0000124572"), Double("0.0000124339"), Double("0.0000124107"), Double("0.0000123875"), Double("0.0000123644"), Double("0.0000123414"), Double("0.0000123184"), Double("0.0000122956"), Double("0.0000122728"), Double("0.0000122500"), Double("0.0000122274"), Double("0.0000122048"), Double("0.0000121822"), Double("0.0000121598"), Double("0.0000121374"), Double("0.0000121151"), Double("0.0000120928"), Double("0.0000120706"), Double("0.0000120485"), Double("0.0000120265"), Double("0.0000120045"), Double("0.0000119826"), Double("0.0000119607"), Double("0.0000119389"), Double("0.0000119172"), Double("0.0000118956"), Double("0.0000118740"), Double("0.0000118525"), Double("0.0000118310"), Double("0.0000118096"), Double("0.0000117883"), Double("0.0000117670"), Double("0.0000117458"), Double("0.0000117247"), Double("0.0000117036"), Double("0.0000116826"), Double("0.0000116617"), Double("0.0000116408"), Double("0.0000116200"), Double("0.0000115992"), Double("0.0000115785"), Double("0.0000115579"), Double("0.0000115373"), Double("0.0000115168"), Double("0.0000114963"), Double("0.0000114760"), Double("0.0000114556"), Double("0.0000114354"), Double("0.0000114151"), Double("0.0000113950"), Double("0.0000113749"), Double("0.0000113549"), Double("0.0000113349"), Double("0.0000113150"), Double("0.0000112951"), Double("0.0000112753"), Double("0.0000112556"), Double("0.0000112359"), Double("0.0000112163"), Double("0.0000111967"), Double("0.0000111772"), Double("0.0000111577"), Double("0.0000111383"), Double("0.0000111190"), Double("0.0000110997"), Double("0.0000110804"), Double("0.0000110613"), Double("0.0000110421"), Double("0.0000110231"), Double("0.0000110041"), Double("0.0000109851"), Double("0.0000109662"), Double("0.0000109474"), Double("0.0000109286"), Double("0.0000109098"), Double("0.0000108911"), Double("0.0000108725"), Double("0.0000108539"), Double("0.0000108354"), Double("0.0000108169"), Double("0.0000107985"), Double("0.0000107801"), Double("0.0000107618"), Double("0.0000107435"), Double("0.0000107253"), Double("0.0000107071"), Double("0.0000106890"), Double("0.0000106710"), Double("0.0000106530"), Double("0.0000106350"), Double("0.0000106171"), Double("0.0000105992"), Double("0.0000105814"), Double("0.0000105636"), Double("0.0000105459"), Double("0.0000105283"), Double("0.0000105107"), Double("0.0000104931"), Double("0.0000104756"), Double("0.0000104581"), Double("0.0000104407"), Double("0.0000104233"), Double("0.0000104060"), Double("0.0000103887"), Double("0.0000103715"), Double("0.0000103543"), Double("0.0000103372"), Double("0.0000103201"), Double("0.0000103031"), Double("0.0000102861"), Double("0.0000102692"), Double("0.0000102523"), Double("0.0000102354"), Double("0.0000102186"), Double("0.0000102018"), Double("0.0000101851"), Double("0.0000101685"), Double("0.0000101518"), Double("0.0000101353"), Double("0.0000101187"), Double("0.0000101023"), Double("0.0000100858"), Double("0.0000100694"), Double("0.0000100531"), Double("0.0000100368"), Double("0.0000100205"), Double("0.0000100043"), Double("0.0000099881"), Double("0.0000099720"), Double("0.0000099559"), Double("0.0000099398"), Double("0.0000099238"), Double("0.0000099079"), Double("0.0000098919"), Double("0.0000098761"), Double("0.0000098602"), Double("0.0000098444"), Double("0.0000098287"), Double("0.0000098130"), Double("0.0000097973"), Double("0.0000097817"), Double("0.0000097661"), Double("0.0000097506"), Double("0.0000097351"), Double("0.0000097196"), Double("0.0000097042"), Double("0.0000096888"), Double("0.0000096735"), Double("0.0000096582"), Double("0.0000096429"), Double("0.0000096277"), Double("0.0000096126"), Double("0.0000095974"), Double("0.0000095823"), Double("0.0000095673"), Double("0.0000095523"), Double("0.0000095373"), Double("0.0000095223"), Double("0.0000095074"), Double("0.0000094926"), Double("0.0000094778"), Double("0.0000094630"), Double("0.0000094482"), Double("0.0000094335"), Double("0.0000094189"), Double("0.0000094042"), Double("0.0000093896"), Double("0.0000093751"), Double("0.0000093606"), Double("0.0000093461"), Double("0.0000093316"), Double("0.0000093172"), Double("0.0000093029"), Double("0.0000092885"), Double("0.0000092742"), Double("0.0000092600"), Double("0.0000092458"), Double("0.0000092316"), Double("0.0000092174"), Double("0.0000092033"), Double("0.0000091892"), Double("0.0000091752"), Double("0.0000091612"), Double("0.0000091472"), Double("0.0000091333"), Double("0.0000091194"), Double("0.0000091055"), Double("0.0000090917"), Double("0.0000090779"), Double("0.0000090641"), Double("0.0000090504"), Double("0.0000090367"), Double("0.0000090231"), Double("0.0000090094"), Double("0.0000089959"), Double("0.0000089823"), Double("0.0000089688"), Double("0.0000089553"), Double("0.0000089418"), Double("0.0000089284"),
        };
        lint kef_kol = 1000;
        Double a = *this,ans("0");
        for (lint i = 1; i < kef_kol;a=a*(*this), ++i) {
            ans += (kef[i] * a);
        }
        ans += kef[0];
        return ans;
    }
    Double pi() {
        Double ans("0"),a16("16"),a16_dop("1"),a8("8"), a1("1"), a2("2"), a4("4"), a5("5"), a6("6");
        lint limit = 100;
        Double k("0");
        Double dop8k, dop8k1, dop8k4, dop8k5, dop8k6;
        Double dop48k1, dop28k4, dop18k5, dop18k6;
        Double a1_a16_dop,dif;
        for (lint i = 0; i < limit; ++i,k+=a1, a16_dop= a16_dop*a16) {
            dop8k = a8 * k;
            dop8k1 = (dop8k + a1);
            dop8k4 = (dop8k + a4);
            dop8k5 = (dop8k + a5);
            dop8k6 = (dop8k + a6);
            dop48k1 = a4 / dop8k1;
            dop28k4 = a2 / dop8k4;
            dop18k5 = a1 / dop8k5;
            dop18k6 = a1 / dop8k6;
            a1_a16_dop = a1 / a16_dop;
            dif = dop48k1 - dop28k4 - dop18k5 - dop18k6;
            ans += (a1_a16_dop) * dif;
        }
        
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
    Double a("1.2");
    Double b("0.2");
    a=a/b;
    cout << a.convert_to_string();
    return 0;
}