#include "CocoaIRMBSolutionItemFactory.h"

#include <CrossNative/CNVisitor/CNVisitor.h>
#include <CocoaViews/NSViewBased/CocoaSolutionExplorer/CocoaSolutionItem.h>
#include <IRMB/STLFile/STLFileVisitor.h>
#include <IRMB/STLFile/STLFile.h>
#include <IRMB/GridGenerator/GridGeneratorVisitor.h>
#include <IRMB/GridGenerator/GridGenerator.h>

class CocoaSolutionItemCreator;
typedef std::shared_ptr<CocoaSolutionItemCreator> CocoaSolutionItemCreatorPtr;
class CocoaSolutionItemCreator
        : public CNVisitor,
          public STLFileVisitor,
          public GridGeneratorVisitor {
public:
    static CocoaSolutionItemCreatorPtr getNewInstance() {
        return CocoaSolutionItemCreatorPtr(new CocoaSolutionItemCreator());
    }
    virtual ~CocoaSolutionItemCreator() {}
private:
    CocoaSolutionItemCreator() {}

public:
    void visit(STLFilePtr stlFile) override {
        item = [[CocoaSolutionItem alloc] initWithName:[NSString stringWithUTF8String:stlFile->getName().c_str()] type:@"STL File"];
    }
    void visit(GridGeneratorPtr gridGenerator) override {
        item = [[CocoaSolutionItem alloc] initWithName:[NSString stringWithUTF8String:gridGenerator->getName().c_str()] type:@"Grid Generator"];
    }


    virtual CocoaSolutionItem* getItem() {
        return item;
    }
private:
    CocoaSolutionItem* item;
};


CocoaIRMBSolutionItemFactoryPtr CocoaIRMBSolutionItemFactory::getNewInstance() {
    return CocoaIRMBSolutionItemFactoryPtr(new CocoaIRMBSolutionItemFactory());
}

CocoaIRMBSolutionItemFactory::~CocoaIRMBSolutionItemFactory() {}
CocoaIRMBSolutionItemFactory::CocoaIRMBSolutionItemFactory() {}

CocoaSolutionItem *CocoaIRMBSolutionItemFactory::makeCocoaSolutionItem(std::shared_ptr<CNVisitable> visitable) {
    CocoaSolutionItemCreatorPtr itemCreator = CocoaSolutionItemCreator::getNewInstance();

    try{
        visitable->accept(itemCreator);
    } catch(CNVisitableVisitorMismatchException& e) {
        throw UnknownTypeException();
    }

    return itemCreator->getItem();
}