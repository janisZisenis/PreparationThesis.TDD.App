#ifndef QTIRMB_QTIRMBVIEWCOMPONENTFACTORY_H
#define QTIRMB_QTIRMBVIEWCOMPONENTFACTORY_H

#include <QtViews/QtViewComponentFactory/QtViewComponentFactory.h>

class CBCommandInvoker;
class AddingHierarchicModel;
class SelectionModel;
class CNMatcher;
class FileFinder;

class QtIRMBViewComponentFactory;
typedef std::shared_ptr<QtIRMBViewComponentFactory> QtIRMBViewComponentFactoryPtr;

class QtIRMBViewComponentFactory : public QtViewComponentFactory {
public:
    static QtIRMBViewComponentFactoryPtr getNewInstance();
    virtual ~QtIRMBViewComponentFactory();
private:
    QtIRMBViewComponentFactory();

public:
    virtual std::shared_ptr<CNComponent> makeAddSTLFileActionComponent(std::shared_ptr<CBCommandInvoker> invoker,
                                                                       std::shared_ptr<AddingHierarchicModel> model,
                                                                       std::shared_ptr<SelectionModel> selectionModel,
                                                                       std::shared_ptr<CNMatcher> matcher);

    virtual std::shared_ptr<CNComponent> makeGridGeneratorActionComponent(std::shared_ptr<CBCommandInvoker> invoker,
                                                                          std::shared_ptr<AddingHierarchicModel> model,
                                                                          std::shared_ptr<SelectionModel> selectionModel,
                                                                          std::shared_ptr<CNMatcher> matcher);
};

#endif //QTIRMB_QTIRMBVIEWCOMPONENTFACTORY_H