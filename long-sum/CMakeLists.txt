add_catch(test_long_sum test.cpp)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties(test_long_sum PROPERTIES COMPILE_FLAGS "-g")
    set_target_properties(test_long_sum PROPERTIES LINK_FLAGS "")
endif()