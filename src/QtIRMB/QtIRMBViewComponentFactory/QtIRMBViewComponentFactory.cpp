#include "QtIRMBViewComponentFactory.h"
#include <CrossViews/CNMenuEntryPresenter/CNMenuEntryPresenter.h>

#include <CrossViews/TransActions/CNAddAction/CNAddAction.h>
#include <IRMB/GridGenerator/CreateComponentStrategy/CreateGridGeneratorComponentStrategy.h>
#include <IRMB/STLFile/CreateComponentStrategy/CreateSTLFileComponentStrategy.h>
#include "QtIRMB/QtFileFinder/QtFileFinder.h"

#include <QtViews/QActionBased/QtAction/QtAction.h>
#include <QtViews/QActionBased/QtMenu/QtMenu.h>
#include <CrossViews/CNDynamicMenuPresenter/CNDynamicMenuPresenter.h>
#include <QtViews/QActionBased/QtMenu/Visitors/QtMenuComposingVisitor.h>
#include <QtViews/QActionBased/QtMenu/Visitors/QtMenuDecomposingVisitor.h>

#include <CrossViews/CNSelectionModel/CNSelectionModel.h>

QtIRMBViewComponentFactoryPtr QtIRMBViewComponentFactory::getNewInstance() {
    return QtIRMBViewComponentFactoryPtr(new QtIRMBViewComponentFactory());
}
QtIRMBViewComponentFactory::~QtIRMBViewComponentFactory() {}
QtIRMBViewComponentFactory::QtIRMBViewComponentFactory() {}

std::shared_ptr<CNComponent> QtIRMBViewComponentFactory::makeAddSTLFileActionComponent(std::shared_ptr<CNCommandInvoker> invoker,
                                                                                       std::shared_ptr<CNComponentAdder> model,
                                                                                       CNSelectionModelPtr selectionModel,
                                                                                       std::shared_ptr<CNMatcher> matcher) {
    std::shared_ptr<QtAction> view = makeQtAction();
    std::shared_ptr<CNTransActionAppearance> appearance = makeCBFixedTransActionAppearance(true, OFF, "STL File");
    CNTransActionPtr action = CNAddAction::getNewInstance(invoker, model, selectionModel,
                                                        CreateSTLFileComponentStrategy::getNewInstance(QtFileFinder::getNewInstance()),
                                                        matcher);
    std::shared_ptr<CNMenuEntryPresenter> presenter = makeMenuEntryPresenter(view, appearance, action);
    std::shared_ptr<CNComposer> composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}

std::shared_ptr<CNComponent> QtIRMBViewComponentFactory::makeGridGeneratorActionComponent(std::shared_ptr<CNCommandInvoker> invoker,
                                                                                          std::shared_ptr<CNComponentAdder> model,
                                                                                          CNSelectionModelPtr selectionModel,
                                                                                          std::shared_ptr<CNMatcher> matcher) {
    std::shared_ptr<QtAction> view = makeQtAction();
    std::shared_ptr<CNTransActionAppearance> appearance = makeCBFixedTransActionAppearance(true, OFF, "Grid Generator");
    CNTransActionPtr action = CNAddAction::getNewInstance(invoker, model, selectionModel, CreateGridGeneratorComponentStrategy::getNewInstance(), matcher);
    std::shared_ptr<CNMenuEntryPresenter> presenter = makeMenuEntryPresenter(view, appearance, action);
    std::shared_ptr<CNComposer> composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}

std::shared_ptr<CNComponent> QtIRMBViewComponentFactory::makeEvaluateMenuComponent(std::string title, std::string tag, CNSelectionModelPtr selectionModel,
                                                                                   std::shared_ptr<CNVisitableListProvider> menuEntryListProvider) {
    std::shared_ptr<QtMenu> view = makeQtMenu(title, tag);
    std::shared_ptr<CNComposer> composer = makeCNVisitingComposer(QtMenuComposingVisitor::getNewInstance(view),
                                                                  QtMenuDecomposingVisitor::getNewInstance(view));

    CNDynamicMenuPresenterPtr presenter = makeDynamicMenuPresenter(view, composer, menuEntryListProvider);
    selectionModel->attach(presenter);
    return makeCNComposable(presenter, composer);
}
