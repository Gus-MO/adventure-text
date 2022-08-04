add_library(AdvPython AdvPython.cpp)

target_include_directories(
	                   AdvPython INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
			   AdvPython PRIVATE "/usr/local/include/python3.10d" 
			   AdvPython PRIVATE "../Scenes"
                          )

list(APPEND EXTRA_LIBS Scenes)

target_compile_options(AdvPython PRIVATE "-Wno-unused-result -Wsign-compare -Wall") #-g -Og

#set(PySource "$ENV{HOME}/.AdvText/AdvPython/")

#target_compile_definitions(PySource PRIVATE "PySource=\"${PySource}\"")

link_directories(
	         AdvPython PRIVATE "/usr/local/lib/python3.10/config-3.10d-x86_64-linux-gnu"
		 AdvPython PRIVATE "/usr/local/lib"
		 )
target_link_libraries(
	              AdvPython
		      PUBLIC "${EXTRA_LIBS}"
	              PRIVATE "-lpython3.10d -lcrypt -lpthread -ldl  -lutil -lm -lm"
		     )

install(TARGETS AdvPython DESTINATION libs/AdvText)
install(FILES AdvPython.hpp DESTINATION include/AdvText)
install(FILES json-parser.py character-parser.py DESTINATION include/AdvText/PySource)

