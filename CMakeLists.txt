cmake_minimum_required(VERSION 3.15)

project(Laboratory3 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDART 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#Чтобы найти пакеты Qt5
#set(CMAKE_PREFIX_PATH "C:\\Qt\\5.14.2\\mingw73_64")

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(project_headers 
	include/AbstractStrategy.h
	include/Configuration.h
	include/FolderGrouping.h
	include/TypeGrouping.h
	include/StrategyManagement.h
	include/FolderGroupingTest.h
	include/TypeGroupingTest.h
	include/ConfigurationTest.h
)

set(project_sources 
	src/main.cpp
	src/FolderGrouping.cpp
	src/TypeGrouping.cpp
	src/StrategyManagement.cpp
	src/FolderGroupingTest.cpp
	src/TypeGroupingTest.cpp
	src/ConfigurationTest.cpp
)

set(project_resources
	src/resource.qrc
)

add_executable(${PROJECT_NAME}
	${project_headers}
	${project_sources}
)

target_link_libraries(${PROJECT_NAME} 
	PUBLIC 
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
)