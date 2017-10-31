#include "CocoaIRMBViewComponentFactory.h"
#include <CrossViews/CNMenuEntryPresenter/CNMenuEntryPresenter.h>

#include <CrossViews/TransActions/CNAddAction/CNAddAction.h>
#include <IRMB/GridGenerator/CreateComponentStrategy/CreateGridGeneratorComponentStrategy.h>
#include <IRMB/STLFile/CreateComponentStrategy/CreateSTLFileComponentStrategy.h>
#include "CocoaIRMB/CocoaFileFinder/CocoaFileFinder.h"

#include <CrossViews/CNDynamicMenuPresenter/CNDynamicMenuPresenter.h>
#include <CocoaViews/NSMenuItemBased/CocoaMenu/CocoaMenu.h>
#include <CocoaViews/NSMenuItemBased/CocoaMenu/Visitors/CocoaMenuComposingVisitor.h>
#include <CocoaViews/NSMenuItemBased/CocoaMenu/Visitors/CocoaMenuDecomposingVisitor.h>

#include <CrossViews/CNSelectionModel/CNSelectionModel.h>

CocoaIRMBViewComponentFactoryPtr CocoaIRMBViewComponentFactory::getNewInstance() {
    return CocoaIRMBViewComponentFactoryPtr(new CocoaIRMBViewComponentFactory());
}
CocoaIRMBViewComponentFactory::~CocoaIRMBViewComponentFactory() {}
CocoaIRMBViewComponentFactory::CocoaIRMBViewComponentFactory() {}

std::shared_ptr<CNComponent> CocoaIRMBViewComponentFactory::makeAddSTLFileActionComponent(std::shared_ptr<CNCommandInvoker> invoker,
                                                                                          std::shared_ptr<CNComponentAdder> model,
                                                                                          std::shared_ptr<CNSelectionModel> selectionModel,
                                                                                          std::shared_ptr<CNMatcher> matcher) {
    std::shared_ptr<CNMenuEntryView> view = makeMenuEntryView();
    std::shared_ptr<CNTransActionAppearance> appearance = makeCBFixedTransActionAppearance(true, OFF, "STL File");
    CNTransActionPtr action = CNAddAction::getNewInstance(invoker, model, selectionModel,
                                                          CreateSTLFileComponentStrategy::getNewInstance(CocoaFileFinder::getNewInstance()),
                                                          matcher);
    std::shared_ptr<CNMenuEntryPresenter> presenter = makeMenuEntryPresenter(view, appearance, action);
    std::shared_ptr<CNComposer> composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}

std::shared_ptr<CNComponent> CocoaIRMBViewComponentFactory::makeGridGeneratorActionComponent(std::shared_ptr<CNCommandInvoker> invoker,
                                                                                             std::shared_ptr<CNComponentAdder> model,
                                                                                             std::shared_ptr<CNSelectionModel> selectionModel,
                                                                                             std::shared_ptr<CNMatcher> matcher) {
    std::shared_ptr<CNMenuEntryView> view = makeMenuEntryView();
    std::shared_ptr<CNTransActionAppearance> appearance = makeCBFixedTransActionAppearance(true, OFF, "Grid Generator");
    CNTransActionPtr action = CNAddAction::getNewInstance(invoker, model, selectionModel,
                                                        CreateGridGeneratorComponentStrategy::getNewInstance(), matcher);
    std::shared_ptr<CNMenuEntryPresenter> presenter = makeMenuEntryPresenter(view, appearance, action);
    std::shared_ptr<CNComposer> composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}

std::shared_ptr<CNComponent> CocoaIRMBViewComponentFactory::makeEvaluateMenuComponent(std::string title, std::string tag,
                                                                                      std::shared_ptr<CNSelectionModel> selectionModel,
                                                                                      std::shared_ptr<CNComponentListProvider> menuEntryListProvider) {
    CocoaMenuPtr view = makeCocoaMenu(title, tag);
    std::shared_ptr<CNComposer> composer = makeCNVisitingComposer(CocoaMenuComposingVisitor::getNewInstance(view),
                                                                  CocoaMenuDecomposingVisitor::getNewInstance(view));

    CNDynamicMenuPresenterPtr presenter = makeDynamicMenuPresenter(view, composer, menuEntryListProvider);
    selectionModel->attach(presenter);
    return makeCNComposable(presenter, composer);
}
