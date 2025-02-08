add_executable(trt tarot.cpp)
target_link_libraries(trt PUBLIC libtrt)
message("tools source directory: ${CMAKE_SOURCE_DIR}")


include(GNUInstallDirs)
install(
    TARGETS trt
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/
)