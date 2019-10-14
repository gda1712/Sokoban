#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "myconio.h"
#include "mapas.h"

struct puntuaciones
{
	char nombre[3][4];
	int puntaje[3];
};

void animacion_Control();
void animacion();			
void llenar_Inicio_Estructura(struct puntuaciones *p);
int menu(int *nvl, struct puntuaciones facil, struct puntuaciones medio, struct puntuaciones dificil, struct puntuaciones *arcade);
void instrucciones(int modo);
void modo_Arcade(struct puntuaciones *arcade);
void seleccionar_Nvl(int *i, int *j, int *tam1, int *tam2, int mapa[][19], int nvl);
void imprimir_Mapa(int tam1, int tam2, int mapa[][19], int x, int y, int cont);
int mover(int *i, int *j, int mapa[][19], int nvl, int modo);
int exite_Movimiento(int mapa[][19], int nvl);
int mover_Caja(int *i, int *j, int k, int l, int mapa[][19]);
void mostrar_Puntuaciones(struct puntuaciones facil, struct puntuaciones medio, struct puntuaciones dificil, struct puntuaciones *arcade);
int ganar(int mapa[][19], int nvl);
void registrar_Puntaje(struct puntuaciones *p, int cont, int nvl);
void setCursorVisible(BOOL visible);
void dormir(float seconds);


int main()
{
	struct puntuaciones facil, medio, dificil, arcade;
	int i, j, gana = 0, move,  x = 45, y = 10, nvl = 3, tam1, tam2, cont = 0, mapa[19][19];
	setCursorVisible(0);
	animacion_Control();
	llenar_Inicio_Estructura(&facil);
	arcade = dificil = medio = facil;


	while(menu(&nvl, facil, medio, dificil, &arcade) != 0)
	{
		gana = 0;
		setCursorVisible(0);
		seleccionar_Nvl(&i, &j, &tam1, &tam2, mapa, nvl);
		instrucciones(1);
		while(1)
		{
			setCursorVisible(0);
			imprimir_Mapa(tam1, tam2, mapa, x, y, cont);
			move = mover(&i, &j, mapa, nvl, 1);
			if(move == 5)
			{
				system("cls");
				seleccionar_Nvl(&i, &j, &tam1, &tam2, mapa, nvl);
				cont = 0;
			}
			if(move == 1)
				cont += 1;
				
			if(move == 4)
			{
				gana = 0;
				break;
			}
			if(ganar(mapa, nvl) == 1)
			{
				gana = 1;
				break;
			}
		}
		imprimir_Mapa(tam1, tam2, mapa, x, y, cont);

		if (nvl == 1 && gana == 1)
			registrar_Puntaje(&facil, cont, nvl);
		else if (nvl == 2 && gana == 1)
			registrar_Puntaje(&medio, cont, nvl);
		else if(nvl == 3 && gana == 1)
			registrar_Puntaje(&dificil, cont, nvl);
		system("cls");
		cont = 0;
		
	}
	return 0;
}


void animacion_Control()
{
	int i, j, y = 5;
	float tiempo = 0.5;
	gotoxy(42,y);
	y = 5;
	for (i = 0; i < 19; ++i)
	{
		for (j = 0; j < 31; ++j)
		{
			
			if (control[i][j] == 15)
			{
				textcolor(15);
				printf("%c", 219);
			}
			else
			{
				textcolor(0);
				printf("%c", 219);
			}
		}
		y++;
		gotoxy(42,y);
	}

	dormir(tiempo);
	y = 5;

	for (i = 0; i < 19; ++i)
	{
		for (j = 0; j < 31; ++j)
		{
			if (control[i][j] == 13)
			{
				textcolor(12);
				printf("%c", 219);
			}
			else
			{
				textcolor(0);
				printf("%c", 219);
			}
		}
		y++;
		gotoxy(42,y);
	}

	dormir(tiempo);
	y = 5;

	for (i = 0; i < 19; ++i)
	{
		for (j = 0; j < 31; ++j)
		{
			if (control[i][j] == 12)
			{
				textcolor(12);
				printf("%c", 219);
			}
			else
			{
				textcolor(0);
				printf("%c", 219);
			}
		}
		y++;
		gotoxy(42,y);
	}
	dormir(tiempo);
	y = 5;
	gotoxy(42,y);
	for (i = 0; i < 19; ++i)
		{
			for (j = 0; j < 31; ++j)
			{
				if (control[i][j] == 12 || control[i][j] == 13)
				{
					textcolor(12);
					printf("%c", 219);
				}
				else if (control[i][j] == 15)
				{
					textcolor(15);
					printf("%c", 219);
				}
				else if (control[i][j] == 7)
				{
					textcolor(7);
					printf("%c", 219);
				}
				else
				{
					textcolor(9);
					printf("%c", 219);
				}
			}
			y++;
			gotoxy(42,y);
		}
		gotoxy(51,6);
		printf("GABRIEL DIAZ");
		sleep(2);
		system("cls");
}


void animacion()
{
	int i, j, y = 0;
	gotoxy(32,y);
	for (i = 0; i < 12; i++)
	{
		for(j = 0; j < 50; j++)
		{
			if(soka[i][j] == 0)
			{
				textcolor(14);
				printf("%c", 178);	
			}else
			{
				textcolor(0);
				printf("%c", 178);
			}
			dormir(0.005);
		}
		y++;
		gotoxy(32,y);
	}
	y = 0;
	gotoxy(32,0);
	for (i = 0; i < 12; i++)
	{
		for(j = 0; j < 50; j++)
		{
			if(soka[i][j] == 0)
			{
				textcolor(14);
				printf("%c", 219);	
			}else
			{
				textcolor(0);
				printf("%c", 219);
			}
			dormir(0.001);
		}
		y++;
		gotoxy(32,y);
	}
}


void llenar_Inicio_Estructura(struct puntuaciones *p)
{
	int i;
	for (i = 0; i < 3; ++i)
	{
		p -> puntaje[i] = 0;
		strcpy(p -> nombre[i],"NNN");
	}
}


int menu(int *nvl, struct puntuaciones facil, struct puntuaciones medio, struct puntuaciones dificil, struct puntuaciones *arcade)
{
	int opcion = 1, aceptar = 0, pos = 16;
	animacion();
	textcolor(14);
	setCursorVisible(0);
	gotoxy(52,15);
	printf("SOKOBAN\n");
	gotoxy(45,pos);
	printf("->");
	gotoxy(50,16);
	printf("Modo Clasico\n");
	gotoxy(50,17);
	printf("Modo  Arcade\n");
	gotoxy(50,18);
	printf("Puntuaciones\n");
	gotoxy(54,19);
	printf("Salir\n");
	
	while(aceptar != 13)
	{
		aceptar = getch();
		if (aceptar == 72 && opcion > 1)
			{
			opcion -= 1;
			gotoxy(45,pos);
			printf("  ");
			pos -= 1;
			}
		if (aceptar == 80 && opcion < 4)
			{
			opcion += 1;
			gotoxy(45,pos);
			printf("  ");
			pos += 1;
			}
		gotoxy(45,pos);
		printf("->");
	}

	if(opcion == 1)
	{
		pos = 3;
		system("cls");
		gotoxy(52,1);
		printf("SOKOBAN\n");
		gotoxy(45,pos);
		printf("->");
		gotoxy(48,3);
		printf("Nivel 1: Facil\n");
		gotoxy(48,4);
		printf("Nivel 2: Medio\n");
		gotoxy(48,5);
		printf("Nivel 3: Dificil\n");

		
		do
		{
			aceptar = getch();
			if (aceptar == 72 && opcion > 1)
				{
				opcion -= 1;
				gotoxy(45,pos);
				printf("  ");
				pos -= 1;
				}
			if (aceptar == 80 && opcion < 3)
				{
				opcion += 1;
				gotoxy(45,pos);
				printf("  ");
				pos += 1;
				}
			gotoxy(45,pos);
			printf("->");
		}while(aceptar != 13);
		*nvl = opcion;
		system("cls");
		return 1;
	}
	if (opcion == 2)
	{
		system("cls");
		modo_Arcade(arcade);
		menu(nvl, facil, medio, dificil,arcade);
		return 1;
	}
	if (opcion == 3)
	{
		system("cls");
		mostrar_Puntuaciones(facil, medio, dificil, arcade);
		menu(nvl, facil, medio, dificil,arcade);
		return 1;
	}
	if (opcion == 4)
		exit(0);
}


void instrucciones(int modo)
{
	system("cls");
	if(modo == 1)
	{
		gotoxy(51,20);
		printf("MODO CLASICO");
		gotoxy(18,10);
		printf("Completa individualmente Cada nivel con la menor cantidad de movimientos para ganar");
		sleep(4);
	}else
	{
		gotoxy(46,20);
		printf("MODO ARCADE (EXTREMO)");
		gotoxy(27,10);
		printf("Completa sin bloquear cada nivel para ganar, un error y pierdes...");
		sleep(4);
	}
	system("cls");
	gotoxy(46,1);
	printf("SOKOBAN INSTRUCCIONES\n");
	gotoxy(48,3);
	printf("W -> ARRIBA\n");
	gotoxy(48,4);
	printf("S -> ABAJO\n");
	gotoxy(48,5);
	printf("A -> IZQUIERDA\n");
	gotoxy(48,6);
	printf("D -> DERECHA\n");
	gotoxy(48,8);
	printf("C -> REINICIAR(solo modo clasico)\n");
	gotoxy(48,9);
	printf("X -> SALIR\n");
	sleep(5);
	system("cls");
}


void modo_Arcade(struct puntuaciones *arcade)
{
	int i, j, move, x = 45, y = 10, nvl, tam1, tam2, cont = 0, mapa[19][19];

	instrucciones(2);
	
	for(nvl = 1; nvl <= 3; nvl++)
	{
	seleccionar_Nvl(&i, &j, &tam1, &tam2, mapa, nvl);
	
	setCursorVisible(0);

	while(1)
	{
	setCursorVisible(0);
	imprimir_Mapa(tam1, tam2, mapa, x, y, cont);
	move = mover(&i, &j, mapa, nvl, 2);

	if (move == 1)
		cont += 1;
	if (move == 4)
		{
		system("cls");
		return;
		}
	if(ganar(mapa, nvl) == 1)
		break;
	}
	imprimir_Mapa(tam1, tam2, mapa, x, y, cont);
	sleep(3);
	system("cls");
		
	}
	registrar_Puntaje(arcade, cont, 4);
}


void seleccionar_Nvl(int *i, int *j, int *tam1, int *tam2, int mapa[][19], int nvl)
{
	int k, l;
	if(nvl == 1)
	{
		for(k = 0; k < 11; k++)
			for(l = 0; l < 19; l++)
				mapa[k][l] = mapa1[k][l];
			
	 	*i = 8;
		*j = 11;
		*tam1 = 11;
		*tam2 = 19;

		return;
	}
	if(nvl == 2)
	{
		for(k = 0; k < 11; k++)
			for(l = 0; l < 19; l++)
				mapa[k][l] = mapa2[k][l];
			
	 	*i = 1;
		*j = 14;
		*tam1 = 10;
		*tam2 = 17;

		return;
	}
	if(nvl == 3)
	{
		for(k = 0; k < 14; k++)
			for(l = 0; l < 19; l++)
				mapa[k][l] = mapa3[k][l];
			
	 	*i = 11;
		*j = 10;
		*tam1 = 14;
		*tam2 = 19;

		return;
	}
}


void imprimir_Mapa(int tam1, int tam2, int mapa[][19], int x, int y, int cont)
{
	int i, j;
	gotoxy(52,0);
	textcolor(15);
	printf("Movimientos: %d", cont);
	for (i = 0; i < tam1; ++i)
	{
		gotoxy(x,y++);
		for (j = 0; j < tam2; ++j)
		{
				textcolor(mapa[i][j]);
				if (mapa[i][j] == 9)
					printf("%c%c", 178, 178);
				else if(mapa[i][j] != 0) 
					printf("%c%c", 178, 219);
				else
					printf("%c%c", 219, 219);
		}
		
	}
}


int mover(int *i, int *j, int mapa[][19], int nvl, int modo)
{
	int retorno, k = *i, l = *j, movimiento;
	char tecla;

	movimiento = exite_Movimiento(mapa, nvl);
	if (movimiento == 0)
	{
		textcolor(15);
		gotoxy(42,25);
		if(modo ==1)
			printf("Sin Movimientos, Presiona 'C' para reiniciar");
		else 
			printf("Sin Movimientos, Presiona 'X' para salir");
	}

	tecla = tolower(getch());
	textcolor(15);

	if (tecla == 'a' && mapa[*i][*j-1] != 9)
	{
		l -= 1;
		retorno = mover_Caja(i, j, k, l, mapa);
		if (retorno == 1)
			return 1;
		if (retorno == 2)
			return 0;
		mapa[*i][*j] = 0;
		*j -= 1;
		mapa[*i][*j] = 10;
		return 1;
	}
	if (tecla == 's' && mapa[*i+1][*j] != 9)
	{
		k += 1;
		retorno = mover_Caja(i, j, k, l, mapa);
		if (retorno == 1)
			return 1;
		if (retorno == 2)
			return 0;
		mapa[*i][*j] = 0;
		*i += 1;
		mapa[*i][*j] = 10;
		return 1;
	}
	if (tecla == 'd' && mapa[*i][*j+1] != 9)
	{
		l += 1;
		retorno = mover_Caja(i, j, k, l, mapa);
		if (retorno == 1)
			return 1;
		if (retorno == 2)
			return 0;
		mapa[*i][*j] = 0;
		*j += 1;
		mapa[*i][*j] = 10;
		return 1;
	}
	if (tecla == 'w' && mapa[*i-1][*j] != 9)
	{
		k -= 1;
		retorno = mover_Caja(i, j, k, l, mapa);
		if (retorno == 1)
			return 1;
		if (retorno == 2)
			return 0;
		mapa[*i][*j] = 0;
		*i -= 1;
		mapa[*i][*j] = 10;
		return 1;
	}
	if (tecla == 'x')
		return 4;
	if (tecla == 'c' && movimiento == 0)
		return 5;
	return 0;
}


int exite_Movimiento(int mapa[][19], int nvl)
{
	int i, j, k, l;

	for (i = 0; i < 19; ++i)
	{
		for (j = 0; j < 19; ++j)
		{
			if(nvl == 1)
			{
				for (k = 6; k <= 8; k++)
					for(l = 16; l <= 17; l++)
						if(i == k && l == j)
							j += 1;
			}

			if(nvl == 2)
			{
				for (k = 6; k <= 8; k++)
					for(l = 1; l <= 4; l++)
						if(i == k && l == j)
							j += 1;
			}

			if(nvl == 3)
			{
				for (k = 1; k <= 5; k++)
					for(l = 14; l <= 17; l++)
						if(i == k && l == j)
							j += 1;
			}

			if(mapa[i][j] == 6 && mapa[i][j+1] == 6)
			{
				if (mapa[i-1][j] == 9 && mapa[i-1][j+1] == 9)
					return 0;
				if (mapa[i+1][j] == 9 && mapa[i+1][j+1] == 9)
					return 0;
			}
			if (mapa[i][j] == 6 && mapa[i+1][j] == 6)
			{
				if (mapa[i][j-1] == 9 && mapa[i+1][j-1] == 9)
					return 0;
				if (mapa[i][j+1] == 9 && mapa[i+1][j+1] == 9)
					return 0;
			}
			if (mapa[i][j] == 6 && mapa[i][j+1] == 6 && mapa[i+1][j] == 6 && mapa[i+1][j+1] == 6)
			{
				return 0;
			}
			if (mapa[i][j] == 6)
			{
				if (mapa[i][j-1] == 9)
				{
					if (mapa[i+1][j] == 9)
						return 0;
					if (mapa[i-1][j] == 9)
						return 0;
				}
				if (mapa[i][j+1] == 9)
				{
					if (mapa[i+1][j] == 9)
						return 0;
					if (mapa[i-1][j] == 9)
						return 0;
				}
			}
		}
	}
	return 1;
}


int mover_Caja(int *i, int *j, int k, int l, int mapa[][19])
{
	if (mapa[k][l] != 6)
		return 0;

	if (*i != k)
	{
		if (*i < k)
		{
			if (mapa[k+1][l] == 0 || mapa[k+1][l] == 12)
			{
				
				mapa[*i][*j] = 0;
				mapa[k][l] = 10;
				mapa[k+1][l] = 6;
				*i = k;
				return 1;
			}
			return 2;
		}else if (*i > k)
		{
			if (mapa[k-1][l] == 0 || mapa[k-1][l] == 12)
			{
				mapa[*i][*j] = 0;
				mapa[k][l] = 10;
				mapa[k-1][l] = 6;
				*i = k;
				return 1;
			}
		return 2;
		}
	}
	if (*j != l)
	{
		if (*j < l)
		{
			if (mapa[k][l+1] == 0 || mapa[k][l+1] == 12)
			{
				mapa[*i][*j] = 0;
				mapa[k][l] = 10;
				mapa[k][l+1] = 6;
				
				*j = l;
				return 1;
			}
			return 2;
		}else if (*j > l)
		{
			if (mapa[k][l-1] == 0 || mapa[k][l-1] == 12)
			{
				
				mapa[*i][*j] = 0;
				mapa[k][l] = 10;
				mapa[k][l-1] = 6;
				*j = l;
				return 1;
			}
		return 2;
		}
	}

}


void mostrar_Puntuaciones(struct puntuaciones facil, struct puntuaciones medio, struct puntuaciones dificil, struct puntuaciones *arcade)
{
	int mostrar = 1, i, j = 2, aceptar = 0, pos = 3;
	gotoxy(46,1);
	printf("SOKOBAN PUNTUACIONES\n");
	gotoxy(45,pos);
	printf("->");
	gotoxy(48,3);
	printf("Nivel 1: Facil\n");
	gotoxy(48,4);
	printf("Nivel 2: Medio\n");
	gotoxy(48,5);
	printf("Nivel 3: Dificil\n");
	gotoxy(50,6);
	printf("Modo Arcade\n");
	
	while(aceptar != 13)
	{
		aceptar = getch();
		if (aceptar == 72 && mostrar > 1)
			{
			mostrar -= 1;
			gotoxy(45,pos);
			printf("  ");
			pos -= 1;
			}
		if (aceptar == 80 && mostrar < 4)
			{
			mostrar += 1;
			gotoxy(45,pos);
			printf("  ");
			pos += 1;
			}
		gotoxy(45,pos);
		printf("->");
	}

	system("cls");
	
	gotoxy(46,1);
	printf("SOKOBAN PUNTUACIONES\n");

	if (mostrar == 1)
	{
		for (i = 0; i < 3; i++)
		{
			gotoxy(53, j);
			printf("%s %d", facil.nombre[i], facil.puntaje[i]);
			j += 1;
		}
	}
	if (mostrar == 2)
	{
		for (i = 0; i < 3; i++)
		{
			gotoxy(53, j);
			printf("%s %d", medio.nombre[i], medio.puntaje[i]);
			j += 1;
		}
	}
	if (mostrar == 3)
	{
		for (i = 0; i < 3; i++)
		{
			gotoxy(53, j);
			printf("%s %d", dificil.nombre[i], dificil.puntaje[i]);
			j += 1;
		}
	}
	if (mostrar == 4)
	{
		for (i = 0; i < 3; i++)
		{
			gotoxy(53, j);
			printf("%s %d", arcade -> nombre[i], arcade -> puntaje[i]);
			j += 1;
		}
	}
	sleep(5);
	system("cls");
}


int ganar(int mapa[][19], int nvl)
{
	int i, j, cont = 0;
	if (nvl == 1)
	{
		for (i = 6; i <= 8; i++)
			for(j = 16; j <= 17; j++)
			{
				if(mapa[i][j] == 0)
					mapa[i][j] = 12;
				if(mapa[i][j] == 6)
					cont += 1;
			}
		if(cont == 6)
			return 1;
	}
	if(nvl == 2)
	{
		for (i = 6; i <= 8; i++)
			for(j = 1; j <= 4; j++)
			{
				if(i == 7 && j == 1)
					continue;
				if(mapa[i][j] == 0)
					mapa[i][j] = 12;
				if(mapa[i][j] == 6)
					cont += 1;
			}
		if(cont == 11)
			return 1;
	}
	if(nvl == 3)
	{
		for (i = 1; i <= 5; i++)
			for(j = 14; j <= 17; j++)
			{
				if(mapa[i][j] == 0)
					mapa[i][j] = 12;
				if(mapa[i][j] == 6)
					cont += 1;
			}
		if(cont == 20)
			return 1;
	}
	return 0;
}


void registrar_Puntaje(struct puntuaciones *p, int cont, int nvl)
{
	int i, j, k;
	char h[4];
	system("cls");
	textcolor(15);
	gotoxy(50,12);
	if (nvl == 1)
		printf("NIVEL 1 COMPLETADO");
	if (nvl == 2)
		printf("NIVEL 2 COMPLETADO");
	if (nvl == 3)
		printf("NIVEL 3 COMPLETADO");
	if (nvl == 4)
		printf("MODO ARCADE COMPLETADO");
	gotoxy(45,13);
	printf("Cantidad de movimientos: %d", cont);
	gotoxy(45,20);
	printf("Ingresa Nombre (3 Caracteres)\n");
	gotoxy(57,21);
	fflush(stdin);
	fgets(h, 4, stdin);
	if(cont <  p -> puntaje[1])
	{
		k = 1;
	}
	if (cont < p -> puntaje[0])
	{
		k = 0;
	}

	for (i = 0; i < 3; ++i)
	{
		if (cont < p -> puntaje[i] || p -> puntaje[i] == 0)
		{
			if(cont < p -> puntaje[i])
			{
				for(j = 2; j > k; j--)
				{
					strcpy(p -> nombre[j], p -> nombre[j - 1]);
					p -> puntaje[j] = p -> puntaje[j - 1];
				}
			}
			strcpy(p -> nombre[i], h);
			p -> puntaje[i] = cont;
			printf("%s", p -> nombre[i]);
			system("cls");
			return;
		}
	}
	system("cls");
}


// NO TOCAR POR NADA, PD GRACIAS POR ESTA FUNCIÓN PROFE, SIRVIO SU CARPETA MINROD
void setCursorVisible(BOOL visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = visible;
	cursor.dwSize = 20;

	SetConsoleCursorInfo(console, &cursor);
}

//ESTE MENOS
void  dormir(float seconds)
{
  DWORD miliSeconds=seconds*1000;
  Sleep(miliSeconds);
}
