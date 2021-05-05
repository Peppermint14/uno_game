project(tests)
add_subdirectory(./../googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
// add in the root CMakeLists.txt script:
// add_subdirectory(googletest) 
// add_subdirectory(tests)

set(TEST_SOURCE_FILES
	./common/cards.cpp
	./client/player_controller.cpp
	./server/game_state.cpp)

add_executable(UNO-tests ${TEST_SOURCE_FILES})

target_compile_definitions(UNO-tests PRIVATE LAMA_SERVER=1 RAPIDJSON_HAS_STDSTRING=1)

target_link_libraries(UNO-tests gtest gtest_main)
// add the "UNO lib" ? 
// like here target_link_libraries(UNO-tests gtest gtest_main Lama-lib)

