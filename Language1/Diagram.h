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
	static bool FLInt; //���� �������������
	static bool FLReturn; //���� return 

	TDiagram(TScaner* s, Tree* root) {
		sc = s;
		Root = root;
	}
	~TDiagram() {}
	void S(); //���������
	void T(int); //�������� ������
	void W(); //��������
	void P(); //����������
	void F(); //�������
	void O(); //��������� ��������
	void OD(); //��������� � ��������
	void OP(); //��������
	void SW(); //switch
	void CS(Node*); //cases
	void DF(); //default
	void OPS(); //���������
	void V1(int, Node*, int); //��������� 1
	void V2(int, Node*, int); //��������� 2
	void V3(int, Node*, int); //��������� 3
	void V4(int, Node*, int); //��������� 4
	void V5(int, Node*, int); //��������� 5
	void V6(int, Node*, int); //��������� 6
	void VF(); //����� �������
	void N(); //���

	void workWithFunc(Node*, TypeLex);

	void setTLInt(bool n);
	bool getTLInt();

	void setTLReturn(bool n);
	bool getTLReturn();
};
#endif