cmake_minimum_required(VERSION 3.11)

project(Cerealkillers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if (MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /DNDEBUG")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -ggdb" )
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native -DNDEBUG -flto")
endif()

include(FetchContent)

add_executable(ck
	src/main.cpp
)

# ------------------ wxWidgets ------------------
set(wxBUILD_SHARED OFF CACHE BOOL "Build wx libraries as shared libs")
set(wxBUILD_PRECOMP OFF CACHE BOOL "Use precompiled headers")
set(wxBUILD_MONOLITHIC OFF CACHE BOOL "Build a single library")

message(STATUS "Fetching wxWidgets ...")
FetchContent_Declare(
	wxWidgets 
	GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
	GIT_TAG        v3.1.4
	GIT_SHALLOW 	TRUE
)

FetchContent_GetProperties(wxWidgets)
FetchContent_MakeAvailable(wxWidgets)

target_link_libraries(ck
	wxbase
	wxcore
	wxnet
	wxWebRequest
)