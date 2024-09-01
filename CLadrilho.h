#ifndef LADRILHO_H
#define LADRILHO_H

#include <allegro.h>

class CLadrilho
{
private:
	BITMAP *imgLadrilho;
	int iPosx;
	int iPosy;
public:
	int id;
	int iLargura;
	int iAltura;

	CLadrilho();
	~CLadrilho();
	void Setax(int);
	void Setay(int);
	void Setaxy(int, int);
	int Pegax();
	int Pegay();
	void Atualiza(BITMAP *);
	bool Colisao(int ,int , int , int);
	void CarregaImagem(BITMAP *);
    void CriaImagem(int);
};

#endif
