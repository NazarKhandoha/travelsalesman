#include<iostream>
#include<stdio.h>
#include<conio.h>
using namespace std;
//Директиви визначення кількості 
#define ALL -1//зменшує кількість міст на одиницю
#define MAXCITIES 10//визначає к-сть міст 
//Опис змінних
enum BOOL{ FALSE, TRUE };
long*visited;//проходи по містах
long*min_circuit;//мінімальний контур
long*ham_circuit;//гамільтонів контур
long min_circuit_length;//мінімальна довжина контуру

int n;//зманна для циклів
long matrix[MAXCITIES][MAXCITIES];//матриця відстаней
long INFI;// керуююча змінна

//Опис функцій
void reset_min_circuit(int s_v_id)//ф-ція визначення мінімального контуру
{
	min_circuit[0] = s_v_id;//присвоєння
	for (int i = 1; i<n; i++)
		min_circuit[i] = -1;
}

void set_visited(int v_id, BOOL flag)//ф-ція проходів по містах
{
	if (v_id == ALL)
		for (int i = 0; i<n; i++)
			visited[i] = flag;
	else
		visited[v_id] = flag;
}

void SET_HAM_CKT(long pl)//ф-ція отримання гамільтонівого контуру
{
	ham_circuit[0] = pl;//присвоєння
	for (int i = 0; i<n; i++)
		ham_circuit[i + 1] = min_circuit[i];//переприсвоєння
	ham_circuit[n + 1] = min_circuit[0];
}

long get_valid_circuit(int s_v, int s_n_v)//ф-ція перерахунку контурів
{
	int next_v, min, v_count = 1;//присвоєння
	long path_length = 0;//присвоєння
	min_circuit[0] = s_v;//присвоєння
	min_circuit[1] = s_n_v;//присвоєння
	set_visited(s_n_v, TRUE);//виклик араередньої функції
	path_length += matrix[s_v][s_n_v];//нарощуємо
	for (int V = s_n_v; v_count<n - 1; v_count++)//цикл знаходження мінімального гамільтонівого контуру
	{
		min = INFI;
		for (int i = 0; i<n; i++)
			if (matrix[V][i]<INFI && !visited[i]
				&& matrix[V][i] <= min
				)
				min = matrix[V][next_v = i];
		set_visited(next_v, TRUE);//виклик ф-ції проходів 
		V = min_circuit[v_count + 1] = next_v;
		path_length += min;
	}
	path_length += matrix[min_circuit[n - 1]][s_v];
	return(path_length);
}

void main()//головна ф-ція
{
	setlocale(0, "UKR");
	INFI = 999;//присвоєння
	int pathcount, i, j, source, dest;//присвоєння
	long dist = 0;//присвоєння
	long new_circuit_length = INFI;//присвоєння
	printf("Введiть кiлькiсть мiст ", MAXCITIES);//вивід на консоль
	scanf("%d", &n);//зчитування
	printf("Введiть кiлькiсть шляхiв: ");//вивід на консоль
	scanf("%d", &pathcount);//зчитування
	printf("Як їхатимемо?:\n");//зчитування
	printf("Введiть початковий пункт, кiнцевий пункт, вiдстань:\n");//вивід на консоль

	for (i = 0; i<n; i++)//цикл пребору 
		for (j = 0; j<n; j++)
			matrix[i][j] = INFI;


	for (i = 0; i<pathcount; i++)//цикл перборушляхів
	{
		printf("[Шлях %d]:", i + 1);//вивід на консоль
		printf("\n");//вивід на консоль
		scanf("%d %d %ld", &source, &dest, &dist);
		if (source != dest)//умова
			matrix[source][dest] = matrix[dest][source] = dist;
	}

	visited = new long[n];//виділення памяті під проходи
	min_circuit = new long[n];///виділення памяті під мінімальні контури 
	ham_circuit = new long[n + 2];//виділення памяті під гамільтонові контури
	min_circuit_length = INFI;//переприсвоєння

	for (int S_V_id = 0; S_V_id<n; S_V_id++)//цикл для контурів
	{
		for (i = 0; i<n; i++)
		{
			set_visited(ALL, FALSE);

			set_visited(S_V_id, TRUE);

			reset_min_circuit(S_V_id);

			new_circuit_length = get_valid_circuit(S_V_id, i);

			if (new_circuit_length <= min_circuit_length)
				SET_HAM_CKT(min_circuit_length = new_circuit_length);
		}
	}

	if (min_circuit_length<INFI)//умова мінімальної довжини контура
	{
		printf("\n\nМiнiмальний цикл довжиною: %ld\nCikl:\n", min_circuit_length);//вивід на консоль
		for (i = 1; i<n + 2; i++)	printf("<%ld> ", ham_circuit[i]);
	}
	else	printf("\n\nЦе не гамiльтоновий цикл!Спробуйте ще");//вивід на консоль
	getch();
	delete[]visited;//очищення памяті
	delete[]min_circuit;//очищення памяті
	delete[]ham_circuit;//очищення памяті
}


