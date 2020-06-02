cmake_minimum_required(VERSION 3.15)

project(Laboratory3 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDART 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#Чтобы найти пакеты Qt5
set(CMAKE_PREFIX_PATH "C:\\Qt\\5.14.2\\msvc2017_64")

find_package(Qt5 COMPONENTS Core Gui Widgets Charts REQUIRED)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(project_ui
	ui/Explorer.ui
)

set(project_headers 
	include/AbstractStrategy.h
	include/Data.h
	include/Explorer.h
	include/Configuration.h
	include/FolderGrouping.h
	include/TypeGrouping.h
	include/StrategyManagement.h
	include/FileBrowserModel.h
)

set(project_sources 
	src/main.cpp
	src/Explorer.cpp
	src/FolderGrouping.cpp
	src/TypeGrouping.cpp
	src/StrategyManagement.cpp
	src/FileBrowserModel.cpp
)

set(project_resources
	src/resource.qrc
)

qt5_wrap_ui(project_headers_wrapped ${project_ui})

add_executable(${PROJECT_NAME}
	${project_ui}
	${project_headers}
	${project_sources}
)

target_link_libraries(${PROJECT_NAME} 
	PUBLIC 
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
	Qt5::Charts
)