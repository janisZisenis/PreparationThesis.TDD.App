#include "CocoaIRMBMenuEntryListProvider.h"
#include "CocoaViews/NSMenuItemBased/CocoaMenuItem/CocoaMenuItem.h"
#include "CrossViews/MenuEntryPresenter/MenuEntryPresenter.h"
#include "CodeBaseImp/CBActionAppearance/CBFixedActionAppearance/CBFixedAppearance.h"
#include <CrossNative/TransActions/CNLoadAction/CNLoadAction.h>
#include <CrossNative/CNComponent/CNComponent.h>
#include <CrossViews/HierarchicModel/API/HierarchicModelAccess.h>
#include <CrossViews/SelectionModel/SelectionModel.h>
#include <IRMB/GridGenerator/GridGeneratorVisitor.h>
#include <IRMB/STLFile/STLFileVisitor.h>
#include "CocoaIRMB/CocoaGridGenerator/CreateComponentStrategy/CreateCocoaGridGeneratorComponentStrategy.h"
#include "CocoaIRMB/CocoaSTLFile/CreateComponentStrategy/CreateCocoaSTLFileComponentStrategy.h"

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
        CocoaMenuItemPtr view = CocoaMenuItem::getNewInstance();
        CBFixedAppearancePtr appearance = CBFixedAppearance::getNewInstance(true, OFF, "Generate Grid");
        CBTransActionPtr action = CNLoadAction::getNewInstance(componentLoader,
                                                               CreateCocoaGridGeneratorComponentStrategy::getNewInstance(gridGenerator),
                                                               matcher);
        MenuEntryPresenterPtr presenter = MenuEntryPresenter::getNewInstance(view, appearance, action);
        view->setListener(presenter);
        menuEntries.push_back(presenter);
    }

    void visit(std::shared_ptr<STLFile> stlFile) override {
        CocoaMenuItemPtr view = CocoaMenuItem::getNewInstance();
        CBFixedAppearancePtr appearance = CBFixedAppearance::getNewInstance(true, OFF, "Show Geometry");
        CBTransActionPtr action = CNLoadAction::getNewInstance(componentLoader,
                                                               CreateCocoaSTLFileComponentStrategy::getNewInstance(stlFile),
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

CocoaIRMBMenuEntryListProviderPtr CocoaIRMBMenuEntryListProvider::getNewInstance(std::shared_ptr<CNComponentLoader> componentLoader,
                                                                           std::shared_ptr<CNMatcher> matcher,
                                                                           std::shared_ptr<SelectionModel> selectionModel,
                                                                           std::shared_ptr<HierarchicModelAccess> modelAccess) {
    return CocoaIRMBMenuEntryListProviderPtr(new CocoaIRMBMenuEntryListProvider(componentLoader, matcher, selectionModel, modelAccess));
}
CocoaIRMBMenuEntryListProvider::~CocoaIRMBMenuEntryListProvider() {}
CocoaIRMBMenuEntryListProvider::CocoaIRMBMenuEntryListProvider(std::shared_ptr<CNComponentLoader> componentLoader,
                                                         std::shared_ptr<CNMatcher> matcher,
                                                         std::shared_ptr<SelectionModel> selectionModel,
                                                         std::shared_ptr<HierarchicModelAccess> modelAccess)
        : componentLoader(componentLoader), matcher(matcher), selectionModel(selectionModel), modelAccess(modelAccess) {}

const std::vector<CNVisitablePtr> CocoaIRMBMenuEntryListProvider::getMenuEntryList() {
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
