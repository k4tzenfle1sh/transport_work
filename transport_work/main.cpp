#include <iostream>
#include <clocale>
#include <vector>
#include <conio.h>
#include <string>
#include "variables.h"

using namespace std;

bool CheckIsClosed(int A, int B) {
	if (A == B)
		return true;
	else
		return false;
}

void DrawTable(Table_District **D, Table_AB *A, Table_AB *B, int n, int m, int iteration, bool isFirstRun, bool isFinalTry, bool drawCycleWay) {
	if (!drawCycleWay) {
		if (isFirstRun)
			cout << "\n�������� ������� �������:" << endl;
		else if (!isFirstRun && iteration > 0 && !isFinalTry)
			cout << "\n������� " << iteration << "-� ��������:" << endl;
		else if (isFinalTry)
			cout << "\n�������� �������:" << endl;
		cout << "|----------------------------------------|" << endl;
		cout << "|      |b(j)| ";
		for (int i = 0; i < n; i++) {
			cout << "\t" << B[i].id << " | ";
		}
		cout << "\n| a(i) |    | ";
		for (int i = 0; i < n; i++) {
			cout << "\t" << B[i].AMT << " | ";
		}
		cout << "\n|----------------------------------------|" << endl;
		int u = 0;
		for (int i = 0; i < m; i++) {
			cout << "|  " << A[i].id << "   | " << A[i].AMT << " | ";
			for (int j = 0; j < n; j++) {
				if (!isnan(D[i][j].TOVAR_AMT))
					cout << "| " << D[i][j].TOVAR_AMT << " - " << D[i][j].RASXOD << " | ";
				else
					cout << "|      " << D[i][j].RASXOD << " | ";
			}
			cout << endl;
		}
		cout << "|----------------------------------------|" << endl;
	}
	else {
		cout << "\n���� ������������ " << iteration+1 << "-� ��������:" << endl;

		cout << "\n|--------------------------------|" << endl;
		int u = 0;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (!isnan(D[i][j].TOVAR_AMT))
					cout << "| " << D[i][j].TOVAR_AMT;
				else
					cout << "|   ";
				if (D[i][j].isUsedOnCycle) {
					if (D[i][j].isMinus_PT)
						cout << "  (-) | ";
					else
						cout << "  (+) | ";
				}
				else
					cout <<" - "<< D[i][j].RASXOD << " | ";
			}
			cout << endl;
		}
		cout << "|--------------------------------|" << endl;
	}
}

void cleanMemory(Table_District **TABLE_DIST, WayCell *SAVETHEWAY, vector <WayCell> WAY, int HORZ_M, int VERT_M) {
	for (int i = 0; i < HORZ_M; i++) {
		for (int j = 0; j < VERT_M; j++) {
			if (TABLE_DIST[i][j].isCheckedAlready == true) { //���� ������ ���-�� �����������, ��
															 //�������� ��� � ������ ������
				TABLE_DIST[i][j].isCheckedAlready = false;
				TABLE_DIST[i][j].isUsedOnCycle = false;
				TABLE_DIST[i][j].isMinus_PT = true;
			}
		}
	}

	//������� ������ ������ ��������
	delete[] SAVETHEWAY;

	//� �������� ���� ������ �����
	WAY.clear();

	/*
	Press
	F
	To
	Pay
	Respect
	*/
}

void replaceCycle(Table_District **TABLE_DIST, WayCell *SAVETHEWAY, vector <WayCell> WAY, int VERT_M, int HORZ_M) {
	int MIN = INT_MAX;
	//����� ������������ ��������
	for (int i = 0; i < WAY.size(); i++) { //���� ������ i,j ������ ����� ����������� � �������� ������� �� ������� �������� 
		if (TABLE_DIST[WAY[i].i][WAY[i].j].isUsedOnCycle && TABLE_DIST[WAY[i].i][WAY[i].j].isMinus_PT == true) { //���� ������ ������������� ������������� � ��� ���� ���������, ��
			if (TABLE_DIST[WAY[i].i][WAY[i].j].TOVAR_AMT <= MIN) //��������� �� �� �����������
				MIN = TABLE_DIST[WAY[i].i][WAY[i].j].TOVAR_AMT;
		}
	}

	//������, ������ ���������� �� ������������ ��������
	for (int i = 0; i < WAY.size(); i++) {
		if (TABLE_DIST[WAY[i].i][WAY[i].j].isUsedOnCycle) {
			if (TABLE_DIST[WAY[i].i][WAY[i].j].isMinus_PT == true) {
				TABLE_DIST[WAY[i].i][WAY[i].j].TOVAR_AMT = TABLE_DIST[WAY[i].i][WAY[i].j].TOVAR_AMT - MIN; //������������� ����� ������
				if (TABLE_DIST[WAY[i].i][WAY[i].j].TOVAR_AMT == 0.0)
					TABLE_DIST[WAY[i].i][WAY[i].j].TOVAR_AMT = NAN;
			}
			else {
				if (!isnan(TABLE_DIST[WAY[i].i][WAY[i].j].TOVAR_AMT)) //�������, ����� �� NaN
					TABLE_DIST[WAY[i].i][WAY[i].j].TOVAR_AMT = TABLE_DIST[WAY[i].i][WAY[i].j].TOVAR_AMT + MIN; //� �������������, ��� �� ��� ��������, �������
				else
					TABLE_DIST[WAY[i].i][WAY[i].j].TOVAR_AMT = 0.0 + MIN; //� ����� ������ �������� � ����, ��� � ������ ����
			}
		}
	}

	cleanMemory(TABLE_DIST, SAVETHEWAY, WAY, M, N); //���� ��������, ���� ���������� ������ � ��� ����� �����������
}

bool checkCell(Table_District **TABLE_DIST, int *i, int *j) {
	if ((!TABLE_DIST[*i][*j].isCheckedAlready && !TABLE_DIST[*i][*j].isUsedOnCycle) && !isnan(TABLE_DIST[*i][*j].TOVAR_AMT)) //���� ������ ����� ����� �� �������������
		return true; //�� ��� ���
	else
		return false; //���� ��� ��������� ����� - ���� ������
}

bool findway(Table_District **TABLE_DIST, WayCell *SAVETHEWAY, int VERT_M, int HORZ_M, int A_i, int A_j, int A_BASIC_i, int A_BASIC_j, int iteration, bool isCycleIsOver[], bool isVerticalSearch) {
	int *i_ptr;
	int *j_ptr; //��������� �� i-e, j-e
	int *A_Find; //��������� �� ���������� �������� �����, ���� ������ �� i, ���� �� j
	int *LIMIT; //��������� �� ����������� ������� ������/�������
	int A; //��� ������
	int *A_state, *A_state_from; //��������� �� �������� �������� ������� i/j � ��������
	int *A_check_valid; //��������� �� �������� ���������� ������� � ��������
	bool ifCheckedisTrue = false; //

	if (isVerticalSearch) { //���� ���� �� ���������, ��
		A_Find = &A_i; //���������� �������� ���� i-e
		LIMIT = &VERT_M; // ������������ �� ��������� (��������, ��� ��������, �� ��� ���� ������� ��� ��-�� ����� �����

		A_check_valid = &A_BASIC_i; //��������� �� i-�� ������

		A_state = &A_j; //� ��������� �������� �� j-��, ��� �� ������ �� ������
		A_state_from = &A_BASIC_j;

	}
	//�� j-�� ��� ����� ��������, ������ ��������, ���� ������ ��� ������
	else {
		A_Find = &A_j;
		LIMIT = &HORZ_M;

		A_check_valid = &A_BASIC_j;

		A_state = &A_i;
		A_state_from = &A_BASIC_i;
	}


	for (A = *A_Find - 1;; A--) { //���� �� ������ ������-��������� ����, ���� � ����� [0;0]
		if (A < 0) {
			A = *LIMIT - 1; //���� ����� ����� ����� ���� � ������ 
		}
		if (A == *A_check_valid && *A_state == *A_state_from) { //���� ���������� ������� ������ � ������� �������
			if ((iteration + 1) >= 4 && (iteration + 1) % 2 == 0) { //� ���� �������� �� ������� ������
				isCycleIsOver[0] = true; //�� ���� ��������, ���� �����
				return true;
			}
			else { //����� ����� ������� ������, ��� ����� ����� �� �����, ���
				isCycleIsOver[0] = true;
				return false;
			}
		}
		else if (A == *A_Find) { //���� �� ��������� � ����� ������, �� �� �������
			return false;
		}
		else {
			if (isVerticalSearch) {
				i_ptr = &A; //��������� �� ����� ����� �� i-�� ���� ��������� ������
				j_ptr = &A_j; //����� ��������� �� j-� ���� ������� ������ j-��
			}
			else {
				i_ptr = &A_i;
				j_ptr = &A;
			}
			if (checkCell(TABLE_DIST, i_ptr, j_ptr)) {
				SAVETHEWAY[0].i = *i_ptr; //������ i-e � �������, ��� ���� ������ �� ��������
				SAVETHEWAY[0].j = *j_ptr; //��� �� ������ j-e

				TABLE_DIST[*i_ptr][*j_ptr].isCheckedAlready = true; //������ ���� �������� ������
				TABLE_DIST[*i_ptr][*j_ptr].isUsedOnCycle = true; //������ ���� ������� �����


				if ((iteration + 1) % 2 == 0) //���� ������
					TABLE_DIST[*i_ptr][*j_ptr].isMinus_PT = false; //�� ���� �� �����
				else
					TABLE_DIST[*i_ptr][*j_ptr].isMinus_PT = true; //����� - �����
				return true;
			}
			else {
				TABLE_DIST[*i_ptr][*j_ptr].isCheckedAlready = true; //����� ������ ������ ���� �������� ������
			}
		}
		if (A - 1 < 0) //���� ��� ������� ���� �� ���������� ������� �� ������ �� ������� �������, ��
			A = *LIMIT; //���� �������� ����������� �������� ���
	}

}

void doRobot(Table_District **TABLE_DIST, WayCell *SAVETHEWAY, vector <WayCell> WAY, Table_AB *TABLE_A, Table_AB *TABLE_B, int VERT_M, int HORZ_M, int A_BASIC_i, int A_BASIC_j, int iter_from, bool isFirstRun, bool isFinalTry, bool drawCycleWay) {
	int A_i, A_j; //���������� ���������� �����
	int iteration = 0; //���������� ������� ��������
	bool isVerticalSearch = true; //�� ������� �������� ����� ���� ������ �� ���������
	bool check_cycle; //������ �����

	bool isCycleIsOver[1]; //������ ���������� ����� �������� ��� ��������� ����� ���������� �-���, �������� ���������
	isCycleIsOver[0] = false;

	//������� �������� �����
	A_i = A_BASIC_i; //����������� ������������ i, j ������ ������
	A_j = A_BASIC_j;

	WAY.push_back(WayCell(A_i, A_j)); //������ � ���� ������ ���

									  //���������� ��� �����
	TABLE_DIST[A_i][A_j].isCheckedAlready = true;
	TABLE_DIST[A_i][A_j].isUsedOnCycle = true;
	TABLE_DIST[A_i][A_j].isMinus_PT = false;

	SAVETHEWAY = new WayCell[1]; //������� ��������� �����. ������, ����� ������� �������� ����� ���������� �-���

								 //����� ����� �� ������
	check_cycle = findway(TABLE_DIST, SAVETHEWAY, VERT_M, HORZ_M, A_i, A_j, A_BASIC_i, A_BASIC_j, iteration, isCycleIsOver, isVerticalSearch);

	if (check_cycle && !isCycleIsOver[0]) { //���� �� ����� �� �� ����������, �� 
		WAY.push_back(WayCell(SAVETHEWAY[0].i, SAVETHEWAY[0].j)); // ������ ������ ���
		iteration = WAY.size() - 1; //����������� ��������

		A_i = WAY[WAY.size() - 1].i; //����������� ������������ i, j ��������� ������
		A_j = WAY[WAY.size() - 1].j;

		while (1) { //����� ������ ������, ���, �� ���� ����
			if (iteration % 2 == 0) { //���� ��������, �� ���� ������ ������ �����
				isVerticalSearch = true;
				check_cycle = findway(TABLE_DIST, SAVETHEWAY, VERT_M, HORZ_M, A_i, A_j, A_BASIC_i, A_BASIC_j, iteration, isCycleIsOver, isVerticalSearch);
			}
			else { //����� �����
				isVerticalSearch = false;
				check_cycle = findway(TABLE_DIST, SAVETHEWAY, VERT_M, HORZ_M, A_i, A_j, A_BASIC_i, A_BASIC_j, iteration, isCycleIsOver, isVerticalSearch);
			}

			if (check_cycle && !isCycleIsOver[0]) { //���� �� �����, ��
				WAY.push_back(WayCell(SAVETHEWAY[0].i, SAVETHEWAY[0].j)); //������ n-�	���
				A_i = WAY[WAY.size() - 1].i; //����������� ������������ i, j ��������� ������
				A_j = WAY[WAY.size() - 1].j;

				iteration = WAY.size() - 1; //����������� ��������
				continue;
			}
			if (!check_cycle && (isCycleIsOver[0] || !isCycleIsOver[0])) { //���� �� ��������� ��� ������ ���, � ��� ���� �� �� ��������� � �������� ����� 
				TABLE_DIST[A_i][A_j].isCheckedAlready = true; //���� ����, ��� ������ ��������� � ������� �� ������

				if (TABLE_DIST[A_i][A_j].isUsedOnCycle) //���� �� ��� ������ �� �������� � ����, �� �������� ���� �����
					TABLE_DIST[A_i][A_j].isUsedOnCycle = false;

				WAY.pop_back(); //������� ����������� ������� �� ������

				if (WAY.size() > 0) { //���� ��� ���� ���� ������������ ����� �� ��������, �� 
					A_i = WAY[WAY.size() - 1].i; //���� ������������
					A_j = WAY[WAY.size() - 1].j;

					iteration = WAY.size() - 1; //������� �������� �� �����������
					continue;
				}

				else { //���� ������, �� ���, ���� ��� ���� ����� ��������� ������
					break;
				}

			}
			if (check_cycle && isCycleIsOver[0]) {

				drawCycleWay = true;

				DrawTable(TABLE_DIST, TABLE_A, TABLE_B, HORZ_M, VERT_M, iter_from, isFirstRun, isFinalTry, drawCycleWay);
				drawCycleWay = false;

				replaceCycle(TABLE_DIST, SAVETHEWAY, WAY, VERT_M, HORZ_M);
				break;
			}
		}
	}
	else; //����� ����� �� ����� ���� ������� ������ ������� �� ���������, �������
}

bool CheckOptimal(Table_Alpha *TABLE_AL, int V_MASS, int INT_MAX_COUNT) {
	bool ifFirst = true;
	for (int i = 0; i < V_MASS; i++) {
		if (TABLE_AL[i].a <= 0)
			INT_MAX_COUNT++;
		else {
			if (ifFirst) {
				cout << "���� ���������� ������������� ����������: ";
				ifFirst = false;
			}
			cout << TABLE_AL[i].a << " ";
		}
	}

	if (INT_MAX_COUNT == V_MASS)
		return true;
	else
		return false;
}

void FindOptimal(Table_AB *TABLE_A, Table_AB *TABLE_B, Table_UV *TABLE_U, Table_UV *TABLE_V, Table_Alpha *TABLE_AL, Table_District **TABLE_DIST, int N, int M, int FULL_MASS, int V_MASS, int *SAVE_OPTI) {
	int temp = NULL,
		count_value = NULL;
	cout << "��������� ������������ �������� �����: " << endl;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (!isnan(TABLE_DIST[i][j].TOVAR_AMT)) {
				count_value++;
				if(count_value != FULL_MASS)
				cout << TABLE_DIST[i][j].TOVAR_AMT << " * " << TABLE_DIST[i][j].RASXOD << " + ";
				else
					cout << TABLE_DIST[i][j].TOVAR_AMT << " * " << TABLE_DIST[i][j].RASXOD << " = ";
				temp = temp + (TABLE_DIST[i][j].TOVAR_AMT*TABLE_DIST[i][j].RASXOD);
			}
		}
	}
	cout << temp << endl;
	SAVE_OPTI[0] = temp;

	count_value = NULL;

	//������� ����������� ������� �����
	cout << "\n������ �����������.\n�����������, ��� V[0] = 0. ����� ������ ���������� *�������* �����, ���:\n" << endl;
	TABLE_V[0].AMOUNT = 0.0;
	bool endofCycle = false;
	while (!endofCycle) {
		for (int j = 0; j < N; j++) {
			for (int i = 0; i < M; i++) {
				if (!isnan(TABLE_DIST[i][j].TOVAR_AMT)) {
					if (isnan(TABLE_U[j].AMOUNT) && !isnan(TABLE_V[i].AMOUNT)) {
						TABLE_U[j].AMOUNT = TABLE_DIST[i][j].RASXOD + TABLE_V[i].AMOUNT;
						cout << "U[" << j << "] = " << TABLE_DIST[i][j].RASXOD << " + " << TABLE_V[i].AMOUNT << " = " << TABLE_U[j].AMOUNT << ";" << endl;
						count_value++;
						continue;
					}
					else if (isnan(TABLE_V[i].AMOUNT) && !isnan(TABLE_U[j].AMOUNT)) {
						TABLE_V[i].AMOUNT = ((-1)*TABLE_DIST[i][j].RASXOD) + TABLE_U[j].AMOUNT;
						cout << "V[" << i << "] = -(" << TABLE_DIST[i][j].RASXOD << ") + " << TABLE_U[j].AMOUNT << " = " << TABLE_V[i].AMOUNT << ";" << endl;
						count_value++;
						continue;
					}
					else;
				}
			}
			if (count_value == FULL_MASS) {
				endofCycle = true;
				break;
			}
			else if (j + 1 >= N)
				j = -1;
			else;
		}
	}

	count_value = NULL;

	//����� ������� �����������
	cout << endl;
	for (int i = 0; i < FULL_MASS; i++) {
		if (!isnan(TABLE_V[i].AMOUNT))
			cout << "V[" << i + 1 << "] = " << TABLE_V[i].AMOUNT << ";" << endl;
		if (!isnan(TABLE_U[i].AMOUNT)) {
			if (i + 1 >= FULL_MASS)
				cout << "U[" << i + 1 << "] = " << TABLE_U[i].AMOUNT << "." << endl;
			else
				cout << "U[" << i + 1 << "] = " << TABLE_U[i].AMOUNT << ";" << endl;
		}
	}
	cout << endl;


	//������� ����������� ��������� �����
	cout << "������ ���������� ��������� ����� �� �������: U[i] - V[j] - ������ ������" << endl;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < M; i++) {
			if (isnan(TABLE_DIST[i][j].TOVAR_AMT)) {
				TABLE_AL[count_value].a = TABLE_U[j].AMOUNT - TABLE_V[i].AMOUNT - TABLE_DIST[i][j].RASXOD;
				cout << "AL[" << count_value << "] = U[" << j << "]-V[" << i << "]-" << TABLE_DIST[i][j].RASXOD << " = " << TABLE_U[j].AMOUNT << " - " << TABLE_V[i].AMOUNT << " - " << TABLE_DIST[i][j].RASXOD << " = " << TABLE_AL[count_value].a << endl;
				TABLE_AL[count_value].i = i;
				TABLE_AL[count_value].j = j;
				count_value++;
			}
		}
	}

	//�������
	cout << endl;
	for (int i = 0; i < V_MASS; i++) {
			cout << "AL[" << i + 1 << "] = " << TABLE_AL[i].a << " [" << TABLE_AL[i].i << ", " << TABLE_AL[i].j << "]" << endl;
	}

}

void FindMaximalNumber(Table_Alpha *TABLE_AL, int V_MASS, int *MAX_i, int *MAX_j) {
	double MAX = NULL;
	for (int i = 0; i < V_MASS; i++) {
		if (TABLE_AL[i].a >= MAX) {
			MAX = TABLE_AL[i].a;
			*MAX_i = TABLE_AL[i].i;
			*MAX_j = TABLE_AL[i].j;
		}
	}
	cout << MAX << endl;
}

void LetsDoSomeWork(WayCell *SAVETHEWAY, vector <WayCell> WAY, Table_AB *TABLE_A, Table_AB *TABLE_B, Table_District **TABLE_DIST, int N, int M, int iteration, bool isFirstRun, bool isFinalTry, bool drawCycleWay) {
	int *SAVE_OPTI;
	SAVE_OPTI = new int[1];
	vector <int> INT_OPTIMAL;
	int INT_MAX_COUNT = NULL,
		FULL_MASS = M + N - 1, //����� ������� ������
		EMPTY_MASS = NULL,
		V_MASS = (N * M) - FULL_MASS,
		MAX_i, MAX_j,
		i_FT, j_FT;

	i_FT = j_FT = MAX_i = MAX_j = NULL;

	Table_AB *TEMP_A = new Table_AB[M];
	Table_AB *TEMP_B = new Table_AB[N];
	Table_UV *TABLE_U = new Table_UV[FULL_MASS];
	Table_UV *TABLE_V = new Table_UV[FULL_MASS];
	Table_Alpha *TABLE_AL = new Table_Alpha[V_MASS];

	for (int i = 0; i < M; i++) {
		TEMP_A[i].AMT = TABLE_A[i].AMT;
		TEMP_A[i].id = TABLE_A[i].id;
	}
	for (int i = 0; i < N; i++) {
		TEMP_B[i].AMT = TABLE_B[i].AMT;
		TEMP_B[i].id = TABLE_B[i].id;
	}
	
	//���������� ������� �������� �����
	while (EMPTY_MASS < FULL_MASS) {
		bool isNotWorkedYet = true;
		if ((TEMP_A[j_FT].AMT > TEMP_B[i_FT].AMT || TEMP_A[j_FT].AMT == TEMP_B[i_FT].AMT) && isNotWorkedYet) {
			TABLE_DIST[j_FT][i_FT].TOVAR_AMT = TEMP_B[i_FT].AMT;
			//TABLE_DIST[j_FT][i_FT].isUsed = true;
			TEMP_A[j_FT].AMT = TEMP_A[j_FT].AMT - TEMP_B[i_FT].AMT;
			TEMP_B[i_FT].AMT = TEMP_B[i_FT].AMT - TEMP_B[i_FT].AMT;
			EMPTY_MASS++;
			i_FT++;
			isNotWorkedYet = false;
		}
		if ((TEMP_A[j_FT].AMT < TEMP_B[i_FT].AMT) && isNotWorkedYet) {
			TABLE_DIST[j_FT][i_FT].TOVAR_AMT = TEMP_A[j_FT].AMT;
			//TABLE_DIST[j_FT][i_FT].isUsed = true;
			TEMP_B[i_FT].AMT = TABLE_B[i_FT].AMT - TEMP_A[j_FT].AMT;
			TEMP_A[j_FT].AMT = TEMP_A[j_FT].AMT - TEMP_A[j_FT].AMT;
			EMPTY_MASS++;
			j_FT++;
			isNotWorkedYet = false;
		}
	}

	while (1) {
		DrawTable(TABLE_DIST, TABLE_A, TABLE_B, N, M, iteration, isFirstRun, isFinalTry, drawCycleWay);
		isFirstRun = false;
		FindOptimal(TABLE_A, TABLE_B, TABLE_U, TABLE_V, TABLE_AL, TABLE_DIST, N, M, FULL_MASS, V_MASS, SAVE_OPTI); //������ ����������� ���� ������������ ������ ������� �����������
		INT_OPTIMAL.push_back(SAVE_OPTI[0]);

		if (INT_OPTIMAL.size() > 1) {
			cout << "\n�� ��������� � �������� ������� �������� ������������ ������� ����������� �� " << INT_OPTIMAL[0] << " - " << INT_OPTIMAL[INT_OPTIMAL.size() - 1] << " = " << INT_OPTIMAL[0] - INT_OPTIMAL[INT_OPTIMAL.size() - 1] << endl;
		}
		//�������� �� �������������
		if (!CheckOptimal(TABLE_AL, V_MASS, INT_MAX_COUNT)) {
			cout << endl << "���������� ���� �� �������� �����������." << endl;
			int *i_ptr = &MAX_j,
				*j_ptr = &MAX_i;
			int count_h = NULL;
			cout << "������ ������������ ��������� ����� ���� ��������� �������������: ";
			FindMaximalNumber(TABLE_AL, V_MASS, i_ptr, j_ptr);


			for (int i = 0; i < FULL_MASS; i++) {
				TABLE_U[i].AMOUNT = NAN;
				TABLE_V[i].AMOUNT = NAN;
			}

			for (int i = 0; i < V_MASS; i++)
				TABLE_AL[i].a = NAN;

			cout << endl << "�������� ���� ������������. " << endl;
			doRobot(TABLE_DIST, SAVETHEWAY, WAY, TABLE_A, TABLE_B, M, N, MAX_j, MAX_i, iteration, isFirstRun, isFinalTry, drawCycleWay);
			iteration++;
			continue;
		}
		else {
			cout << endl << "���������� ���� �������� �����������." << endl;
			isFinalTry = true;
			DrawTable(TABLE_DIST, TABLE_A, TABLE_B, N, M, iteration, isFirstRun, isFinalTry, drawCycleWay);
			break;
		}
	}
}

void clearCin() {
	//������� ����������� �����
	cin.clear();
	//������������� ���������� ������� �����
	cin.ignore(INT_MAX, '\n');
	cout << "������������ ����. ������� ����� ������������� �����. ��������� ����." << endl;
	//��������� �����
	_getch();
	//������� ������
	//system("CLS");
	cout << endl;
}

double CheckData(string InputText) {

	double				temp = NULL;
	string				SymbolFromStringS;			//���������� ��� �������� ������ ������� �� ����� ������
	char				*String_buffer;				//����� �������� �������� ������
	char				*NewStringValue;			//���������� ������ ��� �������� "�������" ��������
	char				OneSynbol;					//���������� ��� �������� ������ ������� �� ������
	bool				NotASymbol = false;			//"���� �� ������", �� ��������� - "���"

	String_buffer = new char[1];
	NewStringValue = new char[1];

	while (!NotASymbol) { //���� �� ��������� �� ������
		for (int i = 0; i < strlen(InputText.c_str()); i++) {
			//������������ ������� ������� �������� ������ ���������
			SymbolFromStringS = InputText[i];
			//����������� ������� ������ � ������� ����������� �������
			strcpy(String_buffer, SymbolFromStringS.c_str());
			//����������� �������� ����������� ������� � ������ ���� char
			OneSynbol = String_buffer[0];
			//���� ������ ���� ����������� �����
			if (isdigit((unsigned char)OneSynbol))
			{
				//�������� ����� � ���������� ������� �� ��������� ������
				cin.putback(OneSynbol);
				cin >> NewStringValue[i];
			}
			//����� ���������� ���� ���������� �������
			else NotASymbol = true;
		}
		/*���� ������ ����� �� ��������� ����� �� ��������� ������,
		������, ��� ������ �� �������� � ���� ������������� �����������*/
		if (NewStringValue != NULL && !NotASymbol)
			break;
	}
	//���� ���� ������� ���������
	if (!NotASymbol) {
		//����������� ����������� ������� � �����
		double a = double(atoi(NewStringValue));
		return a;
	}
	//�����
	else {
		return NAN;
	}
}

bool CommandLineTextWrite_ToArrayDimension(double *MEM_MASSIVE, bool b_1stStage, bool b_2ndStage, bool b_3rdStage, bool b_4thStage, int dimension) {
	double					NeedForCheckPlz = NULL;
	string					TextInput;

	if (b_1stStage && !b_2ndStage && !b_3rdStage && !b_4thStage)
		cout << "������� ���-�� ������� ��������c���:\t";
	else if (!b_1stStage && b_2ndStage && !b_3rdStage && !b_4thStage)
		cout << "������� ���-�� ������� �������:\t";
	else if (!b_1stStage && !b_2ndStage && (b_3rdStage || b_4thStage)) {
		cout << "������� ���-�� ������� ��������� � ";
		if (b_3rdStage)
			cout << "�" << dimension + 1 << " ������:\t";
		if (b_4thStage)
			cout << "�" << dimension + 1 << " ������:\t";
	}

	cin >> TextInput;
	NeedForCheckPlz = CheckData(TextInput);
	if (isnan(NeedForCheckPlz))
		return false;
	else {
		MEM_MASSIVE[0] = NeedForCheckPlz;
		return true;
	}
}

/* //��� ������������ �������, � �� ����, ��� ��� ��������
void MakeClosed(Table_District **TABLE_DIST, Table_District **TEMP_TABLE_DIST, Table_AB *TABLE_A, Table_AB *TABLE_B, int *SAVE_THE_ARROW, bool WorkColumn, int SUMM_A, int SUMM_B) {
	
}*/

int main() {
	setlocale(0, "rus");
	MEM_MASSIVE = new double[1];
	do {
		if(!CommandLineTextWrite_ToArrayDimension(MEM_MASSIVE, is1stStageReady, is2ndStageReady, is3rdStageReady, is4thStageReady, NULL)){
			clearCin();
			continue;
		}
		else {
			M = int(MEM_MASSIVE[0]);
			is1stStageReady = false;
			is2ndStageReady = true;
			while (1) {
				if (!CommandLineTextWrite_ToArrayDimension(MEM_MASSIVE, is1stStageReady, is2ndStageReady, is3rdStageReady, is4thStageReady, NULL)) {
					clearCin();
					continue;
				}
				else {
					N = int(MEM_MASSIVE[0]);
					is2ndStageReady = false;
					break;
				}
			}
		}
		if (!is1stStageReady && !is2ndStageReady)	
			break;
	} while (1);

	cout << endl;

	TABLE_A = new Table_AB[M];
	TABLE_B = new Table_AB[N];
	TABLE_DIST = new Table_District*[M];
	for (int i = 0; i < M; i++)
		TABLE_DIST[i] = new Table_District[N];

	for (int i = 0; i < M; i++) {
		cout << "������� ������� �� ��������� ������� ��� A" << i + 1 << "������ �� ��������� � �1-�" << N << "��������:\t";
		for (int j = 0; j < N; j++) {
			while (1) {
				if (!CommandLineTextWrite_ToArrayDimension(MEM_MASSIVE, is1stStageReady, is2ndStageReady, is3rdStageReady, is4thStageReady, NULL)) {
					clearCin();
					continue;
				}
				else {
					TABLE_DIST[i][j].RASXOD = int(MEM_MASSIVE[0]);
					break;
				}
			}
		}
	}

	cout << endl;
	is3rdStageReady = true;
	for (int i = 0; i < M; i++) {
		while (1) {
			if (!CommandLineTextWrite_ToArrayDimension(MEM_MASSIVE, is1stStageReady, is2ndStageReady, is3rdStageReady, is4thStageReady, i)) {
				clearCin();
				continue;
			}
			else {
				TABLE_A[i].AMT = int(MEM_MASSIVE[0]);
				TABLE_A[i].id = i;
				SUMM_A = SUMM_A + TABLE_A[i].AMT;
				break;
			}
		}
	}

	cout << endl;
	is3rdStageReady = false;
	is4thStageReady = true;

	for (int i = 0; i < N; i++) {
		while (1) {
			if (!CommandLineTextWrite_ToArrayDimension(MEM_MASSIVE, is1stStageReady, is2ndStageReady, is3rdStageReady, is4thStageReady, i)) {
				clearCin();
				continue;
			}
			else {
				TABLE_B[i].AMT = int(MEM_MASSIVE[0]);
				TABLE_B[i].id = i;
				SUMM_B = SUMM_B + TABLE_B[i].AMT;
				break;
			}
		}
	}
	
	cout << endl;
	is4thStageReady = false;
	delete[]MEM_MASSIVE;
	
	if (!CheckIsClosed(SUMM_A, SUMM_B)) {
		cout << "���������� ������ ��������� ����. ���������� �������� ������ � ������������� ����." << endl;

		int *SAVE_THE_ARROW = new int[2];
		SAVE_THE_ARROW[0] = M;
		SAVE_THE_ARROW[1] = N;

		Table_District **TEMP_TABLE_DIST = new Table_District*[M];
		for (int i = 0; i < M; i++)
			TEMP_TABLE_DIST[i] = new Table_District[N];

		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				TEMP_TABLE_DIST[i][j].RASXOD = TABLE_DIST[i][j].RASXOD;
			}
		}
		delete[]TABLE_DIST;

		if (SUMM_A > SUMM_B) {
			isWorkWithColumn = true;
			cout << "��������� ������ ���������� ������ ��� ������������. ���������� �������� B" << N + 1 << " �������." << endl;
		}
		else {
			cout << "��������� ������ ���������� ����������� ��� �������. ���������� �������� �" << M + 1 << " ������." << endl;
		}

		/*� �� ���� ������ ����� ��������� ������� ��� �������� ���������, �������� ���������, �� ��� ����������*/
		//��� �� �������
		{
			int PREV;
			int *i_ptr;
			Table_AB *TABLE_AB_ptr;
			if (isWorkWithColumn) {
				i_ptr = &SAVE_THE_ARROW[1];
				TABLE_AB_ptr = &*TABLE_B;
			}
			else {
				i_ptr = &SAVE_THE_ARROW[0];
				TABLE_AB_ptr = &*TABLE_A;
			}


			PREV = *i_ptr;

			Table_AB *TEMP_TABLE_AB = new Table_AB[*i_ptr];

			for (int i = 0; i < *i_ptr; i++) {

				TEMP_TABLE_AB[i].AMT = TABLE_AB_ptr[i].AMT;
				TEMP_TABLE_AB[i].id = TABLE_AB_ptr[i].id;
			}
			*i_ptr = *i_ptr + 1;

			if (isWorkWithColumn) {
				delete[]TABLE_B;
				TABLE_B = new Table_AB[*i_ptr];
				TABLE_AB_ptr = &*TABLE_B;
			}
			else {
				delete[]TABLE_A;
				TABLE_A = new Table_AB[*i_ptr];
				TABLE_AB_ptr = &*TABLE_A;
			}


			for (int i = 0; i < *i_ptr; i++) {
				TABLE_AB_ptr[i].AMT = TEMP_TABLE_AB[i].AMT;
				TABLE_AB_ptr[i].id = TEMP_TABLE_AB[i].id;
				if (i + 1 == *i_ptr - 1) {
					cout << "� ����� ������, ����� ";
					if (isWorkWithColumn) {
						cout << "�" << *i_ptr << " ������ ����� " << SUMM_A << " - " << SUMM_B << " = " << SUMM_A - SUMM_B << endl;
						TABLE_AB_ptr[i + 1].AMT = SUMM_A - SUMM_B;
					}
					else {
						cout << "A" << *i_ptr << " ������ ����� " << SUMM_B << " - " << SUMM_A << " = " << SUMM_B - SUMM_A << endl;
						TABLE_AB_ptr[i + 1].AMT = SUMM_B - SUMM_A;
					}
					TABLE_AB_ptr[i + 1].id = i + 1;
					break;
				}
			}
			cout << "������ ��� ����� ����� � �������� ������� �� ��������� ����� 0." << endl;
			TABLE_DIST = new Table_District*[SAVE_THE_ARROW[0]];
			for (int i = 0; i < SAVE_THE_ARROW[0]; i++)
				TABLE_DIST[i] = new Table_District[SAVE_THE_ARROW[1]];

			for (int i = 0; i < SAVE_THE_ARROW[0]; i++) {
				for (int j = 0; j < SAVE_THE_ARROW[1]; j++) {
					if ((isWorkWithColumn && j != PREV) || (!isWorkWithColumn && i != PREV))
						TABLE_DIST[i][j].RASXOD = TEMP_TABLE_DIST[i][j].RASXOD;
					else if ((isWorkWithColumn && j == PREV) || (!isWorkWithColumn && i == PREV))
						TABLE_DIST[i][j].RASXOD = NULL;
				}
			}

		}

		M = SAVE_THE_ARROW[0];
		N = SAVE_THE_ARROW[1];

		cout << "������ ��������� � ��������� ����. ������ ����� ���������� � ������ ������� ������." << endl;
		LetsDoSomeWork(SAVETHEWAY, WAY, TABLE_A, TABLE_B, TABLE_DIST, N, M, iteration, isFirstRun, isFinalTry, drawCycleWay);
		system("pause");
		return 1;

	}
	else {
		cout << "���������� ������ ��������� ����. \nskip" << endl;
		LetsDoSomeWork(SAVETHEWAY, WAY, TABLE_A, TABLE_B, TABLE_DIST, N, M, iteration, isFirstRun, isFinalTry, drawCycleWay);
		system("pause");
		return 0;
	}
}