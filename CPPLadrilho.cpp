#include "CLadrilho.h"

CLadrilho::CLadrilho()
{
	this->iLargura = 0;
	this->iAltura = 0;
	this->iPosx = 0;
	this->iPosy = 0;
	this->id = 0;
    this->imgLadrilho = NULL;
}

CLadrilho::~CLadrilho()
{
	this->iLargura = 0;
	this->iAltura = 0;
	this->iPosx = 0;
	this->iPosy = 0;
	this->id = 0;
	delete this->imgLadrilho;
}

void CLadrilho::Setax(int vx)
{
	this->iPosx = vx;
}

void CLadrilho::Setay(int vy)
{
	this->iPosy = vy;
}

void CLadrilho::Setaxy(int vx, int vy)
{
	this->iPosx += vx;
	this->iPosy += vy;
}

int CLadrilho::Pegax()
{
	return this->iPosx;
}

int CLadrilho::Pegay()
{
	return this->iPosy;
}

bool CLadrilho::Colisao(int obj2x,int obj2y, int obj2a, int obj2l)
{
	if (this->iPosx+this->iLargura > obj2x &&
        this->iPosx < obj2x+obj2l &&
        this->iPosy+this->iAltura > obj2y &&
        this->iPosy < obj2y+obj2a)
 		{
 		   return true;
		 } else
		   return false;
}

void CLadrilho::CarregaImagem(BITMAP *imgPedaco)
{
	draw_sprite(this->imgLadrilho, imgPedaco, 0, 0);
}

void CLadrilho::Atualiza(BITMAP *vimgQuadro)
{
	draw_sprite(vimgQuadro, this->imgLadrilho, this->iPosx, this->iPosy);
}

void CLadrilho::CriaImagem(int iTamLadrilho)
{
    imgLadrilho = create_bitmap(iTamLadrilho, iTamLadrilho);
}
