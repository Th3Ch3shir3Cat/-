#include "defs.h"
#include "tree.h"

#define max(a,b) a<b? b : a
#define EMPTY -1

Tree* Tree::cur;


Tree::Tree(Tree* l, Tree* r, Tree* u, Node* d) {
	n = new Node();
	Up = u; Left = l; Right = r; //установили ссылки
	memcpy(n, d, sizeof(Node));	//установили данные
}

Tree::Tree(void) {
	n = new Node();
	Up = NULL; Left = NULL; Right = NULL;
	memcpy(n, &("-----"), sizeof(Node));
	cur = this;
}

void Tree::setCur(Tree* a) {
	cur = a;
}

Tree* Tree::getCur() {
	return cur;
}

void Tree::setLeft(Node * Data) {	//новая вершина
	Tree* a = new Tree(NULL, NULL, this, Data);	//связали с а
	Left = a;
}

void Tree::setRight(Node* Data) {
	Tree* a = new Tree(NULL, NULL, this, Data);
	Right = a;
}

Tree * Tree::FindUp(TypeLex id) {
	return FindUp(this, id);
}



Tree* Tree::FindUp(Tree * From, TypeLex id) {
	Tree* i = From;
	while ((i != NULL) && (memcmp(id, i->n->id, max(strlen(i->n->id), strlen(id))) != 0))
		i = i->Up;
	return i;
}

Tree* Tree::FindUp(DATA_TYPE t) {
	Tree* current = cur;
	while (current != NULL && t != current->n->DataType != 0) {
		current = current->Up;
	}
	return current;
}

Tree* Tree::FindUpOneLevel(Tree* From, TypeLex id)
{
	Tree* i = From;
	while ((i != NULL) && i->Up != NULL &&
		(i->Up->Right != i)
		)
	{
		if (memcmp(id, i->n->id, max(strlen(i->n->id), strlen(id))) == 0)
			return i;
		i = i->Up;
	}
	return NULL;
}


int Tree::DupControl(Tree* addr, TypeLex id) { // проверка идентификатора на повторное описание внутри блока
	if (FindUpOneLevel(addr, id) == NULL)
		return 0;
	return 1;
}


Tree* Tree::FindRightLeft(TypeLex id) {
	//поиск прямых потомков текущей вершины this
	return FindRightLeft(this, id);
}

Tree* Tree::FindRightLeft(Tree* From, TypeLex id)
// поиск прямых потомков заданной вершины From
{
	Tree* i = From->Right; // текущая вершина
	while ((i != NULL) &&
		(memcmp(id, i->n->id, max(strlen(i->n->id), strlen(id))) != 0))
		i == i->Left;
	// обходим только соседей по левым связям
	return i;
}
void Tree::Print(void)
// отладочная программа печати дерева
{
	printf("Вершина с данными %s ----->", n->id);
	if (Left != NULL) printf(" слева данные %s", Left->n->id);
	if (Right != NULL) printf(" справа данные %s", Right->n->id);
	printf("\n");

	if (Right != NULL) Right->Print();
	if (Left != NULL) Left->Print();
}

void Tree::SemSetType(Tree* Addr, DATA_TYPE t)
{
	Addr->n->DataType = t;
}


Tree* Tree::SemGetType(TypeLex a)
{
	Tree* v = FindUp(cur, a);
	if (v == NULL)
		printf("Ошибка! Отсутствует описание идентификатора %s\n", a);
	else	if (v->n->DataType == TYPE_FUNCT)
		printf("Ошибка! Неверное использование вызова функции %s\n", a);
	return v;
}

Tree* Tree::SemGetFunct(TypeLex a)
{
	Tree* v = FindUp(cur, a);
	if (v == NULL)
		printf("отсутствует описание ф-ии ", a);
	if (v->n->DataType != TYPE_FUNCT)
		printf("не является функцией идентификатора ", a);
	return v;
}

Tree* Tree::SemGetValue(TypeLex a)
{
	Tree* v = FindUp(cur, a);
	if (v == NULL)
		printf("Ошибка! Отсутствует идентификатор %s\n", a);
	
	return v;
}

Tree* Tree::SemInclude(TypeLex a, DATA_TYPE t, int typeD, TScaner* sc)
{
	if (DupControl(cur, a))
		printf("Повторное описание идентификатора ", a);
	Tree* v; Node b;
	if (t != TYPE_FUNCT)
	{
		if (t == TYPE_INTEGER) {
			b.value.intData = 0;
			b.typeData = TYPE_INTEGER;
		}
		if (t == TYPE_FLOAT) {
			b.value.floatData = 0;
			b.typeData = TYPE_FLOAT;
		}

		memcpy(b.id, a, strlen(a) + 1); b.DataType = t; b.typeNode = typeD;
		cur->setLeft(&b);
		cur = cur->Left;
		return cur;
	}
	else
	{
		int startFuncUk, startFuncLine, startFuncPos;
		sc->GetUK(startFuncUk, startFuncPos ,startFuncLine);
		b.funcPosition.uk = startFuncUk;
		b.funcPosition.row = startFuncPos;
		b.funcPosition.line = startFuncLine;
		memcpy(b.id, a, strlen(a) + 1); b.DataType = t; b.typeNode = typeD;
		cur->setLeft(&b);
		cur = cur->Left;
		v = cur;
		memcpy(&b.id, &"", 2); b.DataType = EMPTY; b.typeNode = EMPTY;
		cur->setRight(&b);
		cur = cur->Right;
		return v;
	}

}

Tree* Tree::SemInclude(Node* node) {
	Node b;
	b.DataType = node->DataType;
	b.typeData = node->typeData;
	b.typeNode = node->typeNode;
	memcpy(b.id, node->id, strlen(node->id) + 1);
	b.funcPosition = node->funcPosition;
	cur->setLeft(&b);
	cur = cur->Left;
	return cur;
}

Tree* Tree::semAddBlock() {
	if (cur == nullptr)
		cur = this;
	Tree* v;
	Node b1, b2;
	memcpy(&b1.id, &"", 2); b1.DataType = EMPTY; b1.typeNode = EMPTY;
	memcpy(&b2.id, &"", 2); b2.DataType = EMPTY; b2.typeNode = EMPTY;
	cur->setLeft(&b1);
	cur = cur->Left;
	v = cur;
	cur->setRight(&b2);
	cur = cur->Right;
	return v;
}

Tree* Tree::DeleteBlock(Tree* From) {
	
	if (From->Left != NULL) DeleteBlock(From->Left);
	if (From->Right != NULL) DeleteBlock(From->Right);
	if (From->Up->Left) From->Up->Left = NULL;
	else
		From->Up->Right = NULL;
	return nullptr;
}


Node* Tree::getNode() const {
	return n;
}

Tree* Tree::findPlaceForDupFunc(Tree* root) {
	while (root->Left)
		root = root->Left;
	return root;
}

Tree* Tree::getRight() {
	return Right;
}