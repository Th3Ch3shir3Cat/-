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
	Tree* root; //������ �������������� ������
	int types[MAX_MAG]; //������ �����
	int typez = 0; //��������� �� ������ �����
	Tree* nodesFunc[MAX_MAG]; //������ ������ �������
	int nf = 0;

	int currentType; //��������� ��������������� ���
	TypeLex currentId; //��������� �������������� ������
	TypeLex currentConst; 
	int currentConstType; 
	
	bool flagData; //���� �������� ������

	bool wasConst; // ���� ��� ���������

public:
	
	LL_K_(TScaner* sc, Tree* root);

	int LL_K();

	void epsilon();

	void workWithDelta(int t);

	bool isTerminal(int t);

	bool isDelta(int t);


};

