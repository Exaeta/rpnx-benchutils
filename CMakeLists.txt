cmake_minimum_required(VERSION 3.5)

add_library(rpnx-benchutils INTERFACE)
target_include_directories(rpnx-benchutils INTERFACE include/)

INSTALL(FILES "include/rpnx/benchutils.hpp" DESTINATION "include/rpnx" RENAME "benchutils")
