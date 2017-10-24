#ifndef COCOALVIEW_NSOPENFILEDELEGATE_H
#define COCOALVIEW_NSOPENFILEDELEGATE_H

#import <Cocoa/Cocoa.h>

@interface NSOpenFileDelegate : NSObject <NSOpenSavePanelDelegate>

- (BOOL)panel:(id)sender shouldEnableURL:(NSURL *)url;

@end


#endif //COCOALVIEW_NSOPENFILEDELEGATE_H