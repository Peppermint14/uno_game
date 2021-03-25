cmake_minimum_required(VERSION 3.16.3)

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

if (MSVC)
	add_executable(ck_client
		WIN32
		src/client/main.cpp
		src/common/network.cpp
	)
	add_executable(ck_server
		WIN32
		src/server/main.cpp
		src/common/network.cpp
	)
else()
	add_executable(ck_client
		src/client/main.cpp
		src/common/network.cpp
	)
	add_executable(ck_server
		src/server/main.cpp
		src/common/network.cpp
	)
endif()

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

# ------------------ JSON ------------------
message(STATUS "Fetching json ...")
FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent.git
  GIT_TAG v3.9.1
  GIT_SHALLOW TRUE
  )

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# ------------------ SOCKCPP ------------------
set(SOCKPP_BUILD_SHARED OFF CACHE BOOL "Whether to build the shared library")
set(SOCKPP_BUILD_STATIC ON CACHE BOOL "Whether to build the static library")
message(STATUS "Fetching sockpp ...")
FetchContent_Declare(
	sockpp 
	GIT_REPOSITORY https://github.com/fpagliughi/sockpp.git
	GIT_TAG        v0.7
	GIT_SHALLOW 	TRUE
)

FetchContent_GetProperties(sockpp)
FetchContent_MakeAvailable(sockpp)

# ------------------ SPDLOG ------------------
message(STATUS "Fetching SPDLOG...")
FetchContent_Declare(
	spdlog
	GIT_REPOSITORY https://github.com/gabime/spdlog.git
	GIT_TAG        v1.8.2
	GIT_SHALLOW TRUE
)
FetchContent_GetProperties(spdlog)
FetchContent_MakeAvailable(spdlog)

if (MSVC)
	target_link_libraries(ck_client	
		wxnet
		wxcore
		wxbase	
		nlohmann_json::nlohmann_json
		sockpp-static
		spdlog::spdlog
		wsock32
		ws2_32
	) 
	target_link_libraries(ck_server	
		wxnet
		wxcore
		wxbase	
		nlohmann_json::nlohmann_json
		sockpp-static
		spdlog::spdlog
		wsock32
		ws2_32
	)
else()
	target_link_libraries(ck_client	
		wxnet
		wxcore
		wxbase	
		nlohmann_json::nlohmann_json
		sockpp-static
		spdlog::spdlog
	) 
	target_link_libraries(ck_server	
		wxnet
		wxcore
		wxbase	
		nlohmann_json::nlohmann_json
		sockpp-static
		spdlog::spdlog
	)
endif()
