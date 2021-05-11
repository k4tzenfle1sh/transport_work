using namespace std;

struct Table_District {
	double				TOVAR_AMT = NAN;
	int					RASXOD = NULL;
	double				U = NAN;					//������
	double				V = NAN;					//�������
	bool				isCheckedAlready = false;	//���� �������� ������
	bool				isUsedOnCycle = false;		//���� ������� � ����� ������������
	bool				isMinus_PT = true;			//���� ������������� �����
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
	int					AMT;						//����� ��������� � ����������
	Table_AB()
	{}

	Table_AB(int xx, int yy)
	{
		id = xx;
		AMT = yy;
	}
};

struct Table_UV {
	double				AMOUNT = NAN;					//������
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
	int					i = NULL;					//���������� ������
	int					j = NULL;					//���������� �������
	WayCell()
	{}

	WayCell(int aa, int bb)
	{
		i = aa;
		j = bb;

	}
};

int						min = INT_MIN;
int						A_BASIC_i, A_BASIC_j;		//���������� �������� ����� ������
int						iteration = NULL;
int						N = NULL;					//������ �������, ��� �� j-e
int						M = NULL;					//������ ������������, ��� �� i-e
int						SUMM_A = NULL;
int						SUMM_B = NULL;

bool					isOpenWork = false;			//���� ���� ������
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

vector <WayCell>		WAY;						//������ ������ ���� ������

WayCell					*SAVETHEWAY;