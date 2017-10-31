#include "QtIRMBMenuEntryListProvider.h"
#include "QtViews/QActionBased/QtAction/QtAction.h"
#include <CrossViews/CNMenuEntryPresenter/CNMenuEntryPresenter.h>
#include <Base/TransActionAppearances/CNFixedActionAppearance/CNFixedAppearance.h>
#include <CrossViews/TransActions/CNLoadAction/CNLoadAction.h>
#include <Hierarchies/CNComponent/CNComponent.h>
#include <CrossViews/CNHierarchicModel/API/CNHierarchicComponentAccess.h>
#include <CrossViews/CNSelectionModel/CNSelectionModel.h>
#include <IRMB/GridGenerator/GridGeneratorVisitor.h>
#include <IRMB/STLFile/STLFileVisitor.h>
#include "QtIRMB/QtGridGenerator/CreateComponentStrategy/CreateQtGridGeneratorComponentStrategy.h"
#include "QtIRMB/QtSTLFile/CreateComponentStrategy/CreateQtSTLFileComponentStrategy.h"

class MenuEntryListCreator;
typedef std::shared_ptr<MenuEntryListCreator> MenuEntryListCreatorPtr;
class MenuEntryListCreator
        : public CNVisitor,
          public STLFileVisitor,
          public GridGeneratorVisitor {
public:
    static MenuEntryListCreatorPtr getNewInstance(std::shared_ptr<CNComponentLoader> componentLoader, std::shared_ptr<CNMatcher> matcher) {
        return MenuEntryListCreatorPtr(new MenuEntryListCreator(componentLoader, matcher));
    }
    virtual ~MenuEntryListCreator() {}
private:
    MenuEntryListCreator(std::shared_ptr<CNComponentLoader> componentLoader, std::shared_ptr<CNMatcher> matcher)
            : componentLoader(componentLoader), matcher(matcher) {}

public:
    virtual std::vector<CNVisitablePtr> getMenuEntries() {
        return menuEntries;
    }

    void visit(std::shared_ptr<GridGenerator> gridGenerator) override {
        QtActionPtr view = QtAction::getNewInstance();
        CNFixedAppearancePtr appearance = CNFixedAppearance::getNewInstance(true, OFF, "Generate Grid");
        CNTransActionPtr action = CNLoadAction::getNewInstance(componentLoader,
                                                               CreateQtGridGeneratorComponentStrategy::getNewInstance(gridGenerator),
                                                               matcher);
        CNMenuEntryPresenterPtr presenter = CNMenuEntryPresenter::getNewInstance(view, appearance, action);
        view->setListener(presenter);
        menuEntries.push_back(presenter);
    }

    void visit(std::shared_ptr<STLFile> stlFile) override {
        QtActionPtr view = QtAction::getNewInstance();
        CNFixedAppearancePtr appearance = CNFixedAppearance::getNewInstance(true, OFF, "Show Geometry");
        CNTransActionPtr action = CNLoadAction::getNewInstance(componentLoader,
                                                               CreateQtSTLFileComponentStrategy::getNewInstance(stlFile),
                                                               matcher);
        CNMenuEntryPresenterPtr presenter = CNMenuEntryPresenter::getNewInstance(view, appearance, action);
        view->setListener(presenter);
        menuEntries.push_back(presenter);
    }

private:
    std::vector<CNVisitablePtr> menuEntries;
    std::shared_ptr<CNComponentLoader> componentLoader;
    std::shared_ptr<CNMatcher> matcher;
};

QtIRMBMenuEntryListProviderPtr QtIRMBMenuEntryListProvider::getNewInstance(std::shared_ptr<CNComponentLoader> componentLoader,
                                                                           std::shared_ptr<CNMatcher> matcher,
                                                                           std::shared_ptr<CNSelectionModel> selectionModel,
                                                                           std::shared_ptr<CNHierarchicComponentAccess> modelAccess) {
    return QtIRMBMenuEntryListProviderPtr(new QtIRMBMenuEntryListProvider(componentLoader, matcher, selectionModel, modelAccess));
}
QtIRMBMenuEntryListProvider::~QtIRMBMenuEntryListProvider() {}
QtIRMBMenuEntryListProvider::QtIRMBMenuEntryListProvider(std::shared_ptr<CNComponentLoader> componentLoader,
                                                         std::shared_ptr<CNMatcher> matcher,
                                                         std::shared_ptr<CNSelectionModel> selectionModel,
                                                         std::shared_ptr<CNHierarchicComponentAccess> modelAccess)
        : componentLoader(componentLoader), matcher(matcher), selectionModel(selectionModel), modelAccess(modelAccess) {}

const std::vector<CNVisitablePtr> QtIRMBMenuEntryListProvider::getVisitables() {
    if(!selectionModel->hasSelection())
        return std::vector<CNVisitablePtr>();

    CNComponentPtr selected = modelAccess->retrieve(selectionModel->getSelectedIndex());
    MenuEntryListCreatorPtr creator = MenuEntryListCreator::getNewInstance(componentLoader, matcher);
    try{
        selected->accept(creator);
        return creator->getMenuEntries();
    } catch(CNVisitableVisitorMismatchException& e) {
        return std::vector<CNVisitablePtr>();
    }
}
