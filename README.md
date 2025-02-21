# IFCG

## 📦 Dependencies

* CMake 2.8.5+
* OpenGL 3.3+
* GLFW3
* GLM
* Doxygen (Optional)

### Linux

Ubuntu:
```bash
sudo apt-get install cmake
sudo apt-get install libglm-dev
sudo apt-get install libglfw3-dev libglfw3
```

Arch:
```bash
sudo pacman -S cmake
sudo pacman -S glm
sudo pamcan -S glfw
```

### Windows

Download the CMake installer in [https://cmake.org/download/](https://cmake.org/download/)
and install it.

The other dependencies will be installed via vcpkg.
Install the vcpkg:
```bash
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
bootstrap-vcpkg.bat
vcpkg.exe integrate install
```

Install the dependencies
```bash
vcpkg.exe install glm
vcpkg.exe install glfw3
```

## 🔧 Compiling

Clone the repository:
```bash
git clone https://gitlab.com/oederaugusto/ifcg
cd ifcg
mkdir build
cd build
```

### Linux

Compile the project:
```bash
cmake ..
make -j4
```

### Windows

Compile the project (pay attention to the path of the vcpkg.cmake file,
you must change it to your path where you cloned the vcpkg repository):
```bash
cmake -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake ..
cmake --build . --config Release
```

## 📚 Documentation

If you have Doxygen, you can read the documentation using:

### Linux

```bash
make docs
```

## ❓ Help

You can create an Issue or contact the mantainers (authors)

## 👥 Authors
 * João Vitor Espig ([JotaEspig](https://gitlab.com/JotaEspig))
 * TODO

## 🕒 Version History

see [CHANGELOG.md](CHANGELOG.md)

## 📜 License

TODO

## 🙏 Acknowledgments

* [Learn OpenGL](https://github.com/JoeyDeVries/LearnOpenGL)
* [OpenGL course](https://www.youtube.com/watch?v=45MIykWJ-C4&ab_channel=freeCodeCamp.org) - By freeCodeCamp
* [README-Template.md](https://gist.github.com/DomPizzie/7a5ff55ffa9081f2de27c315f5018afc)
