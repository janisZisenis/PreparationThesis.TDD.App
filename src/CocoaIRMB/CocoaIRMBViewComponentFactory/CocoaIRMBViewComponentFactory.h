#ifndef COCOAIRMB_COCOAIRMBVIEWCOMPONENTFACTORY_H
#define COCOAIRMB_COCOAIRMBVIEWCOMPONENTFACTORY_H

#include <CocoaViews/CocoaViewComponentFactory/CocoaViewComponentFactory.h>

class CNCommandInvoker;
class CNComponentAdder;
class CNSelectionModel;
class CNMatcher;
class FileFinder;
class CNVisitableListProvider;

class CocoaIRMBViewComponentFactory;
typedef std::shared_ptr<CocoaIRMBViewComponentFactory> CocoaIRMBViewComponentFactoryPtr;

class CocoaIRMBViewComponentFactory : public CocoaViewComponentFactory {
public:
    static CocoaIRMBViewComponentFactoryPtr getNewInstance();
    virtual ~CocoaIRMBViewComponentFactory();
private:
    CocoaIRMBViewComponentFactory();

public:
    virtual std::shared_ptr<CNComponent> makeEvaluateMenuComponent(std::string title, std::string tag, std::shared_ptr<CNSelectionModel> selectionModel,
                                                                   std::shared_ptr<CNVisitableListProvider> menuEntryListProvider);

    virtual std::shared_ptr<CNComponent> makeAddSTLFileActionComponent(std::shared_ptr<CNCommandInvoker> invoker,
                                                                       std::shared_ptr<CNComponentAdder> model,
                                                                       std::shared_ptr<CNSelectionModel> selectionModel,
                                                                       std::shared_ptr<CNMatcher> matcher);

    virtual std::shared_ptr<CNComponent> makeGridGeneratorActionComponent(std::shared_ptr<CNCommandInvoker> invoker,
                                                                          std::shared_ptr<CNComponentAdder> model,
                                                                          std::shared_ptr<CNSelectionModel> selectionModel,
                                                                          std::shared_ptr<CNMatcher> matcher);
};

#endif //COCOAIRMB_COCOAIRMBVIEWCOMPONENTFACTORY_H