cmake_minimum_required(VERSION 3.27)
project(PacMan)

set(CMAKE_CXX_STANDARD 23)

add_executable(PacMan main.cpp
        Perso.cpp
        Perso.h
        joueur.cpp
        joueur.h
        fantome.cpp
        fantome.h
        ZoneJeu.cpp
        ZoneJeu.h
        Menu.cpp
        Menu.h
        ZoneJeu.cpp
        Menufin.cpp
        Menufin.h
        fantome2.cpp
        fantome2.h)

IF(WIN32)
    target_link_libraries(PacMan -lmingw32 -lallegro-5.0.10-monolith-md-debug)
ELSE()
    INCLUDE_DIRECTORIES(/usr/local/Cellar/allegro/5.2.8.0_2/include)
    LINK_DIRECTORIES(/usr/local/Cellar/allegro/5.2.8.0_2/lib)
    file(GLOB LIBRARIES "/usr/local/Cellar/allegro/5.2.8.0_2/lib/*.dylib")
    message("LIBRARIES = ${LIBRARIES}")
    TARGET_LINK_LIBRARIES(PacMan ${LIBRARIES})
ENDIF(WIN32)