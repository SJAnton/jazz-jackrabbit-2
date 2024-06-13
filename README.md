# Cliente
### Instalación de dependencias:
Las dependencias utilizadas son PKG-Config, SDL2 y SDL2-Image.
```sh
sudo apt-get install pkg-config
```
```sh
sudo apt-get install libsdl2-dev
```
```sh
sudo apt-get install libsdl2-image-dev
```
##Server
### Para crear el makefile del server, ir a la carpeta server_src/build y hacer:
```sh
cmake .
```
y luego, para crear el ejecutable hacer:
```sh
make
```
Esto creara el ejecutable del server.

### Ejecución:
```sh
./server {Puerto}
```
Para ejecutar localmente:
```sh
./server 8080
```
##Cliente
### Para crear el makefile del cliente, ir a la carpeta build y hacer:
```sh
cmake ..
```

### Compilación:
Luego, dentro de la misma carpeta, hacer:
```sh
make
```
Esto creara el ejecutable cel client.

### Ejecución:
Es necesario haber ejecutado el servidor anteriormente.
```sh
./client {IP} {Puerto}
```
Para ejecutar localmente:
```sh
./client localhost 8080
```
