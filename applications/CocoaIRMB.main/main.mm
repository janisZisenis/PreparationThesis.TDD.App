#include <AppKit/AppKit.h>

#include <CodeBaseImp/CBCommandStack/CBCommandStack.h>

#include <CrossNative/CNComponent/CNComponent.h>
#include <CrossNative/CNDynamicHierarchy/CNDynamicHierarchy.h>

#include <CrossViews/SelectionModel/SelectionModelImp.h>
#include <CrossViews/HierarchicModel/HierarchicModel.h>

#include <IRMB/IRMBMatcherFactory/IRMBMatcherFactory.h>
#include "CocoaFileFinder.h"
#include "CocoaIRMBViewComponentFactory.h"
#include "CocoaIRMBSolutionItemFactory.h"
#include "CocoaIRMBPropertiesModelFactory.h"
#include "CocoaViews/CocoaViewMatcherFactory/CocoaViewMatcherFactory.h"

int main(int argc, char** argv) {
    SelectionModelImpPtr selectionModel = SelectionModelImp::getNewInstance();
    HierarchicModelPtr model = HierarchicModel::getNewInstance();
    CBCommandStackPtr commandStack = CBCommandStack::getNewInstance();


    NSApplication* application = [NSApplication sharedApplication];
    [application activateIgnoringOtherApps:true];

    IRMBMatcherFactoryPtr irmbMatcherFactory = IRMBMatcherFactory::getNewInstance();
    CocoaIRMBViewComponentFactoryPtr componentFactory = CocoaIRMBViewComponentFactory::getNewInstance();

    CNComponentPtr shell = componentFactory->makeShellComponent();
    CNComponentPtr menuBar = componentFactory->makeMenuBarComponent();
    CNComponentPtr solutionExplorer = componentFactory->makeSolutionExplorerComponent(selectionModel, model, CocoaIRMBSolutionItemFactory::getNewInstance());
    CNComponentPtr propertiesExplorer = componentFactory->makePropertiesExplorerComponent(selectionModel, model, CocoaIRMBPropertiesModelFactory::getNewInstance());
    CNComponentPtr editMenu = componentFactory->makeMenuComponent("Edit", "edit-menu");
    CNComponentPtr addMenu = componentFactory->makeMenuComponent("Add", "add-menu");
    CNComponentPtr undoMenuEntry = componentFactory->makeUndoActionComponent(commandStack);
    CNComponentPtr redoMenuEntry = componentFactory->makeRedoActionComponent(commandStack);
    CNComponentPtr removeMenuEntry = componentFactory->makeRemoveActionComponent(selectionModel, model, commandStack);
    CNComponentPtr stlMenuEntry = componentFactory->makeAddSTLFileActionComponent(commandStack, model, selectionModel,
                                                                                  irmbMatcherFactory->makeSTLFileParentTypeMatcher());
    CNComponentPtr gridGeneratorMenuEntry = componentFactory->makeGridGeneratorActionComponent(commandStack, model, selectionModel,
                                                                                               irmbMatcherFactory->makeGridGeneratorParentTypeMatcher());

    CocoaViewMatcherFactoryPtr viewMatcherFactory = CocoaViewMatcherFactory::getNewInstance();

    CNDynamicHierarchyPtr viewHierarchy = CNDynamicHierarchy::getNewInstance();
    viewHierarchy->load(shell, viewMatcherFactory->makeTopLevelMatcher());
    viewHierarchy->load(solutionExplorer, viewMatcherFactory->makeShellTypeMatcher());
    viewHierarchy->load(propertiesExplorer, viewMatcherFactory->makeShellTypeMatcher());
    viewHierarchy->load(menuBar, viewMatcherFactory->makeTopLevelMatcher());

    viewHierarchy->load(editMenu, viewMatcherFactory->makeMenuBarTypeMatcher());
    viewHierarchy->load(addMenu, viewMatcherFactory->makeMenuBarTypeMatcher());
    viewHierarchy->load(undoMenuEntry, viewMatcherFactory->makeTagMatcher("edit-menu"));
    viewHierarchy->load(redoMenuEntry, viewMatcherFactory->makeTagMatcher("edit-menu"));
    viewHierarchy->load(removeMenuEntry, viewMatcherFactory->makeTagMatcher("edit-menu"));
    viewHierarchy->load(stlMenuEntry, viewMatcherFactory->makeTagMatcher("add-menu"));
    viewHierarchy->load(gridGeneratorMenuEntry, viewMatcherFactory->makeTagMatcher("add-menu"));

    [application run];
    return 0;
}