#include "CocoaIRMBViewComponentFactory.h"
#include <CrossViews/MenuEntryPresenter/MenuEntryPresenter.h>

#include <CrossViews/TransActions/AddAction/AddAction.h>
#include <IRMB/GridGenerator/CreateComponentStrategy/CreateGridGeneratorComponentStrategy.h>
#include <IRMB/STLFile/CreateComponentStrategy/CreateSTLFileComponentStrategy.h>
#include "CocoaFileFinder.h"

CocoaIRMBViewComponentFactoryPtr CocoaIRMBViewComponentFactory::getNewInstance() {
    return CocoaIRMBViewComponentFactoryPtr(new CocoaIRMBViewComponentFactory());
}
CocoaIRMBViewComponentFactory::~CocoaIRMBViewComponentFactory() {}
CocoaIRMBViewComponentFactory::CocoaIRMBViewComponentFactory() {}

std::shared_ptr<CNComponent> CocoaIRMBViewComponentFactory::makeAddSTLFileActionComponent(std::shared_ptr<CBCommandInvoker> invoker,
                                                          std::shared_ptr<AddingHierarchicModel> model,
                                                          std::shared_ptr<SelectionModel> selectionModel,
                                                          std::shared_ptr<CNMatcher> matcher) {
    std::shared_ptr<MenuEntryView> view = makeMenuEntryView();
    std::shared_ptr<CBTransActionAppearance> appearance = makeCBFixedTransActionAppearance(true, OFF, "STL File");
    CBTransActionPtr action = AddAction::getNewInstance(invoker, model, selectionModel,
                                                        CreateSTLFileComponentStrategy::getNewInstance(CocoaFileFinder::getNewInstance()),
                                                        matcher);
    std::shared_ptr<MenuEntryPresenter> presenter = makeMenuEntryPresenter(view, appearance, action);
    std::shared_ptr<CNComposer> composer = makeNullComposer();

    return makeCNComposable(presenter, composer);
}

std::shared_ptr<CNComponent> CocoaIRMBViewComponentFactory::makeGridGeneratorActionComponent(std::shared_ptr<CBCommandInvoker> invoker,
                                                                                             std::shared_ptr<AddingHierarchicModel> model,
                                                                                             std::shared_ptr<SelectionModel> selectionModel,
                                                                                             std::shared_ptr<CNMatcher> matcher) {
    std::shared_ptr<MenuEntryView> view = makeMenuEntryView();
    std::shared_ptr<CBTransActionAppearance> appearance = makeCBFixedTransActionAppearance(true, OFF, "Grid Generator");
    CBTransActionPtr action = AddAction::getNewInstance(invoker, model, selectionModel,
                                                        CreateGridGeneratorComponentStrategy::getNewInstance(), matcher);
    std::shared_ptr<MenuEntryPresenter> presenter = makeMenuEntryPresenter(view, appearance, action);
    std::shared_ptr<CNComposer> composer = makeNullComposer();

    return makeCNComposable(presenter, composer);
}
