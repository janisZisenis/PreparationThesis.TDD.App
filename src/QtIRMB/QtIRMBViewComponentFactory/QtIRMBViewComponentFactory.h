#ifndef QTIRMB_QTIRMBVIEWCOMPONENTFACTORY_H
#define QTIRMB_QTIRMBVIEWCOMPONENTFACTORY_H

#include <QtViews/QtViewComponentFactory/QtViewComponentFactory.h>

class CNCommandInvoker;
class CNComponentAdder;
class SelectionModel;
class CNMatcher;
class FileFinder;
class MenuEntryListProvider;

class QtIRMBViewComponentFactory;
typedef std::shared_ptr<QtIRMBViewComponentFactory> QtIRMBViewComponentFactoryPtr;

class QtIRMBViewComponentFactory : public QtViewComponentFactory {
public:
    static QtIRMBViewComponentFactoryPtr getNewInstance();
    virtual ~QtIRMBViewComponentFactory();
private:
    QtIRMBViewComponentFactory();

public:
    virtual std::shared_ptr<CNComponent> makeEvaluateMenuComponent(std::string title, std::string tag, std::shared_ptr<CNSelectionModel> selectionModel,
                                                                   std::shared_ptr<CNComponentListProvider> menuEntryListProvider);

    virtual std::shared_ptr<CNComponent> makeAddSTLFileActionComponent(std::shared_ptr<CNCommandInvoker> invoker,
                                                                       std::shared_ptr<CNComponentAdder> model,
                                                                       std::shared_ptr<CNSelectionModel> selectionModel,
                                                                       std::shared_ptr<CNMatcher> matcher);

    virtual std::shared_ptr<CNComponent> makeGridGeneratorActionComponent(std::shared_ptr<CNCommandInvoker> invoker,
                                                                          std::shared_ptr<CNComponentAdder> model,
                                                                          std::shared_ptr<CNSelectionModel> selectionModel,
                                                                          std::shared_ptr<CNMatcher> matcher);
};

#endif //QTIRMB_QTIRMBVIEWCOMPONENTFACTORY_H