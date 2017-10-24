#ifndef COCOAIRMB_COCOASTLFILE_H
#define COCOAIRMB_COCOASTLFILE_H

#include <CocoaViews/NSViewBased/CocoaCentral/CocoaCentral.h>

class CNAcceptor;

@class NSVTKView;
class STLFile;

class CocoaSTLFile;
typedef std::shared_ptr<CocoaSTLFile> CocoaSTLFilePtr;

class CocoaSTLFile : public CocoaCentral, public std::enable_shared_from_this<CocoaSTLFile> {
public:
    static CocoaSTLFilePtr getNewInstance(std::shared_ptr<STLFile> stlFile);
    virtual ~CocoaSTLFile();
protected:
    CocoaSTLFile(std::shared_ptr<STLFile> stlFile);

public:
    NSView *getNSView() override;
    std::string getTitle() override;

    virtual void accept(CNVisitorPtr visitor) override;
private:
    virtual CocoaSTLFilePtr me();

private:
    std::shared_ptr<CNAcceptor> acceptor;

    std::string title;
    std::shared_ptr<STLFile> stlFile;
    NSVTKView* view;
};

#endif //COCOAIRMB_COCOASTLFILE_H