#FILE ENDINGS
resetFileEndingsToCollect()
addObjCAndObjCPPFileTypesToCollect()

#GLOB SOURCE FILES IN MY_SRCS
unset(MY_SRCS)
includeRecursiveAllFilesFrom(${targetName} ${CMAKE_CURRENT_LIST_DIR})
