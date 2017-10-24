set(targetName CocoaIRMB)       #REQUIRED#

set(linkDirectories "")
set(libsToLink IRMB)
set(includeDirectories ${CMAKE_SOURCE_DIR}/src)
#glob files and save in MY_SRCS
include(CMakePackage.cmake)

buildLib(${targetName} "${MY_SRCS}" "${linkDirectories}" "${libsToLink}" "${includeDirectories}")
generateExportHeader(${targetName} ${CMAKE_SOURCE_DIR}/src/${targetName})

target_compile_options(${targetName} PRIVATE -std=c++11)

#Specify the linking to 3rdParty libs
include(3rdPartyLinking.cmake)
