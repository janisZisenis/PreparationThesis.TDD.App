#include "QtIRMBMenuEntryListProvider.h"
#include "QtViews/QActionBased/QtAction/QtAction.h"
#include "CrossViews/MenuEntryPresenter/MenuEntryPresenter.h"
#include "CodeBaseImp/CBActionAppearance/CBFixedActionAppearance/CBFixedAppearance.h"
#include <CrossNative/TransActions/CNLoadAction/CNLoadAction.h>
#include <CrossNative/CNComponent/CNComponent.h>
#include <CrossViews/HierarchicModel/API/HierarchicModelAccess.h>
#include <CrossViews/SelectionModel/SelectionModel.h>
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
        CBFixedAppearancePtr appearance = CBFixedAppearance::getNewInstance(true, OFF, "Generate Grid");
        CBTransActionPtr action = CNLoadAction::getNewInstance(componentLoader,
                                                               CreateQtGridGeneratorComponentStrategy::getNewInstance(gridGenerator),
                                                               matcher);
        MenuEntryPresenterPtr presenter = MenuEntryPresenter::getNewInstance(view, appearance, action);
        view->setListener(presenter);
        menuEntries.push_back(presenter);
    }

    void visit(std::shared_ptr<STLFile> stlFile) override {
        QtActionPtr view = QtAction::getNewInstance();
        CBFixedAppearancePtr appearance = CBFixedAppearance::getNewInstance(true, OFF, "Show Geometry");
        CBTransActionPtr action = CNLoadAction::getNewInstance(componentLoader,
                                                               CreateQtSTLFileComponentStrategy::getNewInstance(stlFile),
                                                               matcher);
        MenuEntryPresenterPtr presenter = MenuEntryPresenter::getNewInstance(view, appearance, action);
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
                                                                           std::shared_ptr<SelectionModel> selectionModel,
                                                                           std::shared_ptr<HierarchicModelAccess> modelAccess) {
    return QtIRMBMenuEntryListProviderPtr(new QtIRMBMenuEntryListProvider(componentLoader, matcher, selectionModel, modelAccess));
}
QtIRMBMenuEntryListProvider::~QtIRMBMenuEntryListProvider() {}
QtIRMBMenuEntryListProvider::QtIRMBMenuEntryListProvider(std::shared_ptr<CNComponentLoader> componentLoader,
                                                         std::shared_ptr<CNMatcher> matcher,
                                                         std::shared_ptr<SelectionModel> selectionModel,
                                                         std::shared_ptr<HierarchicModelAccess> modelAccess)
        : componentLoader(componentLoader), matcher(matcher), selectionModel(selectionModel), modelAccess(modelAccess) {}

const std::vector<CNVisitablePtr> QtIRMBMenuEntryListProvider::getMenuEntryList() {
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
