#include <allegro.h>
#include "CLadrilho.h"
#include "Cenario.h"

void cont_fps()
{
   fps++;
   conta_fps++;
}
END_OF_FUNCTION(cont_fps);

void tempo()
{
   contador++;
}
END_OF_FUNCTION(tempo);

int main()
{
	allegro_init();
	install_keyboard();
	set_color_depth(32);
	install_mouse();
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
   	LOCK_VARIABLE(fps);
   	LOCK_FUNCTION(cont_fps);
   	install_int_ex(cont_fps, BPS_TO_TIMER(60));
   	LOCK_VARIABLE(contador);
   	LOCK_FUNCTION(tempo);
   	install_int(tempo, 100);

	int i = 0;
	int vMy = 0;
	int vMx = 0;
	int	buffer_teclado = 0;
	int iLista[QtdeQuadrilhos];

	bool bGameOver = false;
	bool bAjuda = false;
	bool bTrocaDesenho = false;

 	Dados = load_datafile("Dados.dat");
    
	BITMAP *buffer = NULL;
	buffer = create_bitmap(800,600);
	clear(buffer);

	BITMAP *imgQuadro = NULL;
	imgQuadro = create_bitmap(320,320);
	clear(imgQuadro);

 	IniciaCenario();

    CLadrilho *Ladrilho = new CLadrilho[QtdeQuadrilhos];

	MontaQuadro(Ladrilho, (BITMAP*)Dados[Imagens[iDesenho]].dat); // Desenhos.bmp
	Embaralhar(iLista, QtdeQuadrilhos);
	PosicionaLadrilhos(Ladrilho, iLista, QtdeQuadrilhos);

	while(!bGameOver)
	{
		while( fps > 0)
      	{
            blit((BITMAP*)Dados[13].dat,buffer,0,0,0,0,800,600); // FUNDO.BMP
            blit((BITMAP*)Dados[13].dat,imgQuadro,56,80,0,0,320,320); // FUNDO.BMP
			textprintf_ex(buffer,font,0,0,makecol(255,0,0),-1, "Quebra Cuca 1.2");
			textprintf_ex(buffer,font,0,10,makecol(255,255,0),-1, "Desenho: %d",iDesenho+1);
			textprintf_ex(buffer,font,0,20,makecol(255,255,0),-1, "Movimentos: %d",iMovimentos);

			textprintf_ex(buffer,font,413,0,makecol(255,0,0),-1, "Controles: ");
			textprintf_ex(buffer,font,413,10,makecol(255,255,0),-1, "F1  - Ajuda");
			textprintf_ex(buffer,font,413,20,makecol(255,255,0),-1, "F10 - Embaralhar");
			textprintf_ex(buffer,font,413,30,makecol(255,255,0),-1, "F11 - Desenho Anterior");
			textprintf_ex(buffer,font,413,40,makecol(255,255,0),-1, "F12 - Proximo Desenho");
			textprintf_ex(buffer,font,413,50,makecol(255,255,0),-1, "ESC - Sair do Jogo");

			for (i=0;i<(QtdeQuadrilhos-1);i++)
   			{
  				Ladrilho[i].Atualiza(imgQuadro);
  				if (bAjuda)
  				{
  					textprintf_ex(imgQuadro,font,Ladrilho[i].Pegax()+2,Ladrilho[i].Pegay()+2,makecol(255,255,0),-1, "%d",Ladrilho[i].id);
  				}
			}

			draw_sprite(buffer,(BITMAP*)Dados[Imagens[iDesenho]].dat,413,80);
			draw_sprite(imgQuadro,(BITMAP*)Dados[11].dat,mouse_x,mouse_y); // MOUSE.BMP
 			draw_sprite(buffer,imgQuadro,56,80);

			bTrocaDesenho = VerificaFigura(Ladrilho);
			if (bTrocaDesenho)
			{
				TrocaDesenho(Ladrilho,iLista,1);
				Pausar_Jogo(buffer);
			}

   			if (buffer_teclado == 0)
			{
				if (key[KEY_ESC]) // Fim de jogo
				{
					bGameOver=true;
					buffer_teclado = Limite_Teclado;
				}

				if(key[KEY_F1]) // Ativa Ajuda
				{
					if (bAjuda)
					{
						bAjuda = false;
						buffer_teclado = Limite_Teclado;
					}
     				else
     				{
         				bAjuda = true;
         				buffer_teclado = Limite_Teclado;
         			}
				}

				if (key[KEY_F10]) // Embaralha
				{
   					Embaralhar(iLista,QtdeQuadrilhos);
					PosicionaLadrilhos(Ladrilho, iLista, QtdeQuadrilhos);
  					IniciaCenario();
  					buffer_teclado = Limite_Teclado;
				}

				if (key[KEY_F11]) // Volta Desenho
				{
					TrocaDesenho(Ladrilho,iLista,-1);
					buffer_teclado = Limite_Teclado;
					
				}

				if (key[KEY_F12]) // Avança Desenho
				{
					TrocaDesenho(Ladrilho,iLista,1);
					buffer_teclado = Limite_Teclado;
				}
			} else buffer_teclado--;
			
			if (mouse_b & 1)
			{
				for (i=0;i<QtdeQuadrilhos;i++)
				{
					if (Ladrilho[i].Colisao(mouse_x,mouse_y,1,1))
					{
						vMx=Ladrilho[i].Pegax() / iTamLadrilho;
						vMy=Ladrilho[i].Pegay() / iTamLadrilho;

						//Cima
						if (vMy > 0)
      					{
							if (Cenario[vMx][vMy-1] == 0)
							{
								Cenario[vMx][vMy] = 0;
								Ladrilho[i].Setaxy(0,-iTamLadrilho);
								Cenario[Ladrilho[i].Pegax() / iTamLadrilho][Ladrilho[i].Pegay() / iTamLadrilho] = 1;
								iMovimentos++;
							}
      					}
						//Baixo
      					if (vMy < Matriz_xy-1)
           				{
							if (Cenario[vMx][vMy+1] == 0)
							{
								Cenario[vMx][vMy] = 0;
								Ladrilho[i].Setaxy(0,iTamLadrilho);
								Cenario[Ladrilho[i].Pegax() / iTamLadrilho][Ladrilho[i].Pegay() / iTamLadrilho] = 1;
			 					iMovimentos++;
							}
      					}
						//Direita
						if (vMx < Matriz_xy-1)
      					{
							if (Cenario[vMx+1][vMy] == 0)
							{
								Cenario[vMx][vMy] = 0;
								Ladrilho[i].Setaxy(iTamLadrilho,0);
       							Cenario[Ladrilho[i].Pegax() / iTamLadrilho][Ladrilho[i].Pegay() / iTamLadrilho] = 1;
       							iMovimentos++;
							}
       					}
						//Esquerda
   						if (vMx > 0)
         				{
      						if (Cenario[vMx-1][vMy] == 0)
							{
								Cenario[vMx][vMy] = 0;
								Ladrilho[i].Setaxy(-iTamLadrilho,0);
								Cenario[Ladrilho[i].Pegax() / iTamLadrilho][Ladrilho[i].Pegay() / iTamLadrilho] = 1;
								iMovimentos++;
							}
       					}
					}
				}
			}
			
			fps--;
		}
		blit(buffer,screen,0,0,0,0,800,600);
		vsync();
	}
	
	unload_datafile(Dados);
	buffer = NULL;
	imgQuadro = NULL;
 	delete buffer;
	delete imgQuadro;
	allegro_exit();
	return 0;
}

END_OF_MAIN();
