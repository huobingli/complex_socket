PROJECT(testmysql)
SET(test.cpp)
SET(CXX_FLAGS -g -Wall -pthread -std=c++11 )
INCLUDE_DIRECTORIES(usr/include/mysql/)
LINK_DIRECTORIES(/usr/lib64/mysql/)

SET(CMAKE_CXX_COMPILER "g++")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../)
STRING(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")
##ADD_EXECUTABLE(testmysql ${SRC_LIST})
TARGET_LINK_LIBRARIES(testmysql mysqlclient)

