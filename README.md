# Videojuego - Computación Gráfica

## Descripción del Juego
1. Consiste en un mundo en 3D por el cual nos navegaremos, exactamente entre distintos cuartos dentro de un mapa construido.
2. El contenido de las salas es generado aleatoriamente ( enemigos, tesoro, llave dorada, entrada, salida)
3. A la salida se pasa al siguiente nivel con la llave dorada
4. El juego se finaliza tras pasar la salida del tercer nivel con la llave dorada.

## Compilar
### Dependencias
- OpenGL (Open Graphics Library)
- FreeImage (FreeImage is an Open Source library project for developers who would like to support popular graphics image )
- Glut (OpenGL Utility Toolkit)
- GLU (GLU is the OpenGL Utility Library)
- GLM (OpenGL Mathematics (GLM) is a header only C++ mathematics library for graphics software)
- SFML (Simple and Fast Multimedia Library)

### Makefile

```
$ cd videogame	// ir a la carpeta del juego
$ make			// correr la sentencia make
$ ./main		// ejecutar el programa
```