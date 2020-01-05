
add_library(xil VirtualTrack.cpp  )
add_dependencies(jconfig nlohmann spdlog n_units geol)
target_include_directories(xil PUBLIC . $<TARGET_PROPERTY:jconfig,INTERFACE_INCLUDE_DIRECTORIES> $<TARGET_PROPERTY:geol,INTERFACE_INCLUDE_DIRECTORIES>)


