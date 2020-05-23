#pragma once
#ifndef __DIAGRAM
#define __DIAGRAM
#include "tree.h";

class TDiagram
{
private:
	TScaner* sc;
	Tree* Root;

public:
	
	static int typeD;
	static int typeF;
	static bool FLInt; //Флаг интерпретации
	static bool FLReturn; //Флаг return 

	TDiagram(TScaner* s, Tree* root) {
		sc = s;
		Root = root;
	}
	~TDiagram() {}
	void S(); //программа
	void T(int); //описание данных
	void W(); //описание
	void P(); //переменная
	void F(); //функция
	void O(); //составной оператор
	void OD(); //операторы и описания
	void OP(); //оператор
	void SW(); //switch
	void CS(Node*); //cases
	void DF(); //default
	void OPS(); //операторы
	void V1(int, Node*, int); //выражение 1
	void V2(int, Node*, int); //выражение 2
	void V3(int, Node*, int); //выражение 3
	void V4(int, Node*, int); //выражение 4
	void V5(int, Node*, int); //выражение 5
	void V6(int, Node*, int); //выражение 6
	void VF(); //вызов функции
	void N(); //имя

	void workWithFunc(Node*, TypeLex);

	void setTLInt(bool n);
	bool getTLInt();

	void setTLReturn(bool n);
	bool getTLReturn();
};
#endif