#include "dialogo.h"
#include <SDL.h>
#include <iostream>

using namespace std;

const short int ANCHO_VENTANA = 454;
const short int ALTO_VENTANA = 340;
const int TIEMPO_DELAY_IMAGEN_UNO = 3000;
const int TIEMPO_DELAY_IMAGEN_MENU = 5000;

SDL_Window* pVentana = NULL;
SDL_Surface* pSuperficie = NULL;
SDL_Surface* pImagen = NULL;

bool Inicializar();

bool CargarImagen();

bool CargarImagenMENU();

void Cerrar();

void CargarImagenEnMain();

void CargarImagenMENUEnMain();

//-------------------------------------------------------------------------------


int main(int argc, char* args[])
{
	if (!Inicializar())
	{
		cout << "Error al inicializar en main" << endl;
	}

	else
	{
		CargarImagenEnMain();
		CargarImagenMENUEnMain();
	}

	Cerrar();
	return 0;
}


//-------------------------------------------------------------------------------


bool Inicializar()
{
	bool inicializado = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "Error Inicializando Video: " << SDL_GetError() << endl;
		inicializado = false;
	}

	else
	{
		pVentana = SDL_CreateWindow("RPG DRAGON", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO_VENTANA, ALTO_VENTANA,/*SDL_WINDOW_FULLSCREEN &&*/ SDL_WINDOW_SHOWN);
		if (pVentana == NULL)
		{
			cout << "Error al crear la ventana" << endl;
		}

		else
		{
			pSuperficie = SDL_GetWindowSurface(pVentana);
		}
	}
	return inicializado;
}

//-------------------------------------------------------------------------------

bool CargarImagen()
{
	bool inicializado = true;
	pImagen = SDL_LoadBMP("DragonRPGINTRO.bmp");
	if (pImagen == NULL)
	{
		cout << "Error al cargar Imagen1" << endl;
		inicializado = false;
	}
	return inicializado;
}

//-------------------------------------------------------------------------------

bool CargarImagenMENU()
{
	bool inicializado = true;
	pImagen = SDL_LoadBMP("DragonRPGMENU.bmp");
	if (pImagen == NULL)
	{
		cout << "Error al cargar ImagenMENU" << endl;
		inicializado = false;
	}
	return inicializado;
}

//-------------------------------------------------------------------------------

void Cerrar()
{
	SDL_FreeSurface(pImagen);
	pImagen = NULL;

	SDL_DestroyWindow(pVentana);
	pVentana = NULL;

	SDL_Quit();
}

//-------------------------------------------------------------------------------

void CargarImagenEnMain()
{
	if (!CargarImagen())
	{
		cout << "Error al cargar la imagen en main." << endl;
	}

	else
	{
		SDL_BlitSurface(pImagen, NULL, pSuperficie, NULL);
		SDL_UpdateWindowSurface(pVentana);
		SDL_Delay(TIEMPO_DELAY_IMAGEN_UNO);
	}
}

//-------------------------------------------------------------------------------

void CargarImagenMENUEnMain()
{
	if (!CargarImagenMENU())
	{
		cout << "Error al cargar la imagenMENU en main." << endl;
	}

	else
	{
		SDL_BlitSurface(pImagen, NULL, pSuperficie, NULL);
		SDL_UpdateWindowSurface(pVentana);
		SDL_Delay(TIEMPO_DELAY_IMAGEN_MENU);
	}
}