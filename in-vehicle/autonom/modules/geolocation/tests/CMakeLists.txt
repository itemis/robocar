
	include_directories( "../../../3rdparty/catch2/include" "3rdparty" "../3rdparty/ben-strasser/fast-cpp-csv-parser-master" )

    include_directories(${CXXTEST_INCLUDE_DIR})
    find_package(Catch2 REQUIRED)
    file(MAKE_DIRECTORY tests)
    enable_testing()

add_executable(geol_test CatchTest.cpp MMGeoLocationTest.cpp)
#target_include_directories(geol_test PUBLIC . $<TARGET_PROPERTY:geol,INTERFACE_INCLUDE_DIRECTORIES> $<TARGET_PROPERTY:geol,INTERFACE_INCLUDE_DIRECTORIES>)
target_link_libraries(geol_test Catch2::Catch2 jconfig geol  pthread hal)





include(Catch)
#catch_discover_tests(catchtest )



