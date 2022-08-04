add_library(Actions Actions.cpp)

target_include_directories(
	                   Actions INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
			   Actions PRIVATE "/usr/local/include/python3.10d"
			   AdvPython PRIVATE "../AdvPython"
                          )

list(APPEND EXTRA_LIBS AdvPython)

target_link_libraries(
	              Actions 
		      PUBLIC "${EXTRA_LIBS}"
		     )

install(TARGETS Actions DESTINATION libs/AdvText)
install(FILES Actions.hpp DESTINATION include/AdvText)
