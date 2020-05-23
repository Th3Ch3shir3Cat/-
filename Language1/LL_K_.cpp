#include "LL_K_.h"

void LL_K_::epsilon() {
	z--;
}

LL_K_::LL_K_(TScaner* sc, Tree* v) {
	this->root = v;
	this->sc = sc;
}

int LL_K_::LL_K() {
	
	int t;
	int flag = 1;
	TypeLex l;

	magazin[z++] = type_end;
	magazin[z] = netermProgram;

	t = sc->Scaner(l);

	while (flag) {
		if (isTerminal(magazin[z])) {
			//�������� ��������� � ����������
			if (magazin[z] == t) {
				//����� ������
				if (t == type_end) {
					flag = 0;
				}
				else {
					t = sc->Scaner(l);//��������� ����� ������
					//��������� ��������� ��������������� �������������
					if (t == type_ident)
						strcpy_s(currentId, l);
					else if (t == type_const || t == type_const_float) {
						strcpy_s(currentConst, l);
						currentConstType = t;
					}
					z--; //������� �������� ��������
				}
			}
			else if (isDelta(magazin[z])) {
				workWithDelta(magazin[z]);
				z--;
			}
			else { //��������� ������
				sc->PrintError("�������� ������, �������� ", l);
				return -1;
			}
		}
		else {
			switch (magazin[z]) {
			case netermProgram: {
				if (t == type_int || t == type_float) {
					magazin[z++] = netermProgram;
					magazin[z++] = netermOpisanie;
				}
				else if (t == type_ident) {	
					magazin[z++] = netermProgram;
					magazin[z++] = netermOpertor;
				}
				break;
			}

			case netermOpisanie: {
				if (t == type_int || t == type_float) {
					TypeLex l1;
					int tmpUk = sc->GetUK();
					int t1;
					t1 = sc->Scaner(l1);
					t1 = sc->Scaner(l1);
					if (t1 == type_lsk) {
						//����� ������ �������� ������
						magazin[z++] = EndFlagData;
						//����� � ������ �������
						magazin[z++] = EndIncludeFunc;
						magazin[z++] = netermSostOper;
						magazin[z++] = type_rsk;
						magazin[z++] = type_lsk;
						//�������� �� ����������� ������� � ��������� � � �������
						magazin[z++] = IncludeFunc;
						magazin[z++] = type_ident;
						magazin[z++] = netermType;
					}
					else {
						magazin[z++] = netermOpisanieDannix;
					}
					sc->PutUK(tmpUk);
				}
				break;
			}

			case netermType: {
				if (t == type_int) {
					currentType = type_int;
					//��������� ���� �������� ������
					magazin[z++] = StartFlagData;
					magazin[z++] = type_int;
				}
				else if (t == type_float) {
					currentType = type_float;
					//��������� ���� �������� ������
					magazin[z++] = StartFlagData;
					magazin[z++] = type_float;
				}
				else
					sc->PrintError("�������� ������, �������� __int64 ��� float ", l);
				break;
			}
			case netermOpisanieDannix: {
				if (t == type_int || t == type_float) {
					//����� ������ �������� ������
					magazin[z++] = EndFlagData;
					magazin[z++] = type_tzap;
					magazin[z++] = netermListPerem;
					magazin[z++] = netermType;
				}
				else
					sc->PrintError("�������� ������, �������� __int64 ��� float ", l);
				break;
			}
			case netermListPerem: {
				if (t == type_ident) {
					magazin[z++] = netermListPerem1;
					magazin[z++] = netermPrisvaivanie1;
					//�������� �������������� �� ������������ � ��� ���������
					magazin[z++] = IncludeVar;
					magazin[z++] = type_ident;
				}
				else
					sc->PrintError("�������� ������. �������� ������������� ", l);
				break;
			}

			case netermListPerem1: {
				if (t == type_zap) {
					magazin[z++] = netermListPerem;
					magazin[z++] = type_zap;
				}
				else if (t == type_tzap) {

				}
				else
					sc->PrintError("�������� ������. ��������� ������� , ;", l);
				break;
			}

			case netermPrisvaivanie1: {
				if (t == type_equal)
					magazin[z++] = netermPrisvaivanie;
				else if (t == type_tzap || t == type_zap) {

				}
				else
					sc->PrintError("�������� ������, �������� ������ = , ;", l);
				break;
			}

			case netermPrisvaivanie: {
				if (t == type_equal) {
					//���������� ����� ���������
					magazin[z++] = CastVar;
					magazin[z++] = netermExpression1;
					magazin[z++] = type_equal;
				}
				else
					sc->PrintError("�������� ������. ��������� ������� = ", l);
				break;
			}

			case netermSostOper: {
				if (t == type_lfsk) {
					//����� � ������
					magazin[z++] = RetFromLevel;
					magazin[z++] = type_rfsk;
					magazin[z++] = netermOperatorAndOpisanie;
					//������ ������ ������
					magazin[z++] = StartNewLevel;
					magazin[z++] = type_lfsk;
				}
				else
					sc->PrintError("�������� ������. ��������� {", l);
				break;
			}

			case netermOperatorAndOpisanie: {
				if (t == type_float || t == type_int) {
					magazin[z++] = netermOperatorAndOpisanie;
					magazin[z++] = netermOpisanieDannix;
				}
				else if (t == type_return || t == type_ident || t == type_switch || t == type_lfsk || t == type_tzap || t == type_break) {
					magazin[z++] = netermOperatorAndOpisanie;
					magazin[z++] = netermOpertor;
				}
				break;
			}

			case netermOpertor: {
				if (t == type_return) {
					magazin[z++] = type_tzap;
					//�������� ������������� ��������
					magazin[z++] = CheckReturn;
					magazin[z++] = netermExpression1;
					magazin[z++] = type_return;
				}
				else if (t == type_ident) {
					magazin[z++] = type_tzap;
					magazin[z++] = netermPrisvaivanie;
					//����� �������������� � ������� � ����������� ��� ����
					magazin[z++] = FindVar;
					magazin[z++] = type_ident;
				}
				else if (t == type_switch) {
					magazin[z++] = netermSwitch;
				}
				else if (t == type_break) {
					magazin[z++] = type_break;
				}
				else if (t == type_lfsk) {
					magazin[z++] = netermSostOper;
				}
				else if (t == type_tzap) {
					magazin[z++] = type_tzap;
				}
				else
					sc->PrintError("�������� ������. �������� �������� ", l);
				break;
			}

			case netermSwitch: {
				magazin[z++] = netermSostOperForSwitch;
				magazin[z++] = type_rsk;
				TypeLex l1;
				int t1;
				int tmpUk = sc->GetUK();
				t1 = sc->Scaner(l1);
				t1 = sc->Scaner(l1);
				if (t1 == type_const) {
					magazin[z++] = type_const;
				}
				else if (t1 == type_ident) {
					t1 = sc->Scaner(l1);
					if (t1 == type_equal) {
						magazin[z++] = netermExpression1;
					}
					magazin[z++] = type_ident;
				}
				magazin[z++] = type_lsk;
				magazin[z++] = type_switch;
				sc->PutUK(tmpUk);
				break;
			}

			case netermSostOperForSwitch: {
				//����� � ������ �����
				magazin[z++] = RetFromLevel;
				magazin[z++] = type_rfsk;
				magazin[z++] = netermDefault;
				magazin[z++] = netermCases;
				//���� �� ������� �����
				magazin[z++] = StartNewLevel;
				magazin[z++] = type_lfsk;
				break;
			}

			case netermCases: {
				if (t == type_case) {
					magazin[z++] = netermCases;
					magazin[z++] = type_tzap;
					magazin[z++] = netermOperators;
					magazin[z++] = type_dvd;
					//����������� ���� ���������
					magazin[z++] = ConstType;
					magazin[z++] = type_const;
					magazin[z++] = type_case;
				}
				break;
			}

			case netermDefault: {
				if (t == type_default) {
					magazin[z++] = type_tzap;
					magazin[z++] = netermOperators;
					magazin[z++] = type_dvd;
					magazin[z++] = type_default;
				}
				break;
			}

			case netermOperators: {
				if (t == type_int || t == type_float || t == type_ident || t == type_break) {
					magazin[z++] = netermOperators;
					magazin[z++] = netermOpertor;
				}
				break;
			}

			case netermExpression1: {
				magazin[z++] = netermExpression11;
				magazin[z++] = netermExpression2;
				break;
			}

			case netermExpression11: {
				if (t == type_comp) {
					magazin[z++] = netermExpression11;
					//���������� �����
					magazin[z++] = CastVar;
					magazin[z++] = netermExpression2;
					magazin[z++] = type_comp;
				}
				else if (t == type_ncomp) {
					magazin[z++] = netermExpression11;
					//���������� �����
					magazin[z++] = CastVar;
					magazin[z++] = netermExpression2;
					magazin[z++] = type_ncomp;
				}
				else if (t == type_rsk || t == type_tzap || t == type_zap) {

				}
				else
					sc->PrintError("�������� ������ ", l);
				break;
			}

			case netermExpression2: {
				magazin[z++] = netermExpression22;
				magazin[z++] = netermExpression3;
				break;
			}

			case netermExpression22: {

				if (t == type_gt) {
					magazin[z++] = netermExpression22;
					//���������� �����
					magazin[z++] = CastVar;
					magazin[z++] = netermExpression3;
					magazin[z++] = type_gt;
				}
				else if (t == type_gtcomp) {
					magazin[z++] = netermExpression22;
					//���������� �����
					magazin[z++] = CastVar;
					magazin[z++] = netermExpression3;
					magazin[z++] = type_gtcomp;
				}
				else if (t == type_lt) {
					magazin[z++] = netermExpression22;
					//���������� �����
					magazin[z++] = CastVar;
					magazin[z++] = netermExpression3;
					magazin[z++] = type_lt;
				}
				else if (t == type_ltcomp) {
					magazin[z++] = netermExpression22;
					//���������� �����
					magazin[z++] = CastVar;
					magazin[z++] = netermExpression3;
					magazin[z++] = type_ltcomp;
				}
				else if (t == type_rsk || t == type_tzap || t == type_zap) {
				}
				else
					sc->PrintError("�������� ������, �������� >= > < <= ", l);
				break;
			}

			case netermExpression3: {
				magazin[z++] = netermExpression33;
				magazin[z++] = netermExpression4;
				break;
			}

			case netermExpression33: {
				if (t == type_plus) {
					magazin[z++] = netermExpression33;
					//���������� �����
					magazin[z++] = CastVar;
					magazin[z++] = netermExpression4;
					magazin[z++] = type_plus;
				}
				else if (t == type_minus) {
					magazin[z++] = netermExpression33;
					//���������� �����
					magazin[z++] = CastVar;
					magazin[z++] = netermExpression4;
					magazin[z++] = type_minus;
				}
				else if (t == type_rsk || t == type_tzap || t == type_zap || t == type_lt || t == type_gt || t == type_ltcomp || t == type_gtcomp) {
				}
				else
					sc->PrintError("�������� ������, �������� + - ", l);
				break;
			}

			case netermExpression4: {
				magazin[z++] = netermExpression44;
				magazin[z++] = netermExpression5;
				break;
			}

			case netermExpression44: {
				if (t == type_umg) {
					magazin[z++] = netermExpression44;
					//���������� �����
					magazin[z++] = CastVar;
					magazin[z++] = netermExpression5;
					magazin[z++] = type_umg;
				}
				else if (t == type_razd) {
					magazin[z++] = netermExpression44;
					//���������� �����
					magazin[z++] = CastVar;
					magazin[z++] = netermExpression5;
					magazin[z++] = type_razd;
				}
				else if (t == type_rsk || t == type_tzap || t == type_zap || t == type_plus || t == type_minus) {
				}
				else
					sc->PrintError("�������� ������, �������� * / ", l);
				break;
			}

			case netermExpression5: {
				if (t == type_dplus) {
					//�������� �� ����������� �������� � �����������
					magazin[z++] = CheckUnOperation;
					magazin[z++] = netermExpression6;
					magazin[z++] = type_dplus;
				}
				else if (t == type_dminus) {
					//�������� �� ����������� �������� � �����������
					magazin[z++] = CheckUnOperation;
					magazin[z++] = netermExpression6;
					magazin[z++] = type_dminus;
				}
				else {
					magazin[z++] = netermExpression55;
					magazin[z++] = netermExpression6;
				}
				break;
			}

			case netermExpression55: {
				if (t == type_dplus) {
					//�������� �� ����������� �������� � �����������
					magazin[z++] = CheckUnOperation;
					magazin[z++] = type_dplus;
				}
				else if (t == type_dminus) {
					//�������� �� ����������� �������� � �����������
					magazin[z++] = CheckUnOperation;
					magazin[z++] = type_dminus;
				}
				else if (t == type_rsk || t == type_tzap || t == type_zap || t == type_plus || t == type_minus || t == type_umg || t == type_dvd) {
				}
				else
					sc->PrintError("�������� ������. ��������� �������������� � �������� ��������� ", l);
				break;
			}

			case netermExpression6: {
				if (t == type_ident) {
					magazin[z++] = netermCallFunction;
					magazin[z++] = type_ident;
				}
				else if (t == type_const) {
					//����������� ���� ���������
					magazin[z++] = ConstType;
					magazin[z++] = type_const;
				}
				else if (t == type_const_float) {
					//����������� ���� ���������
					magazin[z++] = ConstType;
					magazin[z++] = type_const_float;
				}
				else if (t == type_lsk) {
					magazin[z++] = type_rsk;
					magazin[z++] = netermExpression1;
					magazin[z++] = type_lsk;
				}
				else
					sc->PrintError("�������� ������, ��������� ���������, �������������, (", l);
				break;
			}

			case netermCallFunction: {
				if (t == type_lsk) {
					magazin[z++] = WorkWithFunc;
					magazin[z++] = type_rsk;
					magazin[z++] = type_lsk;
				}
				else {
					magazin[z++] = FindVar;
				}
				break;
			}
			}
			z--;
		}
	}
	printf("// !----- ����� ������ ----- //\n");
	root->Print();
	printf("// !----- ����� ������ ������ ----- //\n");

}




bool LL_K_::isTerminal(int t) {
	return t < netermProgram && t > 0;
}

bool LL_K_::isDelta(int t) {
	return t >= IncludeFunc && t <= WorkWithFunc;
}

void LL_K_::workWithDelta(int t) {
	switch (t) {

	case IncludeFunc: {
		Tree* v = root->SemInclude(currentId, TYPE_FUNCT, currentType, sc);
		nodesFunc[nf++] = v;
		root->setCur(v->getCur());
		break;
	}
	case IncludeVar: {
		Tree* v = NULL;
		if (currentType == type_int)
			v = root->SemInclude(currentId, TYPE_INTEGER, currentType, sc);
		else if (currentType == type_float)
			v = root->SemInclude(currentId, TYPE_FLOAT, currentType, sc);
		else v = root->SemInclude(currentId, TYPE_UNKNOWN, currentType, sc);
		break;
	}
	case EndIncludeFunc: {
		root->setCur(nodesFunc[--nf]);
		break;
	}

	case FindVar: {
		Tree* v = root->SemGetType(currentId);
		if (v != NULL) {
			types[typez++] = v->getNode()->typeNode;
		}
		break;
	}

	case StartNewLevel: {
		nodesFunc[nf++] = root->getCur();
		root->semAddBlock();
		break;
	}

	case RetFromLevel: {
		root->setCur(nodesFunc[--nf]);
		break;
	}

	case StartFlagData: {
		flagData = true;
		break;
	}

	case EndFlagData: {
		flagData = false;
	}

	case CastVar: {
		if (typez < 2) {
			return;
		}
		int second = types[--typez];
		int first = types[--typez];
		if (second > first) {
			sc->PrintWarningTypes(first, second, smallType);
		}
		break;
	}

	case CheckUnOperation: {
		if (wasConst) {
			sc->PrintError("������� ��������� ��������� ++ ��� -- � ���������", currentId);
		}
		break;
	}

	case CheckReturn: {
		Node* n;
		int i = nf - 1;
		do {
			n = nodesFunc[i--]->getNode();
		} while (n->DataType != TYPE_FUNCT && i >= 0);

		if (n->DataType != TYPE_FUNCT)
			sc->PrintError("������� �� ������� ", currentId);
		int func, expression;
		func = n->typeNode;
		expression = types[--typez];
		if (expression < func) {
			sc->PrintWarningTypes(expression, func, returnType);
		}
		break;
	}

	case WorkWithFunc: {
		Tree* v = root->SemGetFunct(currentId);
		if (v != nullptr) {
			types[typez++] = v->getNode()->typeNode;
		}
		break;
	}

	case ConstType: {
		if (currentConstType != type_const && currentConstType != type_const_float)
			sc->PrintError("������, ��������� �� ������� ", currentConst);
		if (currentConstType == type_const)
			types[typez++] = type_int;
		else if (currentConstType == type_float)
			types[typez++] = type_float;
	}
	
	}

}