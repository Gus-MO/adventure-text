add_library(Screen Screen.cpp)

target_include_directories(Screen
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                           )
target_link_libraries(Screen PRIVATE "-lncurses")

install(TARGETS Screen DESTINATION libs/AdvText)
install(FILES Screen.hpp DESTINATION include/AdvText)
