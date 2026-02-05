# Coleta todos os sources da engine, EXCETO o main.cpp
file(GLOB_RECURSE IFCG_CORE_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/ifcg/*.cpp"
)
# Adiciona o GLAD manualmente (arquivo .c)
list(APPEND IFCG_CORE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/glad/glad.c")

# Cria a biblioteca estática com a lógica da Engine
add_library(ifcg_core STATIC ${IFCG_CORE_SOURCES})

if(NOT MSVC)
    set_source_files_properties(glad/glad.c PROPERTIES COMPILE_FLAGS "-Wno-pedantic")
endif()

target_include_directories(ifcg_core PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/glad
)

# Definições de exportação necessárias para o GLAD/Engine
target_compile_definitions(ifcg_core PUBLIC GLAD_GLAPI_EXPORT PRIVATE GLAD_GLAPI_EXPORT_BUILD)

# Linka as bibliotecas necessárias para o core da engine
target_link_libraries(ifcg_core PUBLIC
    OpenGL::GL
    glfw
    glm::glm
    PRIVATE
    stb_image_lib
)

# O Executável final fica no src e linka com o core
add_executable(ifcg main.cpp)
target_link_libraries(ifcg PRIVATE ifcg_core)

# --- Pós-Build: Recursos e DLLs ---
if (WIN32)
    add_custom_command(TARGET ifcg POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:ifcg>
        $<TARGET_FILE_DIR:ifcg>
        COMMAND_EXPAND_LISTS
    )
endif()

add_custom_command(TARGET ifcg POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:ifcg>/resources
    COMMENT "Sincronizando resources para o diretório bin..."
)