using namespace std;

struct Table_District {
	double TOVAR_AMT;
	int RASXOD;
	double U = NAN; //������
	double V = NAN; //�������
	bool isUsed = false;
	bool isMinus = true;
	bool isPlus = false;
	bool isGarbage = true;
	Table_District()
	{}

	Table_District(double xx, int yy, double aa, double bb, bool zz, bool kk, bool jj, bool hh)
	{
		TOVAR_AMT = xx;
		RASXOD = yy;
		U = aa;
		V = bb;
		isUsed = zz;
		isMinus = kk;
		isPlus = jj;
		isGarbage = hh;
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

bool isOpenWork = false; //���� ���� ������

int N = NULL, //������ �������
	M = NULL, //������ ������������
	SUMM_A = NULL,
	SUMM_B = NULL; 