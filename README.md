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

### Para crear el makefile, ir a la carpeta build y hacer:
```sh
cmake .
```

### Compilación:
El ejecutable del cliente se creará en la carpeta build.
```sh
make
```

### Ejecución:
Es necesario haber ejecutado el servidor anteriormente.
```sh
./client {IP} {Puerto}
```
Para ejecutar localmente:
```sh
./client localhost 8080
```

