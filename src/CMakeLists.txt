set(
    SRC_FILES 
    Codegen.cpp
    Utils.cpp
    Lexer.cpp
    Parser.cpp
    Report.cpp
    Resolved.cpp
    Sema.cpp
    Statement.cpp
)

add_library(libtarot ${SRC_FILES})

message(${CMAKE_SOURCE_DIR}/include)

target_include_directories(
    libtarot
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
    
include(GNUInstallDirs)

install(
    TARGETS libtarot
    EXPORT tarot-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

target_compile_options(libtarot PRIVATE -frtti)

target_link_libraries(libtarot PRIVATE LLVM)

install(
    EXPORT tarot-targets
    FILE tarot-config.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/tarot
)
