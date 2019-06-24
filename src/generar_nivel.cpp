/*
Contiene el codigo necesario para generar un nivel
aleatorio consistente (con una sala final, una inicial,
un numero especifico de tesoros, y llaves de tesoros, y una 
sala para la llave de la salida)
*/

#include "../inc/generar_nivel.h"

#include <iostream>
#include <vector>
#include <random>
#include <list>
#include <algorithm>

/*
Cuartos:
Vacio - 0
Sala normal - 1
Tesoro - 2
Llave dorada - 3
Entrada - 4
Salida - 5
*/


Coord2D::Coord2D()
{
    this->x = 0;
    this->y = 0;
}
Coord2D::Coord2D(int x, int y)
{
    this->x = x;
    this->y = y;
}
void Coord2D::imprimir()
{
    std::cout << "(" << x << ", " << y << ")";
}
bool Coord2D::operator==(Coord2D c)
{
    if (this->x == c.x && this->y == c.y)
        return true;
    else
        return false;
}



ParCoord2D::ParCoord2D()
{
    
}

ParCoord2D::ParCoord2D(Coord2D c1, Coord2D c2)
{
    this->c1 = c1;
    this->c2 = c2;
}
void ParCoord2D::imprimir()
{
    std::cout << "(";
    c1.imprimir();
    std::cout << ", ";
    c2.imprimir();
    std::cout << ")";
}




void imprimir_lista_Coord2D(std::list<Coord2D> &l1)
{
    std::cout << "{";
    for (auto it = l1.begin(); it != l1.end(); ++it)
    {
        (*it).imprimir();
        std::cout << "; ";
    }
    std::cout << "}\n";
}

void imprimir_lista_ParCoord2D(std::list<ParCoord2D> &l1)
{
    std::cout << "{";
    for (auto it = l1.begin(); it != l1.end(); ++it)
    {
        (*it).imprimir();
        std::cout << "; ";
    }
    std::cout << "}\n";
}

void imprimir_matriz_enteros(std::vector<std::vector<int> > &m, int w, int h)
{
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            std::cout << m[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void insertar_posibles_puertas(std::vector<std::vector<int> > &cuartos, std::list<ParCoord2D> &puertas_posibles, int w, int h, int x, int y)
{
    Coord2D c1(x, y);
    int y_new = y - 1;
    int x_new = x;
    Coord2D c2(x_new, y_new);
    if (y_new >= 0 && cuartos[y_new][x_new] == 0)
    {
        puertas_posibles.push_back(ParCoord2D(c1, c2));
    }

    y_new = y;
    x_new = x - 1;
    c2 = Coord2D(x_new, y_new);
    if (x_new >= 0 && cuartos[y_new][x_new] == 0)
    {
        puertas_posibles.push_back(ParCoord2D(c1, c2));
    }

    x_new = x + 1;
    c2 = Coord2D(x_new, y_new);
    if (x_new <= w-1 && cuartos[y_new][x_new] == 0)
    {
        puertas_posibles.push_back(ParCoord2D(c1, c2));
    }

    y_new = y + 1;
    x_new = x;
    c2 = Coord2D(x_new, y_new);
    if (y_new <= h-1 && cuartos[y_new][x_new] == 0)
    {
        puertas_posibles.push_back(ParCoord2D(c1, c2));
    }
}


void elegir_cuarto_aleatorio(std::vector<std::vector<int> > &cuartos, std::list<ParCoord2D> &puertas_posibles, std::list<Coord2D> &cuartos_finales,
                      std::list<ParCoord2D> &puertas, std::mt19937 &rng, int &x1, int &y1)
{
    std::uniform_int_distribution<int> uni1(0, puertas_posibles.size() - 1);
    int pos_sig_puerta = uni1(rng);
    auto it = std::next(puertas_posibles.begin(), pos_sig_puerta);
    ParCoord2D next_door = *it;
    puertas_posibles.erase(it);
    Coord2D from_room = next_door.c1;
    Coord2D to_room = next_door.c2;
    x1 = to_room.x;
    y1 = to_room.y;
    for (auto it1 = puertas_posibles.begin(); it1 != puertas_posibles.end(); )
    {
        if ((*it1).c2 == to_room)
        {
            auto it2 = it1;
            ++it1;
            puertas_posibles.erase(it2);
        }
        else
        {
            ++it1;
        }
        
    }
    cuartos[to_room.y][to_room.x] = 1;   //marcar cuarto como sala normal
    cuartos_finales.remove(from_room);
    cuartos_finales.push_back(to_room);
    puertas.push_back(next_door);
}

void generar_nivel_aleatorio(int anchura, int altura, int n_cuartos, int n_tesoros, std::vector<std::vector<int> > &cuartos,
                             std::list<ParCoord2D> &puertas, std::mt19937 &rng)
{
    cuartos = std::vector<std::vector<int> >(altura, std::vector<int>(anchura, 0));
    
    std::uniform_int_distribution<int> uni1(0, anchura - 1);
    std::uniform_int_distribution<int> uni2(0, altura - 1);

    int x1 = uni1(rng);
    int y1 = uni2(rng);

    std::list<ParCoord2D> puertas_posibles;
    std::list<Coord2D> cuartos_finales;

    cuartos[y1][x1] = 1;
    Coord2D entrance(x1, y1);
    cuartos_finales.push_back(entrance);
    insertar_posibles_puertas(cuartos, puertas_posibles, anchura, altura, x1, y1);
    
    /*
    std::cout << "puertas_posibles = "; 
    imprimir_lista_ParCoord2D(puertas_posibles);
    std::cout << "puertas = "; 
    imprimir_lista_ParCoord2D(puertas);
    std::cout << "cuartos_finales = ";
    imprimir_lista_Coord2D(cuartos_finales);
    std::cout << "cuartos =\n";
    imprimir_matriz_enteros(cuartos, anchura, altura);
    std::cout << "\n";*/

    for (int i = 0; i < n_cuartos - 1; ++i)
    {
        elegir_cuarto_aleatorio(cuartos, puertas_posibles, cuartos_finales, puertas, rng, x1, y1);
        insertar_posibles_puertas(cuartos, puertas_posibles, anchura, altura, x1, y1);  
        
        /*
        std::cout << "puertas_posibles = "; 
        imprimir_lista_ParCoord2D(puertas_posibles);
        std::cout << "puertas = "; 
        imprimir_lista_ParCoord2D(puertas);
        std::cout << "cuartos_finales = ";
        imprimir_lista_Coord2D(cuartos_finales);
        std::cout << "cuartos =\n";
        imprimir_matriz_enteros(cuartos, anchura, altura);
        std::cout << "\n";*/
    }

    cuartos[entrance.y][entrance.x] = 4;  //entrada

/*
La salida se posiciona siempre en una sala que es
un end_room, por ejemplo, si los pasadizo de las salas
lo imaginamos como un arbol, la salida siempre estaria
en una hoja.
*/
    Coord2D exit = cuartos_finales.back();
    cuartos_finales.pop_back();
    cuartos[exit.y][exit.x] = 5;          //salida


/*
La llave dorada puede estar o no en una hoja del arbol
de salas.
*/
    auto it_d = puertas.rbegin();
    if (cuartos_finales.empty() == false)
    {
        Coord2D golden_key = cuartos_finales.back();  //llave dorada
        cuartos_finales.pop_back();
        cuartos[golden_key.y][golden_key.x] = 3;
    }
    else
    {    
        for ( ; it_d != puertas.rend(); ++it_d)
        {
            if (cuartos[(*it_d).c2.y][(*it_d).c2.x] == 1)
            {
                cuartos[(*it_d).c2.y][(*it_d).c2.x] = 3;  //llave dorada
                break;
            }
        }
    }

/*
Los tesoros van a estar en cualquier sala aleatoriamente,
pero de preferencia van a estar alejados de la entrada.
*/
    for (int i = 0; i < n_tesoros; ++i)
    {
        for ( ; it_d != puertas.rend(); ++it_d)
        {
            if (cuartos[(*it_d).c2.y][(*it_d).c2.x] == 1)
            {
                cuartos[(*it_d).c2.y][(*it_d).c2.x] = 2;  //tesoro
                break;
            }
        }
    }

    /* 
    std::cout << "cuartos =\n";
    imprimir_matriz_enteros(cuartos, anchura, altura);
    std::cout << "\n";*/
}