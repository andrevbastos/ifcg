include(FetchContent)

# --- Dependências de Sistema ---
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 CONFIG REQUIRED)
find_package(glm 0.9.9 REQUIRED)

# --- STB Image ---
FetchContent_Declare(
  stb
  GIT_REPOSITORY https://github.com/nothings/stb.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(stb)

# Criamos a lib estática para a implementação da STB
add_library(stb_image_lib STATIC src/stb.cpp)
target_include_directories(stb_image_lib PUBLIC ${stb_SOURCE_DIR})

# --- GoogleTest (Para a pasta tests/) ---
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)