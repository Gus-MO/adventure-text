add_library(Game Game.cpp)

target_include_directories(
	                   Game INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
			   Game PRIVATE "/usr/local/include/python3.10d"
			   Game PRIVATE "../Actions"
			   Game PRIVATE "../Scenes"
                          )

list(APPEND EXTRA_LIBS Actions)
list(APPEND EXTRA_LIBS Scenes)

target_compile_options(Game PRIVATE "-Wno-unused-result -Wsign-compare -Wall") #-g -Og

link_directories(
	         Game PRIVATE "/usr/local/lib/python3.10/config-3.10d-x86_64-linux-gnu"
		 Game PRIVATE "/usr/local/lib"
		 )
target_link_libraries(
	              Game 
		      PUBLIC "${EXTRA_LIBS}"
		      PRIVATE "-lpython3.10d -lcrypt -lpthread -ldl  -lutil -lm -lm -lncurses"
		     )

install(TARGETS Game DESTINATION libs/AdvText)
install(FILES Game.hpp DESTINATION include/AdvText)
