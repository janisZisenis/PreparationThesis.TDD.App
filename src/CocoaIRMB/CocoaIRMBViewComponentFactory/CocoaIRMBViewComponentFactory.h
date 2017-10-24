#ifndef COCOAIRMB_COCOAIRMBVIEWCOMPONENTFACTORY_H
#define COCOAIRMB_COCOAIRMBVIEWCOMPONENTFACTORY_H

#include <CocoaViews/CocoaViewComponentFactory/CocoaViewComponentFactory.h>

class CBCommandInvoker;
class AddingHierarchicModel;
class SelectionModel;
class CNMatcher;
class FileFinder;

class CocoaIRMBViewComponentFactory;
typedef std::shared_ptr<CocoaIRMBViewComponentFactory> CocoaIRMBViewComponentFactoryPtr;

class CocoaIRMBViewComponentFactory : public CocoaViewComponentFactory {
public:
    static CocoaIRMBViewComponentFactoryPtr getNewInstance();
    virtual ~CocoaIRMBViewComponentFactory();
private:
    CocoaIRMBViewComponentFactory();

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

#endif //COCOAIRMB_COCOAIRMBVIEWCOMPONENTFACTORY_H