using namespace std;

struct Table_District {
	double				TOVAR_AMT = NAN;
	int					RASXOD = NULL;
	double				U = NAN;					//строка
	double				V = NAN;					//столбец
	bool				isCheckedAlready = false;	//флаг проверки €чейки
	bool				isUsedOnCycle = false;		//флаг вершины в цикле перестановки
	bool				isMinus_PT = true;			//флаг отрицательной метки
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

struct Table_AB {
	int					id;
	int					AMT;						//запас продукции в количестве
	Table_AB()
	{}

	Table_AB(int xx, int yy)
	{
		id = xx;
		AMT = yy;
	}
};

struct Table_UV {
	double				AMOUNT = NAN;					//строка
	Table_UV()
	{}

	Table_UV(double xx)
	{
		AMOUNT = xx;
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
	int					i = NULL;					//координата строки
	int					j = NULL;					//координата столбца
	WayCell()
	{}

	WayCell(int aa, int bb)
	{
		i = aa;
		j = bb;

	}
};

int						min = INT_MIN;
int						A_BASIC_i, A_BASIC_j;		//координаты исходной точки поиска
int						iteration = NULL;
int						N = NULL;					//пункты продажи, оно же j-e
int						M = NULL;					//пункты производства, оно же i-e
int						SUMM_A = NULL;
int						SUMM_B = NULL;

bool					isOpenWork = false;			//флаг типа задачи
bool					isFirstRun = true;
bool					isFinalTry = false;
bool					drawCycleWay = false;
bool					is1stStageReady = true;
bool					is2ndStageReady = false;
bool					is3rdStageReady = false;
bool					is4thStageReady = false;
bool					isWorkWithColumn = false;

Table_AB					*TABLE_A;
Table_AB					*TABLE_B;
Table_District			**TABLE_DIST;

double					*MEM_MASSIVE;

vector <WayCell>		WAY;						//вектор пам€ти пути робота

WayCell					*SAVETHEWAY;