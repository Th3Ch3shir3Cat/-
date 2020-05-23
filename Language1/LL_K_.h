#pragma once
#include "defs.h"
#include "tree.h"
#include <iostream>

class LL_K_
{
private:
	
	int magazin[MAX_MAG];
	int z = 0;
	TScaner* sc;
	Tree* root; //корень семантического дерева
	int types[MAX_MAG]; //массив типов
	int typez = 0; //указатель на массив типов
	Tree* nodesFunc[MAX_MAG]; //массив вершин функций
	int nf = 0;

	int currentType; //последний отсканированный тип
	TypeLex currentId; //последний отканированный символ
	TypeLex currentConst; 
	int currentConstType; 
	
	bool flagData; //Флаг описания данных

	bool wasConst; // Флаг для константы

public:
	
	LL_K_(TScaner* sc, Tree* root);

	int LL_K();

	void epsilon();

	void workWithDelta(int t);

	bool isTerminal(int t);

	bool isDelta(int t);


};

