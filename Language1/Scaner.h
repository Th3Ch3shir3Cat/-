#pragma once

#ifndef __SCANER
#define __SCANER
#include "defs.h"

class TScaner {
private:
	TypeMod t;
	int uk;
	int numStr;
	int numCh;
	int oldnumStr;
	int oldnumCh;

public:
	void PutUK(int i);
	int GetUK(void);
	void PutUK(int i, int row, int line);
	void GetUK(int& i, int& row, int& line);
	void PrintError(const char*, const char*);
	void PrintWarning(const char*, const char*);
	void PrintWarningTypes(int type1, int type2, int typeWarning);
	int Scaner(TypeLex l);
	void GetData(const char*);
	TScaner(const char*);
	~TScaner() {}
};

#endif