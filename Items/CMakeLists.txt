add_library(Items Items.cpp)

target_include_directories(Items
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                           )

install(TARGETS Items DESTINATION libs/AdvText)
install(FILES Items.hpp DESTINATION include/AdvText)
