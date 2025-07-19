cmake_minimum_required(VERSION 3.16)

project(AGI_Brain LANGUAGES C)

add_executable(AGI_Brain main.c)

include(GNUInstallDirs)
install(TARGETS AGI_Brain
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
