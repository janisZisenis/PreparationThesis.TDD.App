#include "QtIRMBViewComponentFactory.h"
#include <CrossViews/MenuEntryPresenter/MenuEntryPresenter.h>

#include <CrossViews/TransActions/AddAction/AddAction.h>
#include <IRMB/GridGenerator/CreateComponentStrategy/CreateGridGeneratorComponentStrategy.h>
#include <IRMB/STLFile/CreateComponentStrategy/CreateSTLFileComponentStrategy.h>
#include "QtIRMB/QtFileFinder/QtFileFinder.h"

#include <QtViews/QActionBased/QtAction/QtAction.h>
#include <QtViews/QActionBased/QtMenu/QtMenu.h>
#include <CrossViews/DynamicMenuPresenter/DynamicMenuPresenter.h>
#include <QtViews/QActionBased/QtMenu/Visitors/QtMenuComposingVisitor.h>
#include <QtViews/QActionBased/QtMenu/Visitors/QtMenuDecomposingVisitor.h>

#include <CrossViews/SelectionModel/SelectionModel.h>

QtIRMBViewComponentFactoryPtr QtIRMBViewComponentFactory::getNewInstance() {
    return QtIRMBViewComponentFactoryPtr(new QtIRMBViewComponentFactory());
}
QtIRMBViewComponentFactory::~QtIRMBViewComponentFactory() {}
QtIRMBViewComponentFactory::QtIRMBViewComponentFactory() {}

std::shared_ptr<CNComponent> QtIRMBViewComponentFactory::makeAddSTLFileActionComponent(std::shared_ptr<CBCommandInvoker> invoker,
                                                          std::shared_ptr<AddingHierarchicModel> model,
                                                          SelectionModelPtr selectionModel,
                                                          std::shared_ptr<CNMatcher> matcher) {
    std::shared_ptr<QtAction> view = makeQtAction();
    std::shared_ptr<CBTransActionAppearance> appearance = makeCBFixedTransActionAppearance(true, OFF, "STL File");
    CBTransActionPtr action = AddAction::getNewInstance(invoker, model, selectionModel,
                                                        CreateSTLFileComponentStrategy::getNewInstance(QtFileFinder::getNewInstance()),
                                                        matcher);
    std::shared_ptr<MenuEntryPresenter> presenter = makeMenuEntryPresenter(view, appearance, action);
    std::shared_ptr<CNComposer> composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}

std::shared_ptr<CNComponent> QtIRMBViewComponentFactory::makeGridGeneratorActionComponent(std::shared_ptr<CBCommandInvoker> invoker,
                                                                                          std::shared_ptr<AddingHierarchicModel> model,
                                                                                          SelectionModelPtr selectionModel,
                                                                                          std::shared_ptr<CNMatcher> matcher) {
    std::shared_ptr<QtAction> view = makeQtAction();
    std::shared_ptr<CBTransActionAppearance> appearance = makeCBFixedTransActionAppearance(true, OFF, "Grid Generator");
    CBTransActionPtr action = AddAction::getNewInstance(invoker, model, selectionModel, CreateGridGeneratorComponentStrategy::getNewInstance(), matcher);
    std::shared_ptr<MenuEntryPresenter> presenter = makeMenuEntryPresenter(view, appearance, action);
    std::shared_ptr<CNComposer> composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}

std::shared_ptr<CNComponent> QtIRMBViewComponentFactory::makeEvaluateMenuComponent(std::string title, std::string tag, SelectionModelPtr selectionModel,
                                                                                   std::shared_ptr<MenuEntryListProvider> menuEntryListProvider) {
    std::shared_ptr<QtMenu> view = makeQtMenu(title, tag);
    std::shared_ptr<CNComposer> composer = makeCNVisitingComposer(QtMenuComposingVisitor::getNewInstance(view),
                                                                  QtMenuDecomposingVisitor::getNewInstance(view));

    DynamicMenuPresenterPtr presenter = makeDynamicMenuPresenter(view, composer, menuEntryListProvider);
    selectionModel->attach(presenter);
    return makeCNComposable(presenter, composer);
}
