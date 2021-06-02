cmake_minimum_required(VERSION 3.16.3)
SET(CMAKE_CXX_FLAGS "-std=c++14")
project(Cerealkillers-unit-tests)

# ------------------ GOOGLETEST ------------------
message(STATUS "Fetching googletest...")
FetchContent_Declare(
        googletest
        GIT_REPOSITORY      https://github.com/google/googletest.git
        GIT_TAG             release-1.10.0
        GIT_SHALLOW	        TRUE
)
FetchContent_GetProperties(googletest)
FetchContent_MakeAvailable(googletest)

#client libs: ck_libs_c
#server libs: ck_libs_s

# ------------------ CLIENT TESTS ------------------

# ------------------ SERVER TESTS ------------------
add_executable( tcp_server_client_connection_tests "servertest/tcp_server_client_connection_test.cpp" )
target_link_libraries(tcp_server_client_connection_tests gtest gtest_main ck_lib_s ck_lib_c)

add_executable( test_game_controller_tests "servertest/test_game_controller.cpp" )
target_link_libraries(test_game_controller_tests gtest gtest_main ck_lib_s)


#  ====================== Bottom one  is from lastbcrash branch, top one is from server. I don't know which is the right one =================
# project(Cerealkillers-unit-tests)

# # ------------------ GOOGLETEST ------------------
# message(STATUS "Fetching googletest...")
# FetchContent_Declare(
# 		googletest
# 		GIT_REPOSITORY      https://github.com/google/googletest.git
# 		GIT_TAG             release-1.10.0
# 		GIT_SHALLOW	        TRUE
# )
# FetchContent_GetProperties(googletest)
# FetchContent_MakeAvailable(googletest)

# # ------------------ ADD SOURCE FILES HERE ------------------
# set(SERVER_TEST_FILES 
# 	"servertest/test_game_controller.cpp"
# )

# set(CLIENT_TEST_FILES 
#    "clienttest/main.cpp" 
# )

# set(COMMON_TEST_FILES 
# 	"commontest/test_cards.cpp" 
# )
# # ------------------------------------------------------------

# add_executable( server-tests ${SERVER_TEST_FILES} )
# add_executable( client-tests ${CLIENT_TEST_FILES} )

# target_link_libraries(server-tests gtest gtest_main ck_lib)
# target_link_libraries(client-tests gtest gtest_main ck_lib)

