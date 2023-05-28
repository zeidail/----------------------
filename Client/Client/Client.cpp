#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include "Header.h"
struct kvartiri {         //Структура вводимых значений.
	int plkv;            //площадь квартиры
	int kolchel;        // количество человек в квартире
};
struct imyaresa {     //Структура вводимых значений.
	char imres[6];   // название ресурса
	int oplata;     // деньги за ресурс
	int k;         // ????
};
struct dom {       //Структура вводимых значений.
	int ch;       // название ресурса
	int god;     // деньги за ресурс
	int mass[7];// использованные ресы
};
struct pokkv {     //Структура вводимых значений.
	int chi;      // название ресурса
	int godd;    // деньги за ресурс
	int kvnom;  // номер квартиры
	int mas[7];// использованные ресы
};
struct MMM {     //Структура вводимых значений.
	int MM[200];// 
};
void sort(struct dom* ptr, int n) // // Функция sort сортирует структуры по году и числу
{
	struct dom abc;
	for (int t = 0; t <= n; ++t) {
		for (int j = 0; j < n - 1; ++j) {
			if (ptr[j].god > ptr[j + 1].god)
			{
				abc = ptr[j + 1];
				ptr[j + 1] = ptr[j];
				ptr[j] = abc;
			}
			else
			{
				if ((ptr[j].god == ptr[j + 1].god) && (ptr[j].ch > ptr[j + 1].ch))
				{
					abc = ptr[j + 1];
					ptr[j + 1] = ptr[j];
					ptr[j] = abc;
				}
			}

		}
	}
	return;
}
void sort2(struct pokkv* ptr, int n) // Функция sort сортирует структуры по году и числу и 
{
	struct pokkv abc;
	for (int t = 0; t <= n; ++t) {
		for (int j = 0; j < n - 1; ++j) {
			if (ptr[j].godd > ptr[j + 1].godd)
			{
				abc = ptr[j + 1];
				ptr[j + 1] = ptr[j];
				ptr[j] = abc;
			}
			else
			{
				if ((ptr[j].godd == ptr[j + 1].godd) && (ptr[j].chi > ptr[j + 1].chi))
				{
					abc = ptr[j + 1];
					ptr[j + 1] = ptr[j];
					ptr[j] = abc;
				}
			}

		}
	}
	for (int t = 0; t <= n; ++t) {
		for (int j = 0; j < n - 1; ++j) {
			if (ptr[j].kvnom > ptr[j + 1].kvnom)
			{
				abc = ptr[j + 1];
				ptr[j + 1] = ptr[j];
				ptr[j] = abc;
			}
		}
	}
	return;
}
int main() {
	int kolkv, obshS;                      // количество квартир общая площадь	
	FILE* f;
	f = fopen("home.txt", "rt");
	fscanf(f, "%d %d", &kolkv, &obshS);
	struct kvartiri* p_var = NULL;
	p_var = (struct kvartiri*)calloc(kolkv, sizeof(struct kvartiri));
	for (int i = 0; i < kolkv; ++i)
	{
		fscanf(f, "%d %d", &p_var[i].plkv, &p_var[i].kolchel);
	}
	fclose(f);
	int kolres;                           // количество ресурсов
	FILE* ff;
	ff = fopen("takes.txt", "rt");
	fscanf(ff, "%d ", &kolres);
	struct imyaresa* p_vr = NULL;
	p_vr = (struct imyaresa*)calloc(kolkv, sizeof(struct imyaresa));
	for (int i = 0; i < kolres; ++i)
	{
		fscanf(ff, "%s %d %d", p_vr[i].imres, &p_vr[i].oplata, &p_vr[i].k);
	}
	fclose(f);
	int kolpok, kolpokkv;//количество домовых показаний количество показаний квартир
	FILE* fi;
	fi = fopen("details.txt", "rt");
	fscanf(fi, "%d ", &kolpok);
	struct dom* pvr = NULL;
	pvr = (struct dom*)calloc(kolpok, sizeof(struct dom));
	for (int i = 0; i < kolpok; ++i)
	{
		fscanf(fi, "%d.%d", &pvr[i].ch, &pvr[i].god);
		for (int j = 0; j < kolres; ++j)
		{
			fscanf(fi, "%d", &pvr[i].mass[j]);
		}
	}
	fscanf(fi, "%d ", &kolpokkv);
	struct pokkv* pr = NULL;
	pr = (struct pokkv*)calloc(kolpokkv, sizeof(struct pokkv));
	for (int i = 0; i < kolpokkv; ++i)
	{
		fscanf(fi, "%d.%d %d", &pr[i].chi, &pr[i].godd, &pr[i].kvnom);
		for (int j = 0; j < kolres; ++j)
		{
			fscanf(fi, "%d", &pr[i].mas[j]);
		}
	}
	sort(pvr, kolpok);// функция сортировки. 
	sort2(pr, kolpokkv);
	int flat, nm, km, ng, kg;//номер квартиры,  нач месяц ,кон месяц, нач год, кон год
	char trres[6];//требуемый ресурс
	FILE* fil;
	fil = fopen("input.txt", "rt");
	fscanf(fil, "%d %s %d.%d-%d.%d", &flat, trres, &nm, &ng, &km, &kg);
	fclose(fil);
	int SumExpFlat = 0, SumCostFlat = 0, SumExpODN = 0, SumCostODN = 0;
	/*SumExpFlat – суммарное потребление заданного в запросе ресурса в указанной квартире(на
		основании показаний ИПУ) за отчетный период, целое число;
	SumCostFlat – суммарное начисление за потребленный ресурс указанной квартирой за
		отчетный период, целое число;
	SumExpODN – суммарное потребление заданного в запросе ресурса, относящееся на ОДН
		для указанной квартиры за отчетный период, целое число;
	SumCostODN – суммарное начисление за ОДН по данному ресурсу указанной квартире за
		отчетный период, целое число
	W – количество отчетных периодов,
		попадающих в отрезок[StartMonth.StartYear…EndMonth.EndYear].
		четный период в интервале между StartMonth.StartYear и EndMonth.EndYear
в формате MM.YYYY;
ExpFlat – потребление заданного в запросе ресурса в указанной квартире (на основании
показаний ИПУ) за месяц Month.Year, целое число;
CostFlat – начисление за потребленный ресурс указанной квартирой за месяц Month.Year,
целое число;
ExpODN – суммарное потребление заданного в запросе ресурса, относящееся на ОДН для
указанной квартиры за месяц Month.Year, целое число (округление вниз);
SumCostODN – начисление за ОДН по данному ресурсу указанной квартире за месяц
Month.Year, целое число.
Строки должны быть упорядочены по возрастанию даты Month.Year.*/
	int per;// номер реса
	for (int i = 0; i < kolres; i++)
	{
		if (strcmp(trres, p_vr[i].imres) == 0)
			per = i;
	}
	for (int i = 0; i < kolpokkv; i++)
	{
		int yyy=1;
		if ((kg == ng))
		{
			if  ((pr[i].chi >= nm) && (pr[i].chi <= km)) yyy = 1;
		else yyy = 0;
		}
		if ((pr[i].kvnom == flat) && (((pr[i].chi >= nm) && (pr[i].godd >= ng) && (pr[i].godd <= kg)) || ((pr[i].chi <= km) && (pr[i].godd >= ng) && (pr[i].godd <= kg))) && (yyy != 0))
		{
			if ((pr[i].chi == 9) && (pr[i].godd == 2021))
			{
				SumExpFlat += 0;
			}
			else
			{
				SumExpFlat += (pr[i].mas[per]);
				if ((i > 0) && (pr[i - 1].kvnom == flat))
					SumExpFlat -= (pr[i - 1].mas[per]);
			}
		}
	}
	tppoint p1,p3;
	p1.x = SumExpFlat;
	p1.y = p_vr[per].oplata;
	p3 = umnpoint(&p1);
	SumCostFlat = p3.x;
	struct MMM* pm = NULL;
	pm = (struct MMM*)calloc(kolkv, sizeof(struct MMM));
	int g = 0;
	for (int i = 0; i < kolkv; i++)
	{
		int k = 0; int vrkv = i + 1;
		for (int j = 0; j < kolpokkv; j++)
		{
			int yyy = 1;
			if ((kg == ng))
			{
				if ((pr[j].chi >= nm) && (pr[j].chi <= km)) yyy = 1;
				else yyy = 0;
			}
			if ((pr[j].kvnom == flat) && (((pr[j].chi >= nm) && (pr[j].godd >= ng) && (pr[j].godd <= kg)) || ((pr[j].chi <= km) && (pr[j].godd >= ng) && (pr[j].godd <= kg))) && (yyy == 1))
			{
				if ((pr[j].chi == 9) && (pr[j].godd == 2021))
				{
					pm[i].MM[k] = 0;
				}
				else
				{
					pm[i].MM[k] = (pr[j].mas[per]);
					if ( (pr[j - 1].kvnom == flat))
						pm[i].MM[k] -= (pr[j - 1].mas[per]);
					k++; if (k > g) g = k;
				}
			}
		}
	}
	int m[200];//сумма для одн квартир
	for (int j = 0; j < g; j++)
	{
		int vrsum = 0;
		for (int i = 0; i < kolkv; i++)
		{
			vrsum += pm[i].MM[j];
		}
		m[j] = vrsum;
	}
	int mi[200];//для одн
	for (int j = 0; j < kolpok; j++)
	{
		int yyy = 1;
		if ((kg == ng))
		{
			if ((pr[j].chi >= nm) && (pr[j].chi <= km)) yyy = 1;
			else yyy = 0;
		}

		if (((pvr[j].ch >= nm) && (pvr[j].god >= ng) && (pvr[j].god <= kg)) || ((pvr[j].ch <= km) && (pvr[j].god >= ng) && (pvr[j].god <= kg)) && (yyy == 1))
		{
			mi[j] = pvr[j].mass[per] - pvr[j - 1].mass[per];

		}
		if ((pr[j].chi == 9) && (pr[j].godd == 2021))  mi[j] = 0;
	}
	poi p, pp;
	p.x = kolkv;
	p.y = flat;
	for (int i = 0; i < kolkv; i++)
	{
		p.z[i] = p_var[i].plkv;
	}
	pp = ciklpoint(&p);
	int flatS;
	flatS = pp.g;
	int dopsumLUDI=0;
	for (int j = 0; j < kolkv; j++)
	{
		dopsumLUDI += p_var[j].kolchel;
	}
	int dopludi=0;
	for (int j = 0; j < kolkv; j++)
	{
		if ((j == ( flat-1)))  dopludi =p_var[j].kolchel;
	}
	
	
	int sumexp[200];
	if (p_vr[per].k == 0)
	{
		for (int j = 0; j < g; j++)
		{

			SumExpODN += floor((mi[j + 1] - m[j]) * flatS / obshS);
			sumexp[j] = floor((mi[j + 1] - m[j]) * flatS / obshS);
		}
	}
	else
	{
		for (int j = 0; j < g; j++)
		{

			SumExpODN += floor((mi[j + 1] - m[j]) * dopludi / dopsumLUDI);
			sumexp[j] = floor((mi[j + 1] - m[j]) * dopludi / dopsumLUDI);
		}
	}

	p1.x = SumExpODN;
	p1.y = p_vr[per].oplata;
	p3 = umnpoint(&p1);
	SumCostODN = p3.x;
	int  ip = 0;
	FILE* FFF;
	FFF = fopen("output.txt", "w");
	fprintf(FFF, "%d ", SumExpFlat);
	fprintf(FFF, "%d ", SumCostFlat);
	fprintf(FFF, "%d ", SumExpODN);
	fprintf(FFF, "%d \n", SumCostODN);
	
	for (int i = 0; i < kolpokkv; i++)
	{
		int yyy = 1;
		if ((kg == ng))
		{
			if ((pr[i].chi >= nm) && (pr[i].chi <= km)) yyy = 1;
			else yyy = 0;
		}
		int sss = 0;
		if ((pr[i].kvnom == flat) && (((pr[i].chi >= nm) && (pr[i].godd >= ng) && (pr[i].godd <= kg)) || ((pr[i].chi <= km) && (pr[i].godd >= ng) && (pr[i].godd <= kg)))&&(yyy==1))
		{
			fprintf(FFF, "%02d.%d ", pr[i].chi, pr[i].godd);
			if ((pr[i].chi == 9) && (pr[i].godd == 2021))
			{
				fprintf(FFF, "0 0 0 0\n");
			}
			else
			{
				if ( (pr[i - 1].kvnom == flat))
				{
					sss += (pr[i].mas[per]) - (pr[i - 1].mas[per]);
				}
				else sss += (pr[i].mas[per]);
				fprintf(FFF, "%d %d ", sss, sss * p_vr[per].oplata);
				fprintf(FFF, "%d %d \n", sumexp[ip], sumexp[ip] * p_vr[per].oplata);
				ip++;
			}
		}
	}
	return 0;
}
