set(
    SRC_FILES 
    Codegen.cpp
    Indent.cpp
    Lexer.cpp
    Parser.cpp
    Report.cpp
    Resolved.cpp
    Sema.cpp
)
add_library(libtrt ${SRC_FILES})
message(${CMAKE_SOURCE_DIR}/include)
target_include_directories(
    libtrt
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

include(GNUInstallDirs)

install(
    TARGETS libtrt
    EXPORT trt-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

target_compile_options(libtrt PRIVATE -frtti)

target_link_libraries(libtrt PRIVATE LLVM)
install(
    EXPORT trt-targets
    FILE trt-config.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/trt
)
