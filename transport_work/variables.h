using namespace std;

struct Table_District {
	double TOVAR_AMT;
	int RASXOD;
	double U = NAN; //строка
	double V = NAN; //столбец
	bool isCheckedAlready = false; //флаг проверки €чейки
	bool isUsedOnCycle = false; //флаг вершины в цикле перестановки
	bool isMinus_PT = true; //флаг отрицательной метки
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
	int AMT; //запас продукции в количестве
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
	int AMT; //необходимое кол-во продукции
	Table_B()
	{}

	Table_B(int xx, int yy)
	{
		id = xx;
		AMT = yy;
	}
};

struct Table_U {
	double U = NAN; //строка
	Table_U()
	{}

	Table_U(double xx)
	{
		U = xx;
	}
};

struct Table_V {
	double V = NAN; //столбец
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
		j;//столбец
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
	int i = NULL; //координата строки
	int j = NULL; //координата столбца
	WayCell()
	{}

	WayCell(int aa, int bb)
	{
		i = aa;
		j = bb;

	}
};

int min = INT_MIN;
int A_BASIC_i, A_BASIC_j; //координаты исходной точки поиска
int iteration = NULL;

bool isOpenWork = false; //флаг типа задачи
bool isFirstRun = true;
bool isFinalTry = false;
bool drawCycleWay = false;

int N = NULL; //пункты продажи
int	M = NULL; //пункты производства
int SUMM_A = NULL,
	SUMM_B = NULL;

Table_A *TABLE_A;
Table_B *TABLE_B;
Table_District **TABLE_DIST;

vector <WayCell> WAY; //вектор пам€ти пути робота

WayCell *SAVETHEWAY;