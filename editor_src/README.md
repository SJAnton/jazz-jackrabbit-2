# Editor
### Instalación de dependencias:
Con los siguientes comandos se pueden instalar las dependencia necesarias:
```sh
sudo apt install qtcreator qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
```
```sh
sudo apt-get install libyaml-cpp-dev
```

### Para crear el makefile del editor, ir a la carpeta build (si no existe crearla) y hacer:
```sh
cmake ..
```

### Compilación:
Dentro de la carpeta build, hacer:
```sh
make
```
Esto creara el ejecutable del editor.

### Ejecución:
Para ejecutar el editor hacer:
```sh
./editor
```
