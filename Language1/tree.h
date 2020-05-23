
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

	TypeLex id;		//Идентификатор переменной
	int typeNode;
	int DataType;	//Тип значения(функция, идентификатор...)
	int sizeM;
	DATA_VALUE value; //значение
	DATA_TYPE typeData; //Тип вершины(float, int)
	Position funcPosition; //Позиция функции


};



class Tree {
	Node* n;	//Данные таблицы
	Tree* Up, *Left, *Right; //Родитель, левый и правый потомок

public:
	static Tree* cur;
	Tree(Tree* l, Tree* r, Tree* u, Node* Data);
	Tree();
	~Tree() {
	}
	void setLeft(Node *Data);	//записать новые данные левым потомком у текущей вершины
	void setRight(Node *Data);	//записать новый данные правым потомком у текущей вершины

	Tree* FindUp(Tree* From, TypeLex id);	//найти идентификатор в дереве от заданной вершины, 
											//передвигаясь по дереву только вверх от данной вершины


	Tree* FindUp(DATA_TYPE);

	Tree* FindUpOneLevel(Tree* From, TypeLex id);
	Tree* FindUp(TypeLex id);

	Tree* FindRightLeft(Tree *From, TypeLex id);	//выполнить поиск данных только по соседям одного уровня вложенности
	Tree* FindRightLeft(TypeLex id);
	

	void Print(void);

	void setCur(Tree* a);

	Tree* getCur();

	Tree* getRight();

	int DupControl(Tree* Addr, TypeLex a);
	// проверка идентификатора а на повторное описание внутри блока

	void SemSetType(Tree* Addr, DATA_TYPE t);
	// установить тип t для переменной по адресу Addr

	Tree* SemGetType(TypeLex a);
	// Найти в таблице переменую а

	Tree* SemGetFunct(TypeLex a);
	// найти в таблице функцию с именем а

	Tree* SemGetValue(TypeLex a);

	//Занести в таблицу идентификатор
	Tree* SemInclude(TypeLex a, DATA_TYPE t, int typeN, TScaner*);

	Tree* SemInclude(Node*);
	
	//занести в таблицу 
	Tree* semAddBlock();


	Tree* DeleteBlock(Tree *From);

	Node* getNode() const;

	Tree* findPlaceForDupFunc(Tree* root);

};
