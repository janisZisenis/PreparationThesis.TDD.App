include(${CMAKE_SOURCE_DIR}/${cmakeMacroPath}/Qt/Link.cmake)
linkQt(${targetName})

include(${CMAKE_SOURCE_DIR}/${cmakeMacroPath}/VTK/Link.cmake)
linkVTK(${targetName})

target_include_directories(${targetName} PUBLIC "/Users/Janis/Development/CrossNative/src")
target_link_libraries(${targetName} /Users/Janis/Development/CrossNative/cmake-build-debug/applications/Base/libBase.dylib)

target_include_directories(${targetName} PUBLIC "/Users/Janis/Development/CrossNative/src")
target_link_libraries(${targetName} /Users/Janis/Development/CrossNative/cmake-build-debug/applications/CrossViews/libCrossViews.dylib)

target_include_directories(${targetName} PUBLIC "/Users/Janis/Development/CrossNative/src")
target_link_libraries(${targetName} /Users/Janis/Development/CrossNative/cmake-build-debug/applications/QtViews/libQtViews.dylib)