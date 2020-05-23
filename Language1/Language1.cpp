#include <iostream>
#include <cstdio>
#include <string>
#include "defs.h"
#include "Scaner.h"
#include "Diagram.h"
#include "tree.h"
#include "LL_K_.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "RUS");
	TScaner* sc;
	Tree* root;
	int type;
	TypeLex l;
	if (argc <= 1)
		sc = new TScaner("input.txt");
	else
		sc = new TScaner(argv[1]);
	root = new Tree();
	//TDiagram* dg = new TDiagram(sc, root);
	//dg->S();
	//root->Print();
	//type = sc->Scaner(l);
	LL_K_ *llk = new LL_K_(sc, root);
	llk->LL_K();
	type = sc->Scaner(l);
	if (type == type_end)
		printf("Синтаксических ошибок не обнаружено. \n");
	else
		sc->PrintError("Лишний текст в конце программы.", "");
	return 0;
}