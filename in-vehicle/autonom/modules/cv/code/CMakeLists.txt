add_library(our_cv CVUtil.cpp AbstractCamera.cpp  ImageAcquisitionCV.cpp ImageAcquisitionCVGStreamer.cpp CameraFactory.cpp ImageAcquisitionDir.cpp ImageAcquisitionFile.cpp ImageSaver.cpp AbstractImageSaver.cpp ImageSaverFactory.cpp   Streamer.cpp)
target_include_directories(our_cv PUBLIC . $<TARGET_PROPERTY:jconfig,INTERFACE_INCLUDE_DIRECTORIES> $<TARGET_PROPERTY:hal,INTERFACE_INCLUDE_DIRECTORIES>)
target_link_libraries(our_cv fmt)

IF(HAS_RASPICAM_CV)
	message("Adding Raspi Cam modules")
	target_sources(our_cv PRIVATE ImageAcquisitionRCCV.cpp)
ENDIF(HAS_RASPICAM_CV)