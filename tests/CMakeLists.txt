add_executable(cjson_unittest cjson_unittest.cpp ${PROJECT_SOURCE_DIR}/src/cJson.cpp)
target_link_libraries(cjson_unittest ${GMOCK} ${GMOCK} ${GTEST_BOTH_LIBRARIES} pthread)
add_test(Test cjson_unittest)