#include "Double.h" 
using namespace Dominus;

 Double Dominus::pi_16() {
	Double ans("0"), a16("16"), a16_dop("1"), a8("8"), a1("1"), a2("2"), a4("4"), a5("5"), a6("6");
	lint limit = (lint)((double)ans.get_accuracy()/(double)1.2041199826559248);
	Double k("0");
	Double dop8k;
	Double a1_a16_dop, dif, dop;
	for (lint i = 0; i < limit; ++i, k += a1, dop8k += a8, a16_dop = a16_dop * a16) {
		if (i == 89) {
			cout << "AA";
		}
		dif = a4 / (dop8k + a1) - a2 / (dop8k + a4) - a1 / (dop8k + a5) - a1 / (dop8k + a6);
		a1_a16_dop = a1 / a16_dop;
		dop = (a1_a16_dop)*dif;
		ans += dop;
	}
	if (ans.get_mode_fast()) {
		ans.N(14);
	}
	return ans;
}