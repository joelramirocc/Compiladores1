cmake_minimum_required (VERSION 3.10)
project (LEXICO)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Run FA2LEXER to generate the lexer
add_custom_command (
  OUTPUT lexer.cpp
  COMMAND fa2lexer --hdr tokens.h --src lexer.cpp --tpl ${PROJECT_SOURCE_DIR}/../jff/sample1.fa2l
  MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/../jff/sample1.fa2l
  DEPENDS ${PROJECT_SOURCE_DIR}/../jff/start.jff
          ${PROJECT_SOURCE_DIR}/../jff/analizer.jff
)

INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/..)

add_executable(${PROJECT_NAME} stmtInterp.cpp lexer.cpp main.cpp)