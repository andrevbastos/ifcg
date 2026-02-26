include(FetchContent)

# --- Dependências de Sistema ---
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 CONFIG REQUIRED)
find_package(glm 0.9.9 REQUIRED)

# --- GoogleTest (Para a pasta tests/) ---
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)