![jazzJackRabbit](jazzJackRabbit.jpeg)
# Jazz Jackrabbit 2

## Indice 
  - [Compilación](#Compilación)
  - [Ejecución](#Ejecución)
  - [Instrucciones de juego](#Instrucciones_del_juego)
  - [Instalaciones](#Instalaciones)
  

## Compilación

### Dependencias
* [SDL2](SDL2:) (desarrollado con la version )
* [SDL2_image](SDL2_image:), [SDL2_mixer](SDL_mixer:)
* Qt5 (desarrollado con la version 5.15.3)
* [yaml-cpp](yaml-cpp:)
* [PKG-Config](PKG-Config:)


### Comandos
#### Cliente
Para compilar en el cliente:
* Navegar hacia la carpeta "_build" dentro de "client_src" y ejecutar el comando: ```sh ./client {IP} {Puerto} ```
* Una vez que termine, correr el comando ```sh make ```

#### Servidor
Para compilar en el servidor:
* Navegar hacia la carpeta "_build" dentro de "server_src" y ejecutar el comando: ```sh cmake .```
* Una vez que termine, correr el comando ```make```


## Ejecución:
#### Servidor
El ejecutable en el servidor es _./server_, y para ejecutarlo se agrega pasando por parámetro el puerto:
```sh
./server {Puerto}
```
Para ejecutar localmente:
```sh
./server 8080
```

#### Cliente
Para ejecutar el cliente es necesario haber ejecutado el servidor anteriormente. Su ejecutable es _./client_, y se ejecuta dando la IP y el Puerto:
```sh
./client {IP} {Puerto}
```
Para ejecutar localmente:
```sh
./client localhost 8080
```

## Instrucciones del Juego
### Objetivo
El juego consiste en hacer la mayor cantidad de puntos. Las formas de conseguir puntos es:
- Eliminando enemigos
- Recogiendo Monedas o Gemas

### Controles
* Flecha `→`: mueve el jugador hacia la derecha
* Flecha `←`: mueve el jugador hacia la izquierda
* Barra espaciadora ` `: el jugador salta
* Letra `D`: para disparar
* Letra `C`: para cambiar de arma
* Letra `A`: ataque especial
* Tecla `Ctrl`: para correr

## Instalaciones
* ##### SDL2:
```sh
sudo apt-get install libsdl2-dev_
```
* ##### SDL2_image:
```sh
sudo apt-get install libsdl2-image-dev_
```
* ##### SDL2_mixer:
```sh
comando instalacion mixer
```
* ##### Qt5:
```sh
  comando instalacion Qt5
```
* ##### yaml-cpp:
```sh
comando instalacion yaml-cpp
```
* ##### PKG-Config:
```sh
sudo apt-get install pkg-config_
```
