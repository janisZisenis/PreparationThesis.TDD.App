#ifndef QTIRMB_QTIRMBSOLUTIONITEMFACTORY_H
#define QTIRMB_QTIRMBSOLUTIONITEMFACTORY_H

#include <memory>
#include <string>

#include <QtViews/QWidgetBased/QtSolutionExplorer/QtSolutionItemFactory.h>

class QtIRMBSolutionItemFactory;
typedef std::shared_ptr<QtIRMBSolutionItemFactory> QtIRMBSolutionItemFactoryPtr;

class QtIRMBSolutionItemFactory : public QtSolutionItemFactory{
public:
    static QtIRMBSolutionItemFactoryPtr getNewInstance();
    virtual ~QtIRMBSolutionItemFactory();
protected:
    QtIRMBSolutionItemFactory();

public:
    virtual std::shared_ptr<QtSolutionItem> makeQtSolutionItem(std::shared_ptr<CNVisitable> visitable) override;
};

#endif //QTIRMB_QTIRMBSOLUTIONITEMFACTORY_H