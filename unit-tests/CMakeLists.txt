project(Cerealkillers-unit-tests)

# ------------------ GOOGLETEST ------------------
message(STATUS "Fetching googletest...")
FetchContent_Declare(
		googletest
		GIT_REPOSITORY      https://github.com/google/googletest.git
		GIT_TAG             release-1.10.0
        GIT_SHALLOW		    TRUE
)
FetchContent_GetProperties(googletest)
FetchContent_MakeAvailable(googletest)

# ------------------ ADD SOURCE FILES HERE ------------------
set(SERVER_TEST_FILES 
    "servertest/test_game_controller.cpp"
)

set(CLIENT_TEST_FILES 
   "clienttest/main.cpp" 
)
# ------------------------------------------------------------

add_executable( server-tests ${SERVER_TEST_FILES} )
add_executable( client-tests ${CLIENT_TEST_FILES} )

if (MSVC)
    target_link_libraries(server-tests gtest gtest_main wsock32 ws2_32 ck_lib)
    target_link_libraries(client-tests gtest gtest_main wsock32 ws2_32 ck_lib)
else()
    target_link_libraries(server-tests gtest gtest_main ck_lib)
    target_link_libraries(client-tests gtest gtest_main ck_lib)
endif()
