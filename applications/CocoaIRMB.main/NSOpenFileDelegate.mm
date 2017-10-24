#import "NSOpenFileDelegate.h"

@implementation NSOpenFileDelegate

- (BOOL)panel:(id)sender shouldEnableURL:(NSURL *)url;
{
    BOOL isDir;
    if(![[NSFileManager defaultManager] fileExistsAtPath:[url path] isDirectory:&isDir]) return NO;

    NSString *ext = [[url path] pathExtension];
    return isDir ? !([ext isEqual:@"app"]) : [ext isEqual:@"stl"];
}

@end