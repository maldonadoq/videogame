#ifndef _GENERAR_NIVEL_H_
#define _GENERAR_NIVEL_H_

#include <vector>
#include <random>
#include <list>

struct Coord2D
{
    Coord2D();
    Coord2D(int x, int y);
    void imprimir();
    bool operator==(Coord2D c);

    int x, y;
};

struct ParCoord2D
{
    ParCoord2D(Coord2D c1, Coord2D c2);
    void imprimir();

    Coord2D c1, c2;
};

void imprimir_lista_Coord2D(std::list<Coord2D> &l1);
void imprimir_lista_ParCoord2D(std::list<ParCoord2D> &l1);
void imprimir_matriz_enteros(std::vector<std::vector<int> > &m, int w, int h);
void insertar_posibles_puertas(std::vector<std::vector<int> > &cuartos, std::list<ParCoord2D> &puertas_posibles,
                               int w, int h, int x, int y);
void elegir_cuarto_aleatorio(std::vector<std::vector<int> > &cuartos, std::list<ParCoord2D> &puertas_posibles,
                             std::list<Coord2D> &cuartos_finales, std::list<ParCoord2D> &puertas, std::mt19937 &rng, int &x1, int &y1);
void generar_nivel_aleatorio(int anchura, int altura, int n_cuartos, int n_tesoros, std::vector<std::vector<int> > &cuartos,
                             std::list<ParCoord2D> &puertas, std::mt19937 &rng);


#endif