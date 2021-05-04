#include <iostream>
#include <clocale>
#include "variables.h"

using namespace std;

bool CheckIsClosed(int A, int B) {
	if (A == B)
		return true;
	else
		return false;
}

void DrawTable(Table_District **D, Table_A *A, Table_B *B, int n, int m) {
	cout << "\nИсходное опорное решение:\n|----------------------------------------|" << endl;
	cout << "|      | b(j) | ";
	for (int i = 0; i < n; i++) {
		cout << B[i].id << " | ";
	}
	cout << "\n| a(i) |      | ";
	for (int i = 0; i < n; i++) {
		cout << B[i].AMT << " | ";
	}
	cout << "\n|----------------------------------------|" << endl;
	int u = 0;
	for (int i = 0; i < m; i++) {
		cout << A[i].id << " | " << A[i].AMT << " | ";
		for (int j = 0; j < n; j++) {
			if (!isnan(D[i][j].TOVAR_AMT))
				cout << "| " << D[i][j].TOVAR_AMT << " - " << D[i][j].RASXOD << " | ";
			else
				cout << "| NN - " << D[i][j].RASXOD << " | ";
		}
		cout << endl;
	}
	cout << "|----------------------------------------|" << endl;
}

bool CheckOptimal(Table_Alpha *TABLE_AL, int V_MASS, int INT_MAX_COUNT) {
	for (int i = 0; i < V_MASS; i++) {
		if (TABLE_AL[i].a < 0)
			INT_MAX_COUNT++;
	}
	if (INT_MAX_COUNT == V_MASS)
		return true;
	else
		return false;
}

void FindOptimal(Table_A *TABLE_A, Table_B *TABLE_B, Table_U *TABLE_U, Table_V *TABLE_V, Table_Alpha *TABLE_AL, Table_District **TABLE_DIST, int N, int M, int FULL_MASS, int V_MASS, int INT_OPTIMAL) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (!isnan(TABLE_DIST[i][j].TOVAR_AMT)) {
				INT_OPTIMAL = INT_OPTIMAL + (TABLE_DIST[i][j].TOVAR_AMT*TABLE_DIST[i][j].RASXOD);
			}
		}
	}

	//Находим потанцевалы занятых ячеек
	TABLE_V[0].V = 0.0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (!isnan(TABLE_DIST[j][i].TOVAR_AMT)) {
				if (isnan(TABLE_U[i].U)) {
					TABLE_U[i].U = TABLE_DIST[j][i].RASXOD + TABLE_V[j].V;
				}
				if (isnan(TABLE_V[j].V)) {
					TABLE_V[j].V = ((-1)*TABLE_DIST[j][i].RASXOD) + TABLE_U[i].U;
				}
			}
		}
	}

	//Находим потанцевалы свободных ячеек
	int count = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (isnan(TABLE_DIST[j][i].TOVAR_AMT)) {
				TABLE_AL[count].a = TABLE_U[i].U - TABLE_V[j].V - TABLE_DIST[j][i].RASXOD;
				TABLE_AL[count].i = i;
				TABLE_AL[count].j = j;
				count++;
			}
		}
	}

	//временный вывод
	cout << endl;
	for (int i = 0; i < FULL_MASS; i++) {
		if (!isnan(TABLE_U[i].U))
			cout << "U" << i + 1 << " = " << TABLE_U[i].U << ", ";
	}
	cout << endl;
	for (int i = 0; i < FULL_MASS; i++) {
		if (!isnan(TABLE_V[i].V))
			cout << "V" << i + 1 << " = " << TABLE_V[i].V << ", ";
	}
	cout << endl;
	for (int i = 0; i < ((N * M) - FULL_MASS); i++) {
		if (!isnan(TABLE_AL[i].a))
			cout << "Al" << i + 1 << " = " << TABLE_AL[i].a << " [" << TABLE_AL[i].i << ", " << TABLE_AL[i].j << "]" << endl;
	}

}

void FindMaximalNumber(Table_Alpha *TABLE_AL, int V_MASS, int *MAX_i, int *MAX_j) {
	double MAX = NULL;
	//MAX_i = MAX_j = NULL;
	for (int i = 0; i < V_MASS; i++) {
		if (TABLE_AL[i].a >= MAX) {
			MAX = TABLE_AL[i].a;
			*MAX_i = TABLE_AL[i].i;
			*MAX_j = TABLE_AL[i].j;
		}
	}
}

void LetsDoSomeWork(Table_A *TABLE_A, Table_B *TABLE_B, Table_District **TABLE_DIST, int N, int M) {
	int INT_OPTIMAL = NULL,
		INT_MAX_COUNT = NULL,
		FULL_MASS = M + N - 1, //Число занятых клеток
		EMPTY_MASS = NULL,
		V_MASS = (N * M) - FULL_MASS,
		MAX_i, MAX_j,
		i_FT, j_FT;

	i_FT = j_FT = MAX_i = MAX_j = NULL;

	bool isGoingUp;

	Table_A *TEMP_A = new Table_A[M];
	Table_B *TEMP_B = new Table_B[N];
	Table_U *TABLE_U = new Table_U[FULL_MASS];
	Table_V *TABLE_V = new Table_V[FULL_MASS];
	Table_Alpha *TABLE_AL = new Table_Alpha[V_MASS];

	for (int i = 0; i < M; i++) {
		TEMP_A[i].AMT = TABLE_A[i].AMT;
		TEMP_A[i].id = TABLE_A[i].id;
	}
	for (int i = 0; i < N; i++) {
		TEMP_B[i].AMT = TABLE_B[i].AMT;
		TEMP_B[i].id = TABLE_B[i].id;
	}
	
	//Нахождение первого опорного плана
	while (EMPTY_MASS < FULL_MASS) {
		bool isNotWorkedYet = true;
		if ((TEMP_A[j_FT].AMT > TEMP_B[i_FT].AMT || TEMP_A[j_FT].AMT == TEMP_B[i_FT].AMT) && isNotWorkedYet) {
			TABLE_DIST[j_FT][i_FT].TOVAR_AMT = TEMP_B[i_FT].AMT;
			TABLE_DIST[j_FT][i_FT].isUsed = true;
			TEMP_A[j_FT].AMT = TEMP_A[j_FT].AMT - TEMP_B[i_FT].AMT;
			TEMP_B[i_FT].AMT = TEMP_B[i_FT].AMT - TEMP_B[i_FT].AMT;
			EMPTY_MASS++;
			i_FT++;
			isNotWorkedYet = false;
		}
		if ((TEMP_A[j_FT].AMT < TEMP_B[i_FT].AMT) && isNotWorkedYet) {
			TABLE_DIST[j_FT][i_FT].TOVAR_AMT = TEMP_A[j_FT].AMT;
			TABLE_DIST[j_FT][i_FT].isUsed = true;
			TEMP_B[i_FT].AMT = TABLE_B[i_FT].AMT - TEMP_A[j_FT].AMT;
			TEMP_A[j_FT].AMT = TEMP_A[j_FT].AMT - TEMP_A[j_FT].AMT;
			EMPTY_MASS++;
			j_FT++;
			isNotWorkedYet = false;
		}
	}

	//Найдем оптимальный план транспортной задачи методом потенциалов
	FindOptimal(TABLE_A, TABLE_B, TABLE_U, TABLE_V, TABLE_AL, TABLE_DIST, N, M, FULL_MASS, V_MASS, INT_OPTIMAL);
	//проверка на оптимальность
	if (!CheckOptimal(TABLE_AL, V_MASS, INT_MAX_COUNT)) {
		int *i_ptr = &MAX_j,
			*j_ptr = &MAX_i;
		int count_h = NULL;
		FindMaximalNumber(TABLE_AL, V_MASS, i_ptr, j_ptr);
		TABLE_DIST[MAX_i][MAX_j].isPlus = true;
		TABLE_DIST[MAX_i][MAX_j].isUsed = true;

		DrawTable(TABLE_DIST, TABLE_A, TABLE_B, N, M);

	}
}

int main() {
	setlocale(0, "rus");
	cout << "Введите кол-во пунктов производcтва" << endl;
	cin >> M;
	cout << "Введите кол-во пунктов продажи" << endl;
	cin >> N;

	Table_A *TABLE_A = new Table_A[M];
	Table_B *TABLE_B = new Table_B[N];
	Table_District **TABLE_DIST = new Table_District*[M];
	for (int i = 0; i < N; i++)
		TABLE_DIST[i] = new Table_District[N];

	for (int i = 0; i < M; i++) {
		cout << "Введите расходы по перевозке товаров для A" << i + 1 << "строки по отношению к В1-В" << N << "столбцам:\t";
		for (int j = 0; j < N; j++) {
			cin >> TABLE_DIST[i][j].RASXOD;
			TABLE_DIST[i][j].TOVAR_AMT = NAN;
		}
	}
	for (int i = 0; i < M; i++) {
		cout << "Введите кол-во запасов продукции в А" << i + 1 << "складу:\t";
		cin >> TABLE_A[i].AMT;
		TABLE_A[i].id = i;
		SUMM_A = SUMM_A + TABLE_A[i].AMT;
	}
	for (int i = 0; i < N; i++) {
		cout << "Введите кол-во необходимой продукции в В" << i + 1 << "пункте:\t";
		cin >> TABLE_B[i].AMT;
		TABLE_B[i].id = i;
		SUMM_B = SUMM_B + TABLE_B[i].AMT;
	}

	DrawTable(TABLE_DIST, TABLE_A, TABLE_B, N, M);
	if (!CheckIsClosed(SUMM_A, SUMM_B))
		return -1;
	else {
		LetsDoSomeWork(TABLE_A, TABLE_B, TABLE_DIST, N, M);
		DrawTable(TABLE_DIST, TABLE_A, TABLE_B, N, M);
		system("pause");
		return 0;
	}
}