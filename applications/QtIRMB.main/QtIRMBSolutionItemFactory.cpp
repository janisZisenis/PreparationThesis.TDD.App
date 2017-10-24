#include "QtIRMBSolutionItemFactory.h"
#include <QtViews/QWidgetBased/QtSolutionExplorer/QtSolutionItem.h>
#include <CrossNative/CNVisitor/CNVisitor.h>
#include <IRMB/STLFile/STLFileVisitor.h>
#include <IRMB/STLFile/STLFile.h>
#include <IRMB/GridGenerator/GridGenerator.h>
#include <IRMB/GridGenerator/GridGeneratorVisitor.h>

class QtIRMBSolutionItemCreator;
typedef std::shared_ptr<QtIRMBSolutionItemCreator> QtIRMBSolutionItemCreatorPtr;
class QtIRMBSolutionItemCreator
        : public CNVisitor,
          public STLFileVisitor,
          public GridGeneratorVisitor {
public:
    static QtIRMBSolutionItemCreatorPtr getNewInstance() {
        return QtIRMBSolutionItemCreatorPtr(new QtIRMBSolutionItemCreator());
    }
    virtual ~QtIRMBSolutionItemCreator() {}
private:
    QtIRMBSolutionItemCreator() {}

public:
    void visit(STLFilePtr stlFile) override {
        item = QtSolutionItem::getNewInstance(stlFile->getName(), "STL File");
    }
    void visit(GridGeneratorPtr gridGenerator) override {
        item = QtSolutionItem::getNewInstance(gridGenerator->getName(), "Grid Generator");
    }

    virtual QtSolutionItemPtr getItem() {
        return item;
    }
private:
    QtSolutionItemPtr item;
};


QtIRMBSolutionItemFactoryPtr QtIRMBSolutionItemFactory::getNewInstance() {
    return QtIRMBSolutionItemFactoryPtr(new QtIRMBSolutionItemFactory());
}

QtIRMBSolutionItemFactory::~QtIRMBSolutionItemFactory() {}
QtIRMBSolutionItemFactory::QtIRMBSolutionItemFactory() {}

QtSolutionItemPtr QtIRMBSolutionItemFactory::makeQtSolutionItem(CNVisitablePtr visitable) {
    QtIRMBSolutionItemCreatorPtr itemCreator = QtIRMBSolutionItemCreator::getNewInstance();

    try{
        visitable->accept(itemCreator);
    } catch(CNVisitableVisitorMismatchException& e) {
        throw UnknownTypeException();
    }

    return itemCreator->getItem();
}