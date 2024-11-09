# Enable compiler flags for certain build configurations
if(NOT ${CMAKE_BUILD_TYPE} MATCHES Debug)
    list(
        APPEND CompilerFlags 
        "/O2"
    )
endif()

# Enable compiler flags for all builds
list(
	APPEND CompilerFlags 

	"/Wall"
	"/permissive-"
    "/sdl"    
    "/QSpectre"
    "/QSpectre-load"
)

list(
    APPEND LinkerFlags

    "/guard:cf"
    "/guard:ehcont"
    "/DYNAMICBASE"
    "/HIGHENTROPYVA"
)

# Enable sanitizers if chosen

if(ENABLE_SANITIZER)

string(CONCAT sanitizers "/fsanitize=" ${ENABLE_SANITIZER})

    list(
            APPEND CompilerFlags

            ${sanitizers}
        )
endif()