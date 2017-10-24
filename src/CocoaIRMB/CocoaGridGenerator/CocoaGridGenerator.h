#ifndef COCOAIRMB_COCOAGRIDGENERATOR_H
#define COCOAIRMB_COCOAGRIDGENERATOR_H

#include <CocoaViews/NSViewBased/CocoaCentral/CocoaCentral.h>

class CNAcceptor;

class GridGenerator;
@class NSVTKView;

class CocoaGridGenerator;
typedef std::shared_ptr<CocoaGridGenerator> CocoaGridGeneratorPtr;

class CocoaGridGenerator : public CocoaCentral, public std::enable_shared_from_this<CocoaGridGenerator> {
public:
    static CocoaGridGeneratorPtr getNewInstance(std::shared_ptr<GridGenerator> gridGenerator);
    virtual ~CocoaGridGenerator();

protected:
    CocoaGridGenerator(std::shared_ptr<GridGenerator> gridGenerator);

public:
    NSView *getNSView() override;
    std::string getTitle() override;

    virtual void accept(CNVisitorPtr visitor) override;

private:
    virtual CocoaGridGeneratorPtr me();

private:
    std::shared_ptr<CNAcceptor> acceptor;

    std::string title;
    std::shared_ptr<GridGenerator> gridGenerator;
    NSVTKView* view;
};

#endif //COCOAIRMB_COCOAGRIDGENERATOR_H