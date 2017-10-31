include(${CMAKE_SOURCE_DIR}/${cmakeMacroPath}/Boost/Link.cmake)
linkBoost(${targetName} COMPONENTS filesystem)

target_include_directories(${targetName} PUBLIC "/Users/Janis/Development/CrossNative/src")
target_link_libraries(${targetName} /Users/Janis/Development/CrossNative/cmake-build-debug/applications/Base/libBase.dylib)

target_include_directories(${targetName} PUBLIC "/Users/Janis/Development/CrossNative/src")
target_link_libraries(${targetName} /Users/Janis/Development/CrossNative/cmake-build-debug/applications/Hierarchies/libHierarchies.dylib)

target_include_directories(${targetName} PUBLIC "/Users/Janis/Development/GridGenerator/src")
target_link_libraries(${targetName} /Users/Janis/Development/GridGenerator/cmake-build-debug/applications/GridGenerator/libGridGenerator.dylib)

target_include_directories(${targetName} PRIVATE "/Users/Janis/Development/GridGenerator/src")
target_link_libraries(${targetName} /Users/Janis/Development/GridGenerator/cmake-build-debug/applications/VTKWriter/libVTKWriter.dylib)