
add_executable(undistortViewer UndistortViewer.cpp)
add_executable(roiViewer RoiViewer.cpp)
add_executable(arViewer ArView.cpp)
add_executable(perspectiveMapping PerspectiveMapping.cpp)
add_executable(cameraDelay  CameraDelay.cpp)

target_include_directories(cameraDelay PUBLIC . $<TARGET_PROPERTY:jconfig,INTERFACE_INCLUDE_DIRECTORIES> $<TARGET_PROPERTY:our_cv,INTERFACE_INCLUDE_DIRECTORIES>)
target_include_directories(perspectiveMapping PUBLIC . $<TARGET_PROPERTY:jconfig,INTERFACE_INCLUDE_DIRECTORIES> $<TARGET_PROPERTY:our_cv,INTERFACE_INCLUDE_DIRECTORIES>)
target_include_directories(arViewer PUBLIC . $<TARGET_PROPERTY:jconfig,INTERFACE_INCLUDE_DIRECTORIES> $<TARGET_PROPERTY:our_cv,INTERFACE_INCLUDE_DIRECTORIES>)


target_link_libraries(undistortViewer jconfig cv_pipe our_cv  xil vfunctions geol display trajectory hal pthread m ${OpenCV_LIBS}  fruit stdc++fs fmt)
target_link_libraries(roiViewer jconfig cv_pipe our_cv display xil geol vfunctions trajectory hal pthread m ${OpenCV_LIBS}  fruit stdc++fs fmt)
target_link_libraries(arViewer jconfig cv_pipe our_cv geol display xil vfunctions trajectory vfunctions hal pthread m ${OpenCV_LIBS} geol hal  fruit stdc++fs fmt)
target_link_libraries(perspectiveMapping jconfig cv_pipe our_cv display hal xil geol vfunctions pthread m ${OpenCV_LIBS}  hal  fruit stdc++fs fmt)
target_link_libraries(cameraDelay hal jconfig  our_cv ${OpenCV_LIBS}  hal stdc++fs fmt)
IF(HAS_RASPICAM_CV)
target_link_libraries(undistortViewer raspicam_cv mmal mmal_core mmal_util )
target_link_libraries(roiViewer raspicam_cv mmal mmal_core mmal_util)
ENDIF(HAS_RASPICAM_CV)

