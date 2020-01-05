set (CMAKE_CXX_STANDARD 14)
include_directories( "../../../3rdparty/lohmann/include" "../../../3rdparty" "../../../3rdparty/ben-strasser/fast-cpp-csv-parser-master" "../../../3rdparty/nholthaus/units/" )


add_library(geol AbstractGeolocation.cpp MMGeoLocation.cpp GeoLocationFactory.cpp CSVGeoLocation.cpp TimedCSVGeoLocation.cpp FixedGeolocation.cpp)
target_link_libraries(geol hal)
target_include_directories(geol PUBLIC . $<TARGET_PROPERTY:jconfig,INTERFACE_INCLUDE_DIRECTORIES> $<TARGET_PROPERTY:our_cv,INTERFACE_INCLUDE_DIRECTORIES> $<TARGET_PROPERTY:csv_parser,INTERFACE_INCLUDE_DIRECTORIES> )


