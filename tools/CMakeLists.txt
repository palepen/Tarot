add_executable(tarot tarot.cpp)
target_link_libraries(tarot PUBLIC libtarot)
message("tools source directory: ${CMAKE_SOURCE_DIR}")


target_include_directories(
    libtarot
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

include(GNUInstallDirs)
install(
    TARGETS tarot
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/
)
