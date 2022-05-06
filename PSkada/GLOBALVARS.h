#pragma once

//Zmienne globalne, dodac ten plik to kazdego skryptu

//Bool czy gra jest aktywna
char running;

//Numer sceny, ustala scene/swiat koturego imput, fizyka, i rysowania ma byc aktywne
char sceneNumber;

//Rozmiar okna
int displayWidth, displayHeight, displayX, displayY;
#define aspectRatio ((double)16.0/9.0)