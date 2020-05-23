#pragma once
#ifndef __DEFS
#define __DEFS
#include <stdio.h>
#include <stdlib.h>

#include <string>

#define MAX_TEXT 10000 //максимальная длина текста
#define MAX_LEX 100 //максимальная длина лексемы
#define MAX_KEYW 8 //число ключевых слов
#define MAX_LENGH_CH 10
#define MAX_MAG 1000 // Максимальный размер магазина


typedef char TypeLex[MAX_LEX];
typedef char TypeMod[MAX_TEXT];

#define tInt 2
#define tFloat 35

#define type_float 1
#define type_int 2
#define type_case 3
#define type_switch 4
#define type_break 5
#define type_default 6
#define type_return 7
#define type_if 8
#define type_ident 9
#define type_equal 10
#define type_comp 11
#define type_ncomp 12
#define type_lt 13
#define type_ltcomp 14
#define type_gt 15
#define type_gtcomp 16
#define type_plus 17
#define type_minus 18
#define type_dvd 35
#define type_razd 19
#define type_umg 20
#define type_dplus 21
#define type_dminus 22
#define type_tzap 23
#define type_zap 24
#define type_lsk 25
#define type_rsk 26
#define type_lfsk 27
#define type_rfsk 28
#define type_const 29
#define type_const_float 50
#define type_const_str 40
#define type_const_ch 30
#define type_const_exp 31
#define type_const_exp1 32
#define type_toch 33
#define type_lksk 34
#define type_pksk 35

#define type_error 100 
#define type_end 200

//-----------Семантические подпрограммы-------

#define IncludeFunc 300
#define EndIncludeFunc 301
#define EndFlagData 302
#define StartFlagData 303
#define IncludeVar 304
#define StartNewLevel 305
#define RetFromLevel 306
#define CheckReturn 307
#define FindVar 308
#define CastVar 309
#define CheckUnOperation 310
#define ConstType 311
#define PushType 312
#define WorkWithFunc 313

//------------------Нетерминалы----------------
#define netermProgram 501
#define netermOpisanie 502
#define netermType 503
#define netermOpisanieDannix 504
#define netermListPerem 505
#define netermListPerem1 506
#define netermPrisvaivanie1 507
#define netermPrisvaivanie 508
#define netermSostOper 509
#define netermOperatorAndOpisanie 510
#define netermOpertor 511
#define netermSwitch 512
#define netermConstSwitch 513
#define netermIdentSwitch 514
#define netermSostOperForSwitch 515
#define netermCases 516
#define netermDefault 517
#define netermOperators 518
#define netermExpression1 519
#define netermExpression11 520
#define netermExpression2 521
#define netermExpression22 522
#define netermExpression3 523
#define netermExpression33 524
#define netermExpression4 525
#define netermExpression44 526
#define netermExpression5 527
#define netermExpression55 528
#define netermExpression6 529
#define netermCallFunction 530


//-------Виды предупреждений-------------
#define privedenieTypes 1001
#define returnType 1002
#define smallType 1003
std::string TypeDataToString(int);

#endif