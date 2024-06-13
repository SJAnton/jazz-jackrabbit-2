# Servidor
### Instalación de dependencias:
```sh
sudo apt-get install libyaml-cpp-dev
```

### Makefile:
Ir a la carpeta build y hacer
```sh
cmake .
```

### Compilación:
El ejecutable del cliente se creará en la carpeta build.
```sh
make
```

### Ejecución:
```sh
./server {Puerto}
```
Para ejecutar localmente:
```sh
./server 8080
```
