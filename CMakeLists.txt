cmake_minimum_required(VERSION 3.13)
project(compiler)

# enable all warnings
if(MSVC)
  add_compile_options(/W3)
else()
  # disable warnings caused by old version of Flex
  add_compile_options(-Wall -Wno-register)
endif()

# find Flex/Bison
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

# generate lexer/parser
file(GLOB_RECURSE L_SOURCES "src/integrate/sysy*.l")
file(GLOB_RECURSE Y_SOURCES "src/integrate/sysy*.y")
if(NOT (L_SOURCES STREQUAL "" AND Y_SOURCES STREQUAL ""))
  string(REGEX REPLACE ".*/(.*)\\.l" "${CMAKE_CURRENT_BINARY_DIR}/\\1.lex.cpp" L_OUTPUTS "${L_SOURCES}")
  string(REGEX REPLACE ".*/(.*)\\.y" "${CMAKE_CURRENT_BINARY_DIR}/\\1.tab.cpp" Y_OUTPUTS "${Y_SOURCES}")
  flex_target(Lexer ${L_SOURCES} ${L_OUTPUTS})
  bison_target(Parser ${Y_SOURCES} ${Y_OUTPUTS})
  add_flex_bison_dependency(Lexer Parser)
endif()

SET(FLEX1 ${FLEX_Lexer_OUTPUTS})
SET(BISON1 ${BISON_Parser_OUTPUT_SOURCE})


file(GLOB_RECURSE L_SOURCES "src/integrate/eeyore*.l")
file(GLOB_RECURSE Y_SOURCES "src/integrate/eeyore*.y")
if(NOT (L_SOURCES STREQUAL "" AND Y_SOURCES STREQUAL ""))
  string(REGEX REPLACE ".*/(.*)\\.l" "${CMAKE_CURRENT_BINARY_DIR}/\\1.lex.cpp" L_OUTPUTS "${L_SOURCES}")
  string(REGEX REPLACE ".*/(.*)\\.y" "${CMAKE_CURRENT_BINARY_DIR}/\\1.tab.cpp" Y_OUTPUTS "${Y_SOURCES}")
  flex_target(Lexer ${L_SOURCES} ${L_OUTPUTS})
  bison_target(Parser ${Y_SOURCES} ${Y_OUTPUTS})
  add_flex_bison_dependency(Lexer Parser)
endif()

SET(FLEX2 ${FLEX_Lexer_OUTPUTS})
SET(BISON2 ${BISON_Parser_OUTPUT_SOURCE})

file(GLOB_RECURSE L_SOURCES "src/integrate/tigger*.l")
file(GLOB_RECURSE Y_SOURCES "src/integrate/tigger*.y")
if(NOT (L_SOURCES STREQUAL "" AND Y_SOURCES STREQUAL ""))
  string(REGEX REPLACE ".*/(.*)\\.l" "${CMAKE_CURRENT_BINARY_DIR}/\\1.lex.cpp" L_OUTPUTS "${L_SOURCES}")
  string(REGEX REPLACE ".*/(.*)\\.y" "${CMAKE_CURRENT_BINARY_DIR}/\\1.tab.cpp" Y_OUTPUTS "${Y_SOURCES}")
  flex_target(Lexer ${L_SOURCES} ${L_OUTPUTS})
  bison_target(Parser ${Y_SOURCES} ${Y_OUTPUTS})
  add_flex_bison_dependency(Lexer Parser)
endif()

SET(FLEX3 ${FLEX_Lexer_OUTPUTS})
SET(BISON3 ${BISON_Parser_OUTPUT_SOURCE})


# project include directories
include_directories(src/integrate)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# all of C/C++ source files
file(GLOB_RECURSE C_SOURCES "src/integrate/*.c")
file(GLOB_RECURSE CXX_SOURCES "src/integrate/*.cpp")
file(GLOB_RECURSE CC_SOURCES "src/integrate/*.cc")
set(SOURCES ${C_SOURCES} ${CXX_SOURCES} ${CC_SOURCES}
            ${FLEX1} ${FLEX2} ${FLEX3} ${BISON1} ${BISON2} ${BISON3})

# executable
add_executable(compiler ${SOURCES})
set_target_properties(compiler PROPERTIES C_STANDARD 11 CXX_STANDARD 17)


# cmake_minimum_required(VERSION 3.13)
# project(compiler)

# # enable all warnings
# if(MSVC)
#   add_compile_options(/W3)
# else()
#   # disable warnings caused by old version of Flex
#   add_compile_options(-Wall -Wno-register)
# endif()

# # find Flex/Bison
# find_package(FLEX REQUIRED)
# find_package(BISON REQUIRED)

# # generate lexer/parser
# file(GLOB_RECURSE L_SOURCES "src/integrate/*.l")
# file(GLOB_RECURSE Y_SOURCES "src/integrate/*.y")
# if(NOT (L_SOURCES STREQUAL "" AND Y_SOURCES STREQUAL ""))
#   string(REGEX REPLACE ".*/(.*)\\.l" "${CMAKE_CURRENT_BINARY_DIR}/\\1.lex.cpp" L_OUTPUTS "${L_SOURCES}")
#   string(REGEX REPLACE ".*/(.*)\\.y" "${CMAKE_CURRENT_BINARY_DIR}/\\1.tab.cpp" Y_OUTPUTS "${Y_SOURCES}")
#   flex_target(Lexer ${L_SOURCES} ${L_OUTPUTS})
#   bison_target(Parser ${Y_SOURCES} ${Y_OUTPUTS})
#   add_flex_bison_dependency(Lexer Parser)
# endif()


# # project include directories
# include_directories(src/integrate)
# include_directories(${CMAKE_CURRENT_BINARY_DIR})

# # all of C/C++ source files
# file(GLOB_RECURSE C_SOURCES "src/integrate/*.c")
# file(GLOB_RECURSE CXX_SOURCES "src/integrate/*.cpp")
# file(GLOB_RECURSE CC_SOURCES "src/integrate/*.cc")
# set(SOURCES ${C_SOURCES} ${CXX_SOURCES} ${CC_SOURCES}
#             ${FLEX_Lexer_OUTPUTS} ${BISON_Parser_OUTPUT_SOURCE})

# # executable
# add_executable(compiler ${SOURCES})
# set_target_properties(compiler PROPERTIES C_STANDARD 11 CXX_STANDARD 17)