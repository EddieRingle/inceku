cmake_minimum_required (VERSION 2.4)

if(COMMAND cmake_policy)
cmake_policy(VERSION 2.6)
endif(COMMAND cmake_policy)

project (Inceku)

set(CMAKE_BUILD_TYPE RelWithDebInfo)

IF(CMAKE_COMPILER_IS_GNUCXX)
    EXEC_PROGRAM(
    	${CMAKE_CXX_COMPILER} 
        ARGS 			--version 
        OUTPUT_VARIABLE _compiler_output)
    STRING(REGEX REPLACE ".* ([0-9]\\.[0-9]\\.[0-9]) .*" "\\1" 
           gcc_compiler_version ${_compiler_output})
    #MESSAGE("GCC Version: ${gcc_compiler_version}")
    IF(gcc_compiler_version MATCHES "4\\.[0-9]\\.[0-9]")
        SET(PCHSupport_FOUND TRUE)
    ELSE(gcc_compiler_version MATCHES "4\\.[0-9]\\.[0-9]")
        IF(gcc_compiler_version MATCHES "3\\.4\\.[0-9]")
            SET(PCHSupport_FOUND TRUE)
        ENDIF(gcc_compiler_version MATCHES "3\\.4\\.[0-9]")
    ENDIF(gcc_compiler_version MATCHES "4\\.[0-9]\\.[0-9]")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

MACRO(ADD_PRECOMPILED_HEADER _targetName _header _source)
IF(MSVC)
	STRING(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" _headerName "${_header}")
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Yu\"${_headerName}\"")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yu\"${_headerName}\"")
	GET_FILENAME_COMPONENT(_sourceFile ${_source} NAME)
	set_source_files_properties("${_sourceFile}"
		COMPILE_FLAGS "/Yc\"${_headerName}\""
	)
ENDIF(MSVC)
IF(APPLE)
	SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -F/System/Library/PrivateFrameworks -framework CHUD")
ENDIF(APPLE)
IF(CMAKE_COMPILER_IS_GNUCXX AND NOT XCODE)
	IF(NOT CMAKE_BUILD_TYPE)
		MESSAGE(FATAL_ERROR 
			"This is the ADD_PRECOMPILED_HEADER macro. " 
			"You must set CMAKE_BUILD_TYPE!"
		)
	ENDIF(NOT CMAKE_BUILD_TYPE)

	GET_FILENAME_COMPONENT(_name ${_header} NAME)
	GET_FILENAME_COMPONENT(_path ${_header} PATH)
	SET(_outdir "${CMAKE_CURRENT_BINARY_DIR}/${_name}.gch")
	SET(_output "${_outdir}/${CMAKE_BUILD_TYPE}.c++")

	ADD_CUSTOM_COMMAND(
		OUTPUT ${_outdir}
		COMMAND mkdir ${_outdir} # TODO: {CMAKE_COMMAND} -E ... 
	)
	#MAKE_DIRECTORY(${_outdir})
    
	STRING(TOUPPER "CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}" _flags_var_name)
	SET(_compile_FLAGS ${${_flags_var_name}})
	GET_DIRECTORY_PROPERTY(_directory_flags INCLUDE_DIRECTORIES)

	SET(_CMAKE_CURRENT_BINARY_DIR_included_before_path FALSE)
	FOREACH(item ${_directory_flags})
		IF(${item}  STREQUAL ${_path} AND NOT _CMAKE_CURRENT_BINARY_DIR_included_before_path )
			MESSAGE(FATAL_ERROR 
				"This is the ADD_PRECOMPILED_HEADER macro. "
				"CMAKE_CURRENT_BINARY_DIR has to mentioned at INCLUDE_DIRECTORIES's argument list before ${_path}, where ${_name} is located"
			)	
		ENDIF(${item}  STREQUAL ${_path} AND NOT _CMAKE_CURRENT_BINARY_DIR_included_before_path )
	
		IF(${item}  STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
			SET(_CMAKE_CURRENT_BINARY_DIR_included_before_path TRUE)
		ENDIF(${item}  STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
	
		LIST(APPEND _compile_FLAGS "-I${item}")
	ENDFOREACH(item)

	GET_DIRECTORY_PROPERTY(_directory_flags DEFINITIONS)
	LIST(APPEND _compile_FLAGS ${_directory_flags})
	LIST(APPEND _compile_FLAGS ${CMAKE_CXX_FLAGS} )

	SEPARATE_ARGUMENTS(_compile_FLAGS)
	#MESSAGE("_compiler_FLAGS: ${_compiler_FLAGS}")
	#message(${_compile_FLAGS} )
	#message("COMMAND ${CMAKE_CXX_COMPILER} ${_compile_FLAGS} -x c++-header -o ${_output} ${_header}")

	ADD_CUSTOM_COMMAND(
		OUTPUT ${_output} 	
		COMMAND ${CMAKE_CXX_COMPILER}
				${_compile_FLAGS}
				-x c++-header
				-o ${_output} 
				${_header}
		DEPENDS ${_header} ${_outdir}
	)
   	ADD_CUSTOM_TARGET(${_targetName}_gch 
		DEPENDS	${_output} 	
	)
	ADD_DEPENDENCIES(${_targetName} ${_targetName}_gch)
	ADD_DEPENDENCIES(${_targetName}_gch BuildNumber)
	SET_TARGET_PROPERTIES(${_targetName} 
		PROPERTIES	
		COMPILE_FLAGS "-include ${_header} -Winvalid-pch"
	)
ENDIF(CMAKE_COMPILER_IS_GNUCXX AND NOT XCODE)
ENDMACRO(ADD_PRECOMPILED_HEADER)

MACRO(ADD_FLAG where flag)
	SET(${where} "${flag} ${${where}}")
ENDMACRO(ADD_FLAG)

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++98 -fno-rtti -fno-exceptions -Wall -Wno-long-long -pedantic -Icontrib/crisscross/source")
	if(NOT CYGWIN)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -rdynamic")
	endif(NOT CYGWIN)
endif(CMAKE_COMPILER_IS_GNUCXX)

add_subdirectory(contrib/crisscross)

add_executable(Inceku header.cpp main.cpp config.cpp webserver.cpp logger.cpp)
add_precompiled_header(Inceku ${CMAKE_CURRENT_SOURCE_DIR}/header.h ${CMAKE_CURRENT_SOURCE_DIR}/header.cpp)

target_link_libraries (Inceku CrissCross)
