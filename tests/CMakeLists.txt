project(tests)
add_subdirectory(./../googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
# add in the root CMakeLists.txt script:
# add_subdirectory(googletest) 
# add_subdirectory(tests)

set(TEST_SOURCE_FILES
	./commontest/test_cards.cpp
	./clienttest/test_player_controller.cpp
	./servertest/test_game_controller.cpp)

target_link_libraries(UNO-test "${CLIENT_LIBS}" "${SERVER_LIBS}" wsock32 ws2_32)
target_link_libraries(UNO-tests gtest gtest_main)

add_executable(UNO-tests ${TEST_SOURCE_FILES} ${SERVER_FILES} ${CLIENT_FILES} ${COMMON_FILES})