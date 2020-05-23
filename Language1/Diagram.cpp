#include "defs.h"
#include "Scaner.h"
#include "Diagram.h"
#include <cstdlib>
#include <iostream>
#include "tree.h"
#include <stdio.h>

using namespace std;


bool TDiagram::FLInt = true;
bool TDiagram::FLReturn = false;

//���������
void TDiagram::S() {
	TypeLex l;
	int t, uk1;
	uk1 = sc->GetUK();
	t = sc->Scaner(l);
	while (t != type_end) {
		sc->PutUK(uk1);
		W();
		uk1 = sc->GetUK();
		t = sc->Scaner(l);
	};
}

//��������� ��������
void TDiagram::O() {
	TypeLex l;
	int t, uk1;
	t = sc->Scaner(l);
	if (t != type_lfsk) {
		sc->PrintError("�������� ������ {", l);
		exit(0);
	}
	Tree *v = NULL;
	if(FLInt && !FLReturn)
		v = Root->semAddBlock();
	OD();
	uk1 = sc->GetUK();
	t = sc->Scaner(l);
	if (t != type_rfsk) {
		sc->PrintError("�������� ������ }", l);
		exit(0);
	}
}

//�������� ������
void TDiagram::T(int typeP) {
	TypeLex l;
	int t, uk1;
	uk1 = sc->GetUK();
	t = sc->Scaner(l);
	sc->PutUK(uk1);
	do {
		uk1 = sc->GetUK();
		t = sc->Scaner(l);
		if (t != type_ident) {
			sc->PrintError("�������� ��������������", l);
			exit(0);
			return;
		}
		Tree* v;
		if (typeP == 1 && FLInt && !FLReturn)
			v = Root->SemInclude(l, TYPE_FLOAT, typeD,sc);
		else if (typeP == 2 && FLInt && !FLReturn)
			v = Root->SemInclude(l, TYPE_INTEGER, typeD,sc);
		else if(FLInt && !FLReturn) v = Root->SemInclude(l, TYPE_UNKNOWN, typeD,sc);
		
		t = sc->Scaner(l);
	} while (t == type_zap);
}

//��������
void TDiagram::W() {
	TypeLex l;
	int t,t1, uk1;
	uk1 = sc->GetUK();
	t = sc->Scaner(l);
	t1 = t;
	if (t != type_float && t != type_int) {
		//���� ����� ���������� ����������
		if (t == type_ident) {
			sc->PutUK(uk1);
			P();
			t = sc->Scaner(l);
			return;
		}
		else {
			sc->PrintError("�������� ������������ float ��� int", l);
			exit(0);
		}
	}
	uk1 = sc->GetUK();
	t = sc->Scaner(l);
	if (t != type_ident) {
		sc->PrintError("�������� �������������", l);
		exit(0);
	}

	int i = 0;
	t = sc->Scaner(l);
	if (t == type_lsk) {
		sc->PutUK(uk1);
		F();
	}
	else {
		sc->PutUK(uk1);
		T(t1);
	}
}

//����������
void TDiagram::P() {
	TypeLex l;
	int t, uk1;
	t = sc->Scaner(l);
	Tree* v = Root->SemGetValue(l);
		if (t != type_ident) {
			sc->PrintError("�������� �������������", l);
			exit(0);
		}
		t = sc->Scaner(l);
		if (t == type_equal) {
			V1(typeD, v->getNode(),t);
		}
}


//�������
void TDiagram::F() {
	TypeLex l;
	//����� � ������� ������ ���� return � false
	setTLReturn(false);
	int t, uk1;
	t = sc->Scaner(l);
	Tree *v = NULL;
	if (FLInt && !FLReturn) {
		v = Root->SemInclude(l, TYPE_FUNCT, typeD, sc);
		typeF = v->getNode()->typeNode;
	}
	else
		v = Root->SemGetFunct(l);
	t = sc->Scaner(l);
	if (t != type_lsk) {
		sc->PrintError("�������� ������ (", l);
		exit(0);
	}
	t = sc->Scaner(l);
	if (t != type_rsk) {
		sc->PrintError("�������� ������ )", l);
		exit(0);
	}
	O();
	if(FLInt && !FLReturn)
		Root->setCur(v);
}

//��������� � ��������
void TDiagram::OD() {
	TypeLex l;
	int t, t1, uk1;
	uk1 = sc->GetUK();
	t = sc->Scaner(l);
	while (t != type_rfsk) {
		if (t == type_float || t == type_int) {

			t1 = t;
			T(t1);
		}
		else {
			sc->PutUK(uk1);
			OP();
		}
		uk1 = sc->GetUK();
		t = sc->Scaner(l);
		if (t == type_end) {
			sc->PrintError("�������� ������ }", "");
			exit(0);
		}
	};
	sc->PutUK(uk1);
}

//��������
void TDiagram::OP() {
	TypeLex l;
	int t, uk1;
	uk1 = sc->GetUK();
	t = sc->Scaner(l);
	if (t == type_tzap) return;
	if (t == type_switch) {
		sc->PutUK(uk1);
		SW();
		t = sc->Scaner(l);
		if (t != type_tzap) {
			sc->PrintError("�������� ������ ", l);
			exit(0);
		}
		return;
	}
	if (t == type_return) {
		uk1 = sc->GetUK();
		t = sc->Scaner(l);
		sc->PutUK(uk1);
		if (t != type_ident) {
			sc->PrintError("�������� �������������", l);
			exit(0);
		}
		Tree* v = Root->SemGetType(l);
		if (v != NULL) {
			typeD = v->getNode()->typeNode;
			Tree* v1 = Root->FindUp(TYPE_FUNCT);
			v1->getNode()->value = v->getNode()->value;
			t = sc->Scaner(l);
			t = sc->Scaner(l);
			if (t != type_tzap) {
				sc->PrintError("������� ������ ;", l);
				exit(0);
			}
		}
		setTLReturn(true);
		return;
	}
	if (t == type_break) {
		t = sc->Scaner(l);
		if (t != type_tzap) {
			sc->PrintError("������� ������ ;", l);
			exit(0);
		}
		return;
	}
	if (t == type_ident) {
		sc->PutUK(uk1);
		P();
		t = sc->Scaner(l);
		if (t != type_tzap) {
			sc->PrintError("��������� ;", l);
			exit(0);
		}
		return;
	}
	if (t == type_lfsk) {
		sc->PutUK(uk1);
		O();
		return;
	}
}

//switch
void TDiagram::SW() {
	TypeLex l;
	int t, uk1;
	uk1 = sc->GetUK();
	t = sc->Scaner(l);
	
	if (t != type_switch) {
		sc->PrintError("�������� �������� switch", l);
		exit(0);
	}
	t = sc->Scaner(l);
	if (t != type_lsk) {
		sc->PrintError("�������� ������ (", l);
		exit(0);
	}
	t = sc->Scaner(l);
	if (t != type_const && t != type_ident) {
		sc->PrintError("��������� ��������� ��� �������������", l);
		exit(0);
	}
	//���������� �������� �������������� � switch
	Node *v = Root->SemGetValue(l)->getNode();
	t = sc->Scaner(l);
	if (t != type_rsk) {
		sc->PrintError("�������� ������ )", l);
		exit(0);
	}
	t = sc->Scaner(l);
	if (t != type_lfsk) {
		sc->PrintError("�������� ������ {", l);
		exit(0);
	}
	uk1 = sc->GetUK();
	t = sc->Scaner(l);
	sc->PutUK(uk1);
	if (t != type_case) {
		sc->PrintError("�������� �������� case", l);
		exit(0);
	}
	//��������� ������� �������� ����� �������������
	bool localFlag = getTLInt();
	CS(v);
	uk1 = sc->GetUK();
	t = sc->Scaner(l);
	if (t == type_default) {
		sc->PutUK(uk1);
		DF();
	}
	//��������������� ����
	setTLInt(localFlag);
}

//cases
void TDiagram::CS(Node* mainVal) {
	TypeLex l;
	int t, uk1;
	uk1 = sc->GetUK();
	t = sc->Scaner(l);
	while (t == type_case) {
		t = sc->Scaner(l);
		if (t != type_lsk && t != type_const) {
			sc->PrintError("�������� ������ ( ��� ���������", l);
			exit(0);
		}
		
		//��������� ����� �������� ����� �������������
		if (FLInt && mainVal->value.intData == (__int64)atoi(l)) FLInt = true;
		else
			FLInt = false;
		
		t = sc->Scaner(l);
		if (t != type_rsk && t != type_dvd) {
			sc->PrintError("�������� ������ ) ��� :", l);
			exit(0);
		}
		OPS();
		//����������� �������� ����� ������������� ���� �������� ���� 1
		if(FLInt)
			FLInt = 1 - FLInt;
		uk1 = sc->GetUK();
		t = sc->Scaner(l);
	}
	sc->PutUK(uk1);
}

//default
void TDiagram::DF() {
	TypeLex l;
	int t, uk1;
	t = sc->Scaner(l);
	if (t != type_default) {
		sc->PrintError("�������� �������� default", l);
		exit(0);
	}
	t = sc->Scaner(l);
	if (t != type_dvd) {
		sc->PrintError("�������� ������ :", l);
		exit(0);
	}
	OPS();
	t = sc->Scaner(l);
	if (t != type_rfsk) {
		sc->PrintError("�������� ������ }", "");
		exit(0);
	}
}

//���������
void TDiagram::OPS() {
	TypeLex l;
	int t, uk1;
	uk1 = sc->GetUK();
	t = sc->Scaner(l);
	sc->PutUK(uk1);
	while (t == type_ident || t == type_switch
		|| t == type_return || t == type_break
		|| t == type_lfsk) {
		OP();
		uk1 = sc->GetUK();
		t = sc->Scaner(l);
		sc->PutUK(uk1);
	};
}

//��������� 1
void TDiagram::V1(int tD, Node *n, int z) {
	TypeLex l;
	int t, uk1;
	uk1 = sc->GetUK();
	t = sc->Scaner(l);
	if ((t != type_plus) && (t != type_minus))
		sc->PutUK(uk1);
	V2(tD,n,z);
	uk1 = sc->GetUK();
	t = sc->Scaner(l);
	while ((t == type_comp) || (t == type_ncomp)) {
		V2(tD,n,t);
		uk1 = sc->GetUK();
		t = sc->Scaner(l);
	};
	sc->PutUK(uk1);
}

//��������� 2
void TDiagram::V2(int tD, Node* n, int z) {
	TypeLex l;
	int t, uk1;
	V3(tD, n,z);
	uk1 = sc->GetUK();
	t = sc->Scaner(l);
	while ((t == type_gt) || (t == type_gtcomp) || t == type_lt || t == type_ltcomp) {
		V3(tD, n,t);
		uk1 = sc->GetUK();
		t = sc->Scaner(l);
	};
	sc->PutUK(uk1);
}

//��������� 3
void TDiagram::V3(int tD, Node* n, int z) {
	TypeLex l;
	int t, uk1;
	V4(tD, n,z);
	uk1 = sc->GetUK();
	t = sc->Scaner(l);
	while ((t == type_minus) || (t == type_plus)) {
		//t = sc->Scaner(l);
		V4(tD, n,t);
		uk1 = sc->GetUK();
		t = sc->Scaner(l);
	};
	sc->PutUK(uk1);
}

//��������� 4
void TDiagram::V4(int tD, Node* n, int z) {
	TypeLex l;
	int t, uk1;
	V5(tD, n,z);
	uk1 = sc->GetUK();
	t = sc->Scaner(l);

	while ((t == type_umg) || (t == type_razd)) {
		V5(tD, n,t);
		uk1 = sc->GetUK();
		t = sc->Scaner(l);
	};
	sc->PutUK(uk1);
}

//��������� 5
void TDiagram::V5(int tD, Node* n, int z) {
	TypeLex l;
	int t, uk1;
	uk1 = sc->GetUK();
	t = sc->Scaner(l);
	if (t == type_dplus || t == type_dminus) {
		V6(tD, n,t);
	}
	else {
		sc->PutUK(uk1);
		V6(tD,n,z);
		uk1 = sc->GetUK();
		t = sc->Scaner(l);
		if (t != type_dplus && t != type_dminus)
			sc->PutUK(uk1);
	}
}

//��������� 6
void TDiagram::V6(int tD, Node* n, int z) {
	TypeLex l;
	TypeLex lf;
	int t, t1, uk1, tP;
	uk1 = sc->GetUK();
	t = sc->Scaner(l);

	if ((t == type_const_ch) || (t == type_const)
		|| (t == type_const_exp) || (t == type_const_exp1)
		|| (t == type_const_str) || t == type_ident || t == type_const_float) {

		//�������������
		if (t == type_ident) {
			if(z == type_equal){
				uk1 = sc->GetUK();
				//�������� �� ����� �������
				t1 = sc->Scaner(lf);
				if (t1 == type_lsk) {
					
					//�������� �������

					workWithFunc(n, l);
					if(FLInt)
						switch (n->typeData) {
						case 2: //��� __int64
							printf("%s = %I64d\n", n->id, n->value.intData);
							break;
						case 3: //��� float
							printf("%s = %f\n", n->id, n->value.floatData);
							break;
						}

					t = sc->Scaner(l);
				}
				else {
					if (FLInt && !FLReturn) { //����������� �������� ��� ����� ������������� = 1 � ����� return false

						//���� �� ������� � ���� ����� �� ����������� ����� ��������

						Tree* v1 = Root->SemGetValue(l);
						switch (n->typeData) {
						case 2: //��� ������� __int64
							switch (v1->getNode()->typeData) {
							case 2: //��� ������� __int64
								n->value.intData = v1->getNode()->value.intData;
								printf("%s = %I64d\n", n->id, n->value.intData);
								break;
							case 3: //��� �������� float
								n->value.intData = v1->getNode()->value.floatData;
								printf("%s = %I64d\n", n->id, n->value.intData);
								break;
							}
							break;
						case 3: //��� ������� float
							switch (v1->getNode()->typeData) {
							case 2: //��� ������� int
								n->value.floatData = v1->getNode()->value.intData;
								printf("%s = %f\n", n->id, n->value.floatData);
								break;
							case 3: //��� �������� float
								n->value.floatData = v1->getNode()->value.floatData;
								printf("%s = %f\n", n->id, n->value.floatData);
								break;
							}
							break;
						}
						sc->PutUK(uk1);
					}
					sc->PutUK(uk1);
				}
			}
			else {//���� ���� �������� �� ����� ������ ����� ����� ���������� ����������
				if (FLInt && !FLReturn) {
					Tree* v2 = Root->SemGetValue(l);
					switch (n->typeData) {
					case 2: //��� ������� int
						switch (v2->getNode()->typeData) {
						case 2: // ��� ������� __int64
							switch (z) {
							case type_plus:
								n->value.intData += v2->getNode()->value.intData;
								printf("%s = %I64d\n", n->id, n->value.intData);
								break;
							case type_minus:
								n->value.intData -= v2->getNode()->value.intData;
								printf("%s = %I64d\n", n->id, n->value.intData);
								break;
							case type_umg:
								n->value.intData *= v2->getNode()->value.intData;
								printf("%s = %I64d\n", n->id, n->value.intData);
								break;
							case type_razd:
								n->value.intData /= v2->getNode()->value.intData;
								printf("%s = %I64d\n", n->id, n->value.intData);
								break;
							default:
								break;
							}
							break;
						case 3: //��� ������� float
							switch (z) {
							case type_plus:
								n->value.intData += v2->getNode()->value.floatData;
								printf("%s = %I64d\n", n->id, n->value.intData);
								break;
							case type_minus:
								n->value.intData -= v2->getNode()->value.floatData;
								printf("%s = %I64d\n", n->id, n->value.intData);
								break;
							case type_umg:
								n->value.intData *= v2->getNode()->value.floatData;
								printf("%s = %I64d\n", n->id, n->value.intData);
								break;
							case type_razd:
								n->value.intData /= v2->getNode()->value.floatData;
								printf("%s = %I64d\n", n->id, n->value.intData);
								break;
							default:
								break;
							}
							break;
						}
						break;
					case 3: //��� ������� float
						switch (v2->getNode()->typeData) {
						case 2: //��� ������� __int64
							switch (z) {
							case type_plus:
								n->value.floatData += v2->getNode()->value.intData;
								printf("%s  = %f\n", n->id, n->value.floatData);
								break;
							case type_minus:
								n->value.floatData -= v2->getNode()->value.intData;
								printf("%s  = %f\n", n->id, n->value.floatData);
								break;
							case type_umg:
								n->value.floatData *= v2->getNode()->value.intData;
								printf("%s = %f\n", n->id, n->value.floatData);
								break;
							case type_razd:
								n->value.floatData /= v2->getNode()->value.intData;
								printf("%s = %f\n", n->id, n->value.floatData);
								break;
							default:
								break;
							}
							break;
						case 3: //��� ������� float
							switch (z) {
							case type_plus:
								n->value.floatData += v2->getNode()->value.floatData;
								printf("%s = %f\n", n->id, n->value.floatData);
								break;
							case type_minus:
								n->value.floatData -= v2->getNode()->value.floatData;
								printf("%s  = %f\n", n->id, n->value.floatData);
								break;
							case type_umg:
								n->value.floatData *= v2->getNode()->value.floatData;
								printf("%s = %f\n", n->id, n->value.floatData);
								break;
							case type_razd:
								n->value.floatData /= v2->getNode()->value.floatData;
								printf("%s = %f\n", n->id, n->value.floatData);
								break;
							default:
								break;
							}
							break;
						}
						break;
					}
				}
			}
			
		}
		else { //���������
			if (FLInt && !FLReturn) {
				if (z == type_equal) {
					switch (n->typeData) {
						//��� __int64
					case 2:
						n->value.intData = (__int64)atoi(l);
						break;
						//��� float
					case 3:
						n->value.floatData = std::atof(l);
						break;
					default:
						break;
					}
					if (n->typeData == 2) { //��� __int64
						printf("%s = %I64d\n", n->id, n->value.intData);
					}
					else { //��� float
						printf("%s = %f\n", n->id, n->value.floatData);
					}
				}
			}
		}
		return;
	}
	if (t == type_lsk) {
		V1(tD,n, z);
		t = sc->Scaner(l);
		if (t != type_rsk) {
			sc->PrintError("�������� ������ )", l);
			exit(0);
		}
		return;
	}
	t = sc->Scaner(l);
	sc->PutUK(uk1);
	if (t == type_lsk)
		VF();
	else
		N();
}

//���
void TDiagram::N() {
	TypeLex l;
	int t, uk1;
	do {
		t = sc->Scaner(l);
		if (t != type_ident) {
			sc->PrintError("�������� �������������", l);
			exit(0);
		}
		uk1 = sc->GetUK();
		t = sc->Scaner(l);
	} while (t != type_tzap);
	sc->PutUK(uk1);
}

//����� �������
void TDiagram::VF() {
	TypeLex l;
	int t;
	t = sc->Scaner(l);
	if (t != type_ident) {
		sc->PrintError("�������� �������������", l);
		exit(0);
	}
	t = sc->Scaner(l);
	if (t != type_lsk) {
		sc->PrintError("�������� ������ (", l);
		exit(0);
	}
	t = sc->Scaner(l);
	if (t != type_rsk) {
		sc->PrintError("�������� ������ )", l);
		exit(0);
	}
}



void TDiagram::workWithFunc(Node* n, TypeLex nameFunc) {
	//���� ���� ������������� false ������ �����
	if (!getTLInt())
		return;
	Tree* v = Root->SemGetFunct(nameFunc);
	
	setTLReturn(false);

	printf("Call %s\n", nameFunc);
	//��������� ������� �������
	int saveUk, savePos, saveLine;
	sc->GetUK(saveUk, savePos, saveLine);
	//������ ������� �� ������ �����
	int funcUk, funcPos, funcLine;
	v->getNode()->funcPosition.getValue(funcUk, funcLine,funcPos);
	funcUk += 2;
	sc->PutUK(funcUk, funcPos, funcLine);
	Tree* lastCur = Root->getCur();
	Root->setCur(Root->findPlaceForDupFunc(Root));
	Tree* dupFunc = Root->SemInclude(v->getNode());
	//��������� ��������
	O();
	setTLInt(true);
	Root->setCur(lastCur);
	n->value = dupFunc->getNode()->value;
	//������� ������� �������
	Root->DeleteBlock(dupFunc);
	sc->PutUK(saveUk, saveLine, savePos);

}

void TDiagram::setTLInt(bool n) {
	this->FLInt = n;
}

bool TDiagram::getTLInt() {
	return this->FLInt;
}

void TDiagram::setTLReturn(bool n) {
	this->FLReturn = n;
}

bool TDiagram::getTLReturn() {
	return this->FLReturn;
}

int TDiagram::typeD = 0;
int TDiagram::typeF = 0;