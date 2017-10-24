include(${CMAKE_SOURCE_DIR}/${cmakeMacroPath}/Boost/Link.cmake)
linkBoost(${targetName} COMPONENTS filesystem)

target_include_directories(${targetName} PUBLIC "/Users/Janis/Development/CodeBase/src")
target_link_libraries(${targetName} /Users/Janis/Development/CodeBase/build/applications/CodeBaseImp/libCodeBaseImp.dylib)

target_include_directories(${targetName} PUBLIC "/Users/Janis/Development/CrossNative/src")
target_link_libraries(${targetName} /Users/Janis/Development/CrossNative/build/applications/CrossNative/libCrossNative.dylib)

target_include_directories(${targetName} PUBLIC "/Users/Janis/Development/GridGenerator/src")
target_link_libraries(${targetName} /Users/Janis/Development/GridGenerator/build/applications/GridGenerator/libGridGenerator.dylib)

target_include_directories(${targetName} PRIVATE "/Users/Janis/Development/GridGenerator/src")
target_link_libraries(${targetName} /Users/Janis/Development/GridGenerator/build/applications/VTKWriter/libVTKWriter.dylib)