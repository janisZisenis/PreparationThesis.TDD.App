#ifndef COCOAIRMB_COCOAIRMBSOLUTIONITEMFACTORY_H
#define COCOAIRMB_COCOAIRMBSOLUTIONITEMFACTORY_H

#include <memory>
#include <string>

#include <CocoaViews/NSViewBased/CocoaSolutionExplorer/CocoaSolutionItemFactory.h>

class CocoaIRMBSolutionItemFactory;
typedef std::shared_ptr<CocoaIRMBSolutionItemFactory> CocoaIRMBSolutionItemFactoryPtr;

class CocoaIRMBSolutionItemFactory : public CocoaSolutionItemFactory {
public:
    static CocoaIRMBSolutionItemFactoryPtr getNewInstance();
    virtual ~CocoaIRMBSolutionItemFactory();
protected:
    CocoaIRMBSolutionItemFactory();

public:
    virtual CocoaSolutionItem* makeCocoaSolutionItem(std::shared_ptr<CNVisitable> visitable) override;
};

#endif //COCOAIRMB_COCOAIRMBSOLUTIONITEMFACTORY_H