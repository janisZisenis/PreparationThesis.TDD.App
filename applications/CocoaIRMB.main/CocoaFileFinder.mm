#include "CocoaFileFinder.h"
#import <Cocoa/Cocoa.h>
#import "NSOpenFileDelegate.h"

CocoaFileFinderPtr CocoaFileFinder::getNewInstance() {
    return CocoaFileFinderPtr(new CocoaFileFinder());
}

CocoaFileFinder::~CocoaFileFinder() {}
CocoaFileFinder::CocoaFileFinder() {}

bool CocoaFileFinder::findFile() {
    bool success = false;

    NSOpenFileDelegate* delegate = [[NSOpenFileDelegate alloc] init];
    NSOpenPanel* panel = [NSOpenPanel openPanel];
    [panel setDelegate:delegate];

    [panel setCanChooseFiles:YES];
    [panel setAllowsMultipleSelection:NO];
    [panel setCanChooseDirectories:NO];
    [panel setDirectoryURL: [NSURL fileURLWithPath:@"/Users/Janis/Desktop/STL/"]];
//    [panel setDirectoryURL:[NSURL fileURLWithPath:NSHomeDirectory()]];

    if ([panel runModal] == NSModalResponseOK) {
        success = true;
        foundFile = [[[[panel URLs] objectAtIndex:0] path] UTF8String];
    };

    return success;
}

std::string CocoaFileFinder::getFileName() {
    std::string temp = foundFile;
    foundFile = "";
    return temp;
}
