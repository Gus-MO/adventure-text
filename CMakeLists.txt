cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(AdventureText VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add librarys
add_subdirectory(Actions)
list(APPEND EXTRA_LIBS Actions)

add_subdirectory(AdvPython)
list(APPEND EXTRA_LIBS AdvPython)

add_subdirectory(Characters)
list(APPEND EXTRA_LIBS Characters)

add_subdirectory(Game)
list(APPEND EXTRA_LIBS Game)

add_subdirectory(Items)
list(APPEND EXTRA_LIBS Items)

add_subdirectory(Scenes)
list(APPEND EXTRA_LIBS Scenes)

add_subdirectory(Screen)
list(APPEND EXTRA_LIBS Screen)

set(AdventuresPath "$ENV{HOME}/.AdvText/Adventures/" CACHE STRING "Custom path for adventures. Default $ENV{HOME}/.AdvText/Adventures")

add_executable(AdventureText adv_game.cpp main_enums.cpp main_functions.cpp)

# Librarys link
target_link_libraries(AdventureText
	              PUBLIC "${EXTRA_LIBS}"
		      PRIVATE "-lpython3.10d -lcrypt -lpthread -ldl  -lutil -lm -lm -lncurses"
		     )

target_include_directories(
			   AdventureText PRIVATE "/usr/local/include/python3.10d"
                          )

target_compile_options(AdventureText PRIVATE "-Wno-unused-result -Wsign-compare -Wall") #-g -Og

target_compile_definitions(AdventureText PRIVATE "AdventuresPath=\"${AdventuresPath}\"")

link_directories(
	         AdventureText PRIVATE "/usr/local/lib/python3.10/config-3.10d-x86_64-linux-gnu"
		 AdventureText PRIVATE "/usr/local/lib"
		 )

# Executable
install(TARGETS AdventureText DESTINATION bin)
install(FILES main_classes.hpp main_enums.hpp DESTINATION include/AdvText)
install(FILES Adventures/Example/Example.json DESTINATION AdventuresPath/Example)
