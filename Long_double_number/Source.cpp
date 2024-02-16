#include "class_lib/Double.h"

using namespace Dominus;
int main()
{
    lint acc;
    cout<<"accuracy: ";
    cin>> acc;
    lint li = 9;
    lint mode = false;
    if (acc <=150){
        li=9;
        mode=false;
    }else {
        li =4;
        mode=true;
    }
    Dominus::Double ans("1",li, acc,mode);
	lint tim = clock();
	ans = Dominus::pi_16(li, acc, mode);
	cout << ans.convert_to_string() << endl << ((double)(clock() - tim) / CLOCKS_PER_SEC) << endl;
	return 0;
}