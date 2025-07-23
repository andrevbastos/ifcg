# IFCG

A C ++ and Opengl graphic engine library as part of the IFC - Blumenau computer graphics discipline.
*Uma biblioteca de motor gráfico feito em C++ e OpenGL como parte da disciplina de Computação Gráfica do IFC - Blumenau. (pt-br)*

## 📦 Dependencies

* CMake 2.8.5+
* OpenGL 3.3+
* GLFW3
* GLM
* Doxygen (Optional)

### Installation
**Ubuntu/Debian:**
```bash
sudo apt install cmake libglm-dev libglfw3-dev
```

**Arch:**
```bash
sudo pacman -S cmake glm glfw-x11
```

## 🔧 Compiling

**Clone the repository:**
```bash
git clone https://github.com/andrevbastos/ifcg
cd ifcg
mkdir build
cd build
```

**Compile and run the project:**
```bash
cmake ..
make
./bin/ifcg-app
```

## 🧑‍🏫 Usage

The ([main](tests/main.cpp)) file has some good usage examples. You can alter it and the whole project however you prefer, but when using the current CMakeLists setup remember: ([include](include)) folder must only contain .hpp files, ([src](src)) folder must only contain .cpp files and the entry point will alway be at ([main](tests/main.cpp)).

## 👤 Author

 * André Vitor Bastos ([andrevbastos](https://github.com/andrevbastos))

## 👥 Special Thanks

 * Éder Augusto ([oederaugusto](https://gitlab.com/oederaugusto/))
 * João Vitor Espig ([JotaEspig](https://gitlab.com/JotaEspig))
 * Helder Martins ([imheldermartins](https://github.com/imheldermartins))

## 🙏 Acknowledgments

* [OpenGL course](https://youtube.com/playlist?list=PLPaoO-vpZnumdcb4tZc4x5Q-v7CkrQ6M-&si=ggvK1vKGWtdA4YJm) - by Victor Gordan