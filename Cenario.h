#include <allegro.h>

volatile long int fps = 0;
volatile long int contador = 0;
int mostra_fps = 0;
int conta_fps  = 0;

void MontaQuadro(CLadrilho [], BITMAP *);
void PosicionaLadrilhos(CLadrilho [], int [], int );
bool Verifica(int [], int, int);
void Embaralhar(int [], int);
void LimpaArray(int []);
void Pausar_Jogo(BITMAP *buffer);
bool VerificaFigura(CLadrilho Ladrilho[]);
void TrocaDesenho(CLadrilho [], int [], int);

static int iMovimentos = 0;

const int iTotalDesenhos = 19;
int Imagens[iTotalDesenhos] = {0,1,2,3,4,5,6,7,8,9,10,14,15,16,17,18,19,20,21};

const int Matriz_xy = 4; // Quantidade de Quadros na vertical e na horizontal

const int iTamLadrilho = 320 / Matriz_xy;
const int QtdeQuadrilhos = (Matriz_xy * Matriz_xy);
const int Limite_Teclado = 10;

static int Cenario[Matriz_xy][Matriz_xy];
static int iDesenho = 0;

DATAFILE *Dados = NULL;

void MontaQuadro(CLadrilho Ladrilho[],BITMAP *vimgImagem)
{
	int x = 0;
	int y = 0;
	int iControle = 0;

	BITMAP *imgPedaco = NULL;
  	imgPedaco = create_bitmap(iTamLadrilho, iTamLadrilho);
  	clear(imgPedaco);
  	
	for (x = 0; x < Matriz_xy; x++)
	{
		for (y = 0; y < Matriz_xy; y++)
		{
            Ladrilho[iControle].CriaImagem(iTamLadrilho);
			blit(vimgImagem,imgPedaco,y*iTamLadrilho,x*iTamLadrilho,0,0,iTamLadrilho,iTamLadrilho);
			rect(imgPedaco, 0, 0, iTamLadrilho-1, iTamLadrilho-1, makecol(255,255,255));
			Ladrilho[iControle].CarregaImagem(imgPedaco);
			Ladrilho[iControle].id = iControle;
			Ladrilho[iControle].iLargura = imgPedaco->w;
			Ladrilho[iControle].iAltura = imgPedaco->h;
			iControle++;
		}
	}
	delete imgPedaco;
}

void PosicionaLadrilhos(CLadrilho Ladrilho[],int iLista[], int iTamanho)
{
	int x = 0;
	int y = 0;
 	int iControle = 0;

	for (x=0; x<Matriz_xy; x++)
	{
		for (y=0; y<Matriz_xy; y++)
		{
			Ladrilho[iLista[iControle]].Setax(y * iTamLadrilho);
			Ladrilho[iLista[iControle]].Setay(x * iTamLadrilho);
			iControle++;
		}
	}
}

void IniciaCenario()
{
	int x = 0;
	int y = 0;
	int iControle = 0;
	
	for (x=0; x<Matriz_xy; x++)
	{
		for (y=0; y<Matriz_xy; y++)
		{
			Cenario[x][y] = 1;
			iControle++;
		}
	}
	Cenario[Matriz_xy-1][Matriz_xy-1] = 0;
}

bool Verifica(int iLista[], int iValor, int iTamanho)
{
	int i = 0;
	bool bDuplicidade = false;

	for (i=0; i<iTamanho; i++)
	{
  		if (iLista[i] == iValor)
  		{
	 		bDuplicidade = true;
  		}
	}

	return bDuplicidade;
}

void Embaralhar(int iLista[], int iTamanho)
{
	int iControle=0;
 	int iRND=0;

	LimpaArray(iLista);
	iMovimentos=0;

	iLista[QtdeQuadrilhos-1] = QtdeQuadrilhos-1;

	while (iControle<iTamanho-1)
	{
		iRND = int(rand()%iTamanho);

  		if (!Verifica(iLista,iRND,iTamanho))
  		{
  			iLista[iControle] = iRND;
  			iControle++;
  		}
	}
}

void LimpaArray(int iLista[])
{
	int i=0;

	for (i=0; i<QtdeQuadrilhos; i++)
	{
		iLista[i] = i+QtdeQuadrilhos;
	}
}

void Pausar_Jogo(BITMAP *buffer)
{
	BITMAP *imgPause=NULL;
	imgPause = (BITMAP*)Dados[12].dat;

	while(!key[KEY_ENTER])
	{
		draw_sprite(buffer, imgPause, 250, 420);
		draw_sprite(screen, buffer, 0, 0);
		fps=0;
	}

	imgPause = NULL;
	delete imgPause;
}

bool VerificaFigura(CLadrilho Ladrilho[])
{
	int x = 0;
	int y = 0;
 	int iControle = 0;
	bool bGameOver = true;
	bool bCancela = false;

	for (x=0;x<Matriz_xy;x++)
	{
		for (y=0; y<Matriz_xy; y++)
		{
			if (Ladrilho[iControle].Pegax() /iTamLadrilho != y ||
   				Ladrilho[iControle].Pegay() /iTamLadrilho != x ||
       			Ladrilho[iControle].id != iControle)
			{
				bGameOver=false;
				bCancela = true;
				break;
   			}
   			iControle++;
		}
		if (bCancela)
  		{
  			break;
		}
	}
	return bGameOver;
}

void TrocaDesenho(CLadrilho Ladrilho[], int iLista[],int iValor)
{
	iDesenho += iValor;

	iMovimentos = 0;
    if (iDesenho >= iTotalDesenhos)
    {
  		iDesenho = 0;
  	}else
  	if (iDesenho < 0)
    {
  		iDesenho = iTotalDesenhos-1;
  	}

  	MontaQuadro(Ladrilho,(BITMAP*)Dados[Imagens[iDesenho]].dat);
  	Embaralhar(iLista,QtdeQuadrilhos);
	PosicionaLadrilhos(Ladrilho, iLista, QtdeQuadrilhos);
  	IniciaCenario();
}

