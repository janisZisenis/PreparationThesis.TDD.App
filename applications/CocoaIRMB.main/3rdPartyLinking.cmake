include(${CMAKE_SOURCE_DIR}/${cmakeMacroPath}/Cocoa/Link.cmake)
linkCocoa(${targetName})

include(${CMAKE_SOURCE_DIR}/${cmakeMacroPath}/VTK/Link.cmake)
linkVTK(${targetName})

target_include_directories(${targetName} PUBLIC "/Users/Janis/Development/CodeBase/src")
target_link_libraries(${targetName} /Users/Janis/Development/CodeBase/build/applications/CodeBaseImp/libCodeBaseImp.dylib)

target_include_directories(${targetName} PUBLIC "/Users/Janis/Development/CrossNative/src")
target_link_libraries(${targetName} /Users/Janis/Development/CrossNative/build/applications/CrossViews/libCrossViews.dylib)

target_include_directories(${targetName} PUBLIC "/Users/Janis/Development/CrossNative/src")
target_link_libraries(${targetName} /Users/Janis/Development/CrossNative/build/applications/CocoaViews/libCocoaViews.dylib)