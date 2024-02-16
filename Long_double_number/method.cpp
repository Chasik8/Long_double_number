#include "class_lib/Double.h"

using namespace Dominus;

Double Dominus::pi_16(lint li, lint acc, bool mode) {
	Double ans("0", li, acc, mode), a16("16", li, acc, mode), a16_dop("1", li, acc, mode), a8("8", li, acc, mode);
	Double a1("1", li, acc, mode), a2("2", li, acc, mode), a4("4", li, acc, mode), a5("5", li, acc, mode);
	Double a6("6", li, acc, mode);
	lint limit = (lint)(ans.get_accuracy() / 1.2041199826559248);
	Double k("0", li, acc, mode);
	Double dop8k("0", li, acc, mode);
	Double a1_a16_dop, dif, dop;
	for (lint i = 0; i < limit; ++i, k += a1, dop8k += a8, a16_dop = a16_dop * a16) {
		dif = a4 / (dop8k + a1) - a2 / (dop8k + a4) - a1 / (dop8k + a5) - a1 / (dop8k + a6);
		a1_a16_dop = a1 / a16_dop;
		dop = (a1_a16_dop)*dif;
		ans += dop;
	}
	ans.clear();
	return ans;
}