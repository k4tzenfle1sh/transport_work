using namespace std;

struct Table_District {
	double TOVAR_AMT;
	int RASXOD;
	double U = NAN; //������
	double V = NAN; //�������
	bool isCheckedAlready = false; //���� �������� ������
	bool isUsedOnCycle = false; //���� ������� � ����� ������������
	bool isMinus_PT = true; //���� ������������� �����
	Table_District()
	{}

	Table_District(double xx, int yy, double aa, double bb, bool zz, bool kk, bool cc)
	{
		TOVAR_AMT = xx;
		RASXOD = yy;
		U = aa;
		V = bb;
		isCheckedAlready = zz;
		isUsedOnCycle = kk;
		isMinus_PT = cc;
	}
};

struct Table_A {
	int id;
	int AMT; //����� ��������� � ����������
	Table_A()
	{}

	Table_A(int xx, int yy)
	{
		id = xx;
		AMT = yy;
	}
};

struct Table_B {
	int id;
	int AMT; //����������� ���-�� ���������
	Table_B()
	{}

	Table_B(int xx, int yy)
	{
		id = xx;
		AMT = yy;
	}
};

struct Table_U {
	double U = NAN; //������
	Table_U()
	{}

	Table_U(double xx)
	{
		U = xx;
	}
};

struct Table_V {
	double V = NAN; //�������
	Table_V()
	{}

	Table_V(double xx)
	{
		V = xx;
	}
};

struct Table_Alpha {
	double a = NAN;
	int i,
		j;//�������
	Table_Alpha()
	{}

	Table_Alpha(double xx, int yy, int zz)
	{
		a = xx;
		i = yy;
		j = zz;
	}
};

struct WayCell {
	int i = NULL; //���������� ������
	int j = NULL; //���������� �������
	WayCell()
	{}

	WayCell(int aa, int bb)
	{
		i = aa;
		j = bb;

	}
};

int min = INT_MIN;
int A_BASIC_i, A_BASIC_j; //���������� �������� ����� ������
int iteration = NULL;

bool isOpenWork = false; //���� ���� ������
bool isFirstRun = true;
bool isFinalTry = false;
bool drawCycleWay = false;

int N = NULL; //������ �������
int	M = NULL; //������ ������������
int SUMM_A = NULL,
	SUMM_B = NULL;

Table_A *TABLE_A;
Table_B *TABLE_B;
Table_District **TABLE_DIST;

vector <WayCell> WAY; //������ ������ ���� ������

WayCell *SAVETHEWAY;