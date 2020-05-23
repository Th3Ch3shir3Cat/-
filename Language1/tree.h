
#pragma once
#include "defs.h"
#include "Scaner.h"

enum DATA_TYPE {
	TYPE_UNKNOWN = 1, TYPE_INTEGER,
	TYPE_FLOAT, TYPE_CHAR, TYPE_FUNCT
};

/*
	
*/
union DATA_VALUE {
	__int64 intData;
	float floatData;
};
struct Position {
	int uk;
	int line;
	int row;

	Position() {

	}

	Position(int uk, int line, int row) {
		this->uk = uk;
		this->line = line;
		this->row = row;
	}

	void getValue(int& _uk, int& _line, int& _row) {
		_uk = uk;
		_line = line;
		_row = row;
	}
};
struct Node {

	TypeLex id;		//������������� ����������
	int typeNode;
	int DataType;	//��� ��������(�������, �������������...)
	int sizeM;
	DATA_VALUE value; //��������
	DATA_TYPE typeData; //��� �������(float, int)
	Position funcPosition; //������� �������


};



class Tree {
	Node* n;	//������ �������
	Tree* Up, *Left, *Right; //��������, ����� � ������ �������

public:
	static Tree* cur;
	Tree(Tree* l, Tree* r, Tree* u, Node* Data);
	Tree();
	~Tree() {
	}
	void setLeft(Node *Data);	//�������� ����� ������ ����� �������� � ������� �������
	void setRight(Node *Data);	//�������� ����� ������ ������ �������� � ������� �������

	Tree* FindUp(Tree* From, TypeLex id);	//����� ������������� � ������ �� �������� �������, 
											//������������ �� ������ ������ ����� �� ������ �������


	Tree* FindUp(DATA_TYPE);

	Tree* FindUpOneLevel(Tree* From, TypeLex id);
	Tree* FindUp(TypeLex id);

	Tree* FindRightLeft(Tree *From, TypeLex id);	//��������� ����� ������ ������ �� ������� ������ ������ �����������
	Tree* FindRightLeft(TypeLex id);
	

	void Print(void);

	void setCur(Tree* a);

	Tree* getCur();

	Tree* getRight();

	int DupControl(Tree* Addr, TypeLex a);
	// �������� �������������� � �� ��������� �������� ������ �����

	void SemSetType(Tree* Addr, DATA_TYPE t);
	// ���������� ��� t ��� ���������� �� ������ Addr

	Tree* SemGetType(TypeLex a);
	// ����� � ������� ��������� �

	Tree* SemGetFunct(TypeLex a);
	// ����� � ������� ������� � ������ �

	Tree* SemGetValue(TypeLex a);

	//������� � ������� �������������
	Tree* SemInclude(TypeLex a, DATA_TYPE t, int typeN, TScaner*);

	Tree* SemInclude(Node*);
	
	//������� � ������� 
	Tree* semAddBlock();


	Tree* DeleteBlock(Tree *From);

	Node* getNode() const;

	Tree* findPlaceForDupFunc(Tree* root);

};
