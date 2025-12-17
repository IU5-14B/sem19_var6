cmake_minimum_required(VERSION 3.10)
project(LinearProgrammingSolver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Исходные файлы
set(SOURCES
    src/main.cpp
    src/LinearProgram.cpp
    src/Solver.cpp
)

# Заголовочные файлы
set(HEADERS
    include/LinearProgram.h
    include/Solver.h
)

# Создание исполняемого файла
add_executable(lp_solver ${SOURCES} ${HEADERS})

# Включение директорий
target_include_directories(lp_solver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)