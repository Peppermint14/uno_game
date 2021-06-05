# ------------------ GOOGLETEST ------------------
message(STATUS "Fetching googletest...")
FetchContent_Declare(
        googletest
        GIT_REPOSITORY      https://github.com/google/googletest.git
        GIT_TAG             release-1.10.0
        GIT_SHALLOW	    TRUE
)
FetchContent_MakeAvailable(googletest)

#client libs: ck_libs_c
#server libs: ck_libs_s

# ------------------ CLIENT TESTS ------------------

# ------------------ SERVER TESTS ------------------
add_executable( tcp_server_client_connection_tests "servertest/tcp_server_client_connection_test.cpp" )
target_link_libraries(tcp_server_client_connection_tests gtest gtest_main ck_lib_s ck_lib_c)

add_executable( test_game_controller_tests "servertest/test_game_controller.cpp" )
target_link_libraries(test_game_controller_tests gtest gtest_main ck_lib_s)

