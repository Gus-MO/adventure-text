add_library(Scenes Scenes.cpp)

target_include_directories(
	                   Scenes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
			   Scenes PRIVATE "/usr/local/include/python3.10d"
			   Scenes PRIVATE "../Items"
                          )

list(APPEND EXTRA_LIBS Items)


target_compile_options(AdvPython PRIVATE "-Wno-unused-result -Wsign-compare -Wall") #-g -Og


target_compile_options(Scenes PRIVATE "-Wno-unused-result -Wsign-compare -Wall") #-g -Og

link_directories(
	         Scenes PRIVATE "/usr/local/lib/python3.10/config-3.10d-x86_64-linux-gnu"
	         Scenes PRIVATE "/usr/local/lib"
		 )

target_link_libraries(
	              Scenes 
		      PUBLIC "${EXTRA_LIBS}"
		      PRIVATE "-lpython3.10d -lcrypt -lpthread -ldl  -lutil -lm -lm -lncurses"
		     )


install(TARGETS Scenes DESTINATION libs/AdvText)
install(FILES Scenes.hpp DESTINATION include/AdvText)
