#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include "defs.h"
#include "Scaner.h"
#include <iostream>

TScaner::TScaner(const char* FileName) {
	GetData(FileName);
	PutUK(0);
	numStr = 1;
	numCh = 0;
}

TypeLex KeyWord[MAX_KEYW] = { "float", "__int64", "case",
								"switch", "break", "default",
								"return", "if" };

int IndexKeyword[MAX_KEYW] = { type_float, type_int, type_case,
								type_switch, type_break, type_default,
								type_return, type_if
};

void TScaner::PutUK(int i) {
	numStr = oldnumStr;
	numCh = oldnumCh;
	uk = i;
}
int TScaner::GetUK(void) {
	oldnumStr = numStr;
	oldnumCh = numCh;
	return uk;
}

void TScaner::PutUK(int i, int row, int line) {
	uk = i;
	numStr = line;
	numCh = row;
}

void TScaner::GetUK(int &i, int &row, int &line) {
	line = oldnumStr;
	row = oldnumCh;
	i = uk;
}

void TScaner::PrintError(const char* err, const char* a) {
	printf("Номер строки: %d Номер позиции: %d\n", numStr, numCh);
	if (a[0] == '\n') {
		printf("Ошибка :  %s %s\n", err, a);
		exit(1);
	}
	else {
		printf("Ошибка : %s. Неверный символ %s\n", err, a);
		exit(1);
	}
}

void TScaner::PrintWarning(const char* err, const char* a) {
	printf("Номер строки: %d Номер позиции: %d\n", numStr, numCh);
		printf("Предупреждение : %s. Неверный символ %s\n", err, a);
}

void TScaner::PrintWarningTypes(int type1, int type2, int typeWarning) {
	switch (typeWarning) {
	case privedenieTypes: {
		std::cout << "Предупреждение! Строка " << numStr << ", позиция " << numCh << ". Приведение типа " << TypeDataToString(type1) << " к типу " << TypeDataToString(type2);
		break;
	}
	case returnType: {
		std::cout << "Предупреждение! Строка " << numStr << ", позиция " << numCh << ". Приведение типа "<< TypeDataToString(type1) << " функции и типа возвращаемого значения " << TypeDataToString(type2) << "\n";
		break;
	}
	case smallType: {
		std::cout << "Предупреждение! Строка " << numStr << ", позиция " << numCh << ". Приведение типа " << TypeDataToString(type1) << " к типу " << TypeDataToString(type2) << ".Возможна потеря данных\n";
		break;
	}
	}
}

int TScaner::Scaner(TypeLex l) {
	int i;
	for (i = 0; i < MAX_LEX; i++)
		l[i] = 0;
	i = 0;
start:
	while ((t[uk] == ' ') || (t[uk] == '\n' || t[uk] == '\t')) {
		if (t[uk] == '\n') {
			numStr++;
			numCh = 0;
		}
		else
			numCh++;
		uk++;
	}
	if ((t[uk] == '/' && t[uk + 1] == '/'))
	{
		uk = uk + 2;
		while ((t[uk] != '\n') && (t[uk] != '#')) {
			uk++;
		}
		if (t[uk] == '\n')
			numCh = 0;
		goto start;
	}
	if (t[uk] == '\0')
	{
		l[0] = '#';
		return type_end;
	}
	if ((t[uk] <= '9') && (t[uk] >= '0'))
	{
		l[i++] = t[uk++];
		numCh++;
		while ((t[uk] <= '9') && (t[uk] >= '0'))
			if (i < MAX_LEX - 1)
			{
				numCh++;
				l[i++] = t[uk++];
			}
			else {
				uk++;
				numCh++;
			}
		if (i >= MAX_LENGH_CH - 1) {
			PrintError("Длинная константа: ", l);
			return type_error;
		}
		if (t[uk] == '.')
		{
			l[i++] = t[uk++];
			numCh++;
			goto N1;
		}
		if ((t[uk] == 'E') || (t[uk] == 'e'))
		{
			numCh++;
			l[i++] = t[uk++];
			goto N2;
		}
		return type_const;
	}
	else
		if ((t[uk] >= 'a') && (t[uk] <= 'z') ||
			(t[uk] >= 'A') && (t[uk] <= 'Z') || (t[uk] == '_'))
		{
			numCh++;
			l[i++] = t[uk++];
			while ((t[uk] <= '9') && (t[uk] >= '0') ||
				(t[uk] >= 'a') && (t[uk] <= 'z') ||
				(t[uk] >= 'A') && (t[uk] <= 'Z') || (t[uk] == '_'))
				if (i < MAX_LEX - 1) {
					l[i++] = t[uk++];
					numCh++;
				}
				else {
					uk++;
					numCh++;
				}
			int j;
			for (j = 0; j < MAX_KEYW; j++) {
				if (strcmp(l, KeyWord[j]) == 0) return IndexKeyword[j];
			}
			return type_ident;
		}
		else if (t[uk] == '.')
		{
			numCh++;
			l[i++] = t[uk++];
			if ((t[uk] <= '9') && (t[uk] >= '0')) {
				l[i++] = t[uk++];
				numCh++;
				goto N1;
			}
			return type_toch;
		}
		else if (t[uk] == '\"')
		{
			uk++;
			numCh++;
			while ((t[uk] != '\"') && (t[uk] != '#') && (t[uk] != '\n'))
			{
				if (i < MAX_LEX - 1) {
					l[i++] = t[uk++];
					numCh++;
				}
				else {
					uk++;
					numCh++;
				}
			}
			if (t[uk] != '\"')
			{
				PrintError("Неверная символьная константа", l);
				return type_error;
			}
			numCh++;
			uk++;
			return type_const_ch;
		}
		else if (t[uk] == ',') {
			numCh++;
			l[i++] = t[uk++];
			return type_zap;
		}
		else if (t[uk] == ';') {
			l[i++] = t[uk++];
			numCh++;
			return type_tzap;
		}
		else if (t[uk] == '(') {
			l[i++] = t[uk++];
			numCh++;
			return type_lsk;
		}
		else if (t[uk] == '[') {
			l[i++] = t[uk++];
			numCh++;
			return type_lksk;
		}
		else if (t[uk] == ']') {
			l[i++] = t[uk++];
			numCh++;
			return type_pksk;
		}
		else if (t[uk] == ')') {
			l[i++] = t[uk++];
			numCh++;
			return type_rsk;
		}
		else if (t[uk] == '{') {
			l[i++] = t[uk++];
			numCh++;
			return type_lfsk;
		}
		else if (t[uk] == '}') {
			l[i++] = t[uk++];
			numCh++;
			return type_rfsk;
		}
		else if (t[uk] == '+') {
			l[i++] = t[uk++];
			numCh++;
			if (t[uk] == '+') {
				l[i++] = t[uk++];
				numCh++;
				return type_dplus;
			}
			return type_plus;
		}
		else if (t[uk] == '-') {
			numCh++;
			l[i++] = t[uk++];
			return type_minus;
		}
		else if (t[uk] == '/') {
			numCh++;
			l[i++] = t[uk++];
			return type_razd;
		}
		else if (t[uk] == '*') {
			numCh++;
			l[i++] = t[uk++];
			return type_umg;
		}
		else if (t[uk] == ':') {
			numCh++;
			l[i++] = t[uk++];
			return type_dvd;
		}
		else if (t[uk] == '<') {
			numCh++;
			l[i++] = t[uk++];
			if (t[uk] == '=') {
				numCh++;
				l[i++] = t[uk++];
				return type_ltcomp;
			}
			return type_lt;
		}
		else if (t[uk] == '>') {
			l[i++] == t[uk++];
			numCh++;
			if (t[uk] == '=') {
				l[i++] = t[uk++];
				numCh++;
				return type_gtcomp;
			}
			return type_gt;
		}
		else if (t[uk] == '!') {
			l[i++] = t[uk++];
			numCh++;
			if (t[uk] == '=') {
				l[i++] = t[uk++];
				numCh++;
				return type_ncomp;
			}
			else {
				PrintError("Неверный символ", l);
				return type_error;
			}
		}
		else if (t[uk] == '=') {
			l[i++] = t[uk++];
			numCh++;
			if (t[uk] == '=') {
				l[i++] = t[uk++];
				numCh++;
				return type_comp;
			}
			else return type_equal;
		}
		else {
			PrintError("Неверный символ", l);
			uk++;
			numCh++;
			return type_error;
		}

N1:
	while ((t[uk] <= '9') && (t[uk] >= '0')) {

		if (i < MAX_LENGH_CH - 1) {
			l[i++] = t[uk++];
			numCh++;
		}
		else {
			uk++;
			numCh++;
		}
	}

	if (i >= MAX_LENGH_CH - 1) {
		PrintError("Длинная константа: ", l);
		return type_error;
	}
	if ((t[uk] == 'e') || (t[uk] == 'E')) {
		l[i++] = t[uk++];
		numCh++;
		goto N2;
	}
	return type_const_float;
N2:
	if ((t[uk] == '+') || (t[uk] == '-')) {
		l[i++] = t[uk++];
		numCh++;
		if ((t[uk] <= '9') && (t[uk] >= '0')) {
			if (i < MAX_LEX - 1) {
				l[i++] = t[uk++];
				numCh++;
			}
			else {
				uk++; numCh++;
			}
			goto N3;
		}
		else {
			PrintError("Неверная константа", l);
			return type_error;
		}
	}
N3:
	while ((t[uk] < ' 9') && (t[uk] >= '0')) {
		if (i < MAX_LEX - 1) {
			l[i++] = t[uk++]; numCh++;
		}
		else { uk++; numCh++; }
	}
	return type_const_exp;
}

void TScaner::GetData(const char* FileName) {
	char aa;
	FILE* in = fopen(FileName, "r");
	if (in == NULL) {
		PrintError("Отсутствует входной файл", "");
		exit(1);
	}
	int i = 0;
	while (!feof(in)) {
		fscanf(in, "%c", &aa);
		if (!feof(in))
			t[i++] = aa;
		if (i >= MAX_TEXT - 1) {
			PrintError("Слишком большой размер исходного файла", "");
			break;
		}
	}
	t[i] = '\0';
	fclose(in);
}