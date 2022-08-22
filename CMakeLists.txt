cmake_minimum_required(VERSION 3.16.3)

project(Cerealkillers)

cmake_policy(SET CMP0076 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if (MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /DNDEBUG")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive") # removed -fno-rtti
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -ggdb -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG" )
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Os -march=native -DNDEBUG -flto -fomit-frame-pointer")
	set(CMAKE_CXX_FLAGS_TURBOSPEED "-Ofast -funroll-loops -s -DNDEBUG -flto -fomit-frame-pointer -march=native")
endif()

include(FetchContent)

# ------------------ ADD SOURCE FILES HERE ------------------
set(CLIENT_FILES_LIB
	"src/client/digital_UNO.cpp"
	"src/client/tcp_client.cpp"
	"src/client/player_state.cpp"
	"src/client/player.cpp"
	"src/client/player_controller.cpp"
	#UI
	"src/client/UI/ConnectionPanel.cpp"
	"src/client/UI/GameWindow.cpp"
	"src/client/UI/ImagePanel.cpp"
	"src/client/UI/InputField.cpp"
	"src/client/UI/MainGamePanel.cpp"
)

set( CLIENT_FILES "${CLIENT_FILES_LIB}" )
list( APPEND CLIENT_FILES "src/client/main.cpp" )

set(SERVER_FILES_LIB	
	"src/server/tcp_server.cpp"	
	"src/server/game_controller.cpp"
	"src/server/game_state.cpp"
	"src/server/player.cpp"
)

set( SERVER_FILES "${SERVER_FILES_LIB}" )
list( APPEND SERVER_FILES "src/server/main.cpp" )

set(COMMON_FILES
	"src/common/utils.cpp"
	"src/common/cards.cpp"
	"src/common/logger.cpp"
)
# ------------------------------------------------------------

if (MSVC)
	add_executable(ck_client WIN32 "${CLIENT_FILES}" "${COMMON_FILES}")
	add_executable(ck_server "${SERVER_FILES}" "${COMMON_FILES}")
else()
	add_executable(ck_client "${CLIENT_FILES}" "${COMMON_FILES}")
	add_executable(ck_server "${SERVER_FILES}" "${COMMON_FILES}")
endif()

# ------------------ wxWidgets ------------------

set(wxBUILD_SHARED OFF CACHE BOOL "Build wx libraries as shared libs")
set(wxBUILD_PRECOMP OFF CACHE BOOL "Use precompiled headers")
set(wxBUILD_MONOLITHIC OFF CACHE BOOL "Build a single library")
message(STATUS "Fetching wxWidgets ...")
FetchContent_Declare(
	wxWidgets 
	GIT_REPOSITORY	https://github.com/wxWidgets/wxWidgets.git
	GIT_TAG			v3.1.4
	GIT_SHALLOW		TRUE
)
FetchContent_MakeAvailable(wxWidgets)

# ------------------ JSON ------------------
message(STATUS "Fetching json ...")
FetchContent_Declare(json
	GIT_REPOSITORY	https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent.git
	GIT_TAG			v3.9.1
	GIT_SHALLOW		TRUE
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
	GIT_REPOSITORY	https://github.com/fpagliughi/sockpp.git
	GIT_TAG			v0.7
	GIT_SHALLOW		TRUE
)
FetchContent_MakeAvailable(sockpp)

# ------------------ SPDLOG ------------------
message(STATUS "Fetching SPDLOG...")
FetchContent_Declare(
	spdlog
	GIT_REPOSITORY	https://github.com/gabime/spdlog.git
	GIT_TAG			v1.8.2
	GIT_SHALLOW		TRUE
)
FetchContent_MakeAvailable(spdlog)

# ------------------ ADD LIBRARIES HERE -----------------------
set(CLIENT_LIBS
	"wxnet"
	"wxcore"
	"wxbase"
	"nlohmann_json::nlohmann_json"
	"sockpp-static"
	"spdlog::spdlog"
)

set(SERVER_LIBS
	"nlohmann_json::nlohmann_json"
	"sockpp-static"
	"spdlog::spdlog"
)
# ------------------------------------------------------------

if (MSVC)
	target_link_libraries(ck_client "${CLIENT_LIBS}" wsock32 ws2_32) 
	target_link_libraries(ck_server "${SERVER_LIBS}" wsock32 ws2_32)
else()
	target_link_libraries(ck_client "${CLIENT_LIBS}") 
	target_link_libraries(ck_server "${SERVER_LIBS}")
endif()
#----------------------------------------------------------------

# ------------------ TESTS ------------------

#if(CK_BUILD_TESTS)
	add_library(ck_lib_s "${SERVER_FILES_LIB}" "${COMMON_FILES}")
	if (MSVC)
		target_link_libraries(ck_lib_s "${SERVER_LIBS}" wsock32 ws2_32)
	else()
		target_link_libraries(ck_lib_s "${SERVER_LIBS}")
	endif()

	add_library(ck_lib_c "${CLIENT_FILES_LIB}" "${COMMON_FILES}")
	if (MSVC)
		target_link_libraries(ck_lib_c "${CLIENT_LIBS}" wsock32 ws2_32)
	else()
		target_link_libraries(ck_lib_c "${CLIENT_LIBS}")
	endif()

	add_subdirectory(unit-tests)
#endif()

