add_library(Characters Characters.cpp)

target_include_directories(Characters
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                           )

install(TARGETS Characters DESTINATION libs/AdvText)
install(FILES Characters.hpp DESTINATION include/AdvText)
