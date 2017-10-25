#include "CocoaIRMBViewComponentFactory.h"
#include <CrossViews/MenuEntryPresenter/MenuEntryPresenter.h>

#include <CrossViews/TransActions/AddAction/AddAction.h>
#include <IRMB/GridGenerator/CreateComponentStrategy/CreateGridGeneratorComponentStrategy.h>
#include <IRMB/STLFile/CreateComponentStrategy/CreateSTLFileComponentStrategy.h>
#include "CocoaIRMB/CocoaFileFinder/CocoaFileFinder.h"

#include <CrossViews/DynamicMenuPresenter/DynamicMenuPresenter.h>
#include <CocoaViews/NSMenuItemBased/CocoaMenu/CocoaMenu.h>
#include <CocoaViews/NSMenuItemBased/CocoaMenu/Visitors/CocoaMenuComposingVisitor.h>
#include <CocoaViews/NSMenuItemBased/CocoaMenu/Visitors/CocoaMenuDecomposingVisitor.h>

#include <CrossViews/SelectionModel/SelectionModel.h>

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
    std::shared_ptr<CNComposer> composer = makeCNNullComposer();

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
    std::shared_ptr<CNComposer> composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}

std::shared_ptr<CNComponent> CocoaIRMBViewComponentFactory::makeEvaluateMenuComponent(std::string title, std::string tag, 
                                                                                      std::shared_ptr<SelectionModel> selectionModel, 
                                                                                      std::shared_ptr<MenuEntryListProvider> menuEntryListProvider) {
    CocoaMenuPtr view = makeCocoaMenu(title, tag);
    std::shared_ptr<CNComposer> composer = makeCNVisitingComposer(CocoaMenuComposingVisitor::getNewInstance(view),
                                                                  CocoaMenuDecomposingVisitor::getNewInstance(view));

    DynamicMenuPresenterPtr presenter = makeDynamicMenuPresenter(view, composer, menuEntryListProvider);
    selectionModel->attach(presenter);
    return makeCNComposable(presenter, composer);
}
