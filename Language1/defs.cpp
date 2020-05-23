#include "defs.h"

std::string TypeDataToString(int t) {
	if (t == type_int) {
		return "__int64";
	}
	else if (t == type_float) {
		return "float";
	}
	return "Неопределенный тип";
}