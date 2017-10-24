#include <QApplication>

#include <CodeBaseImp/CBCommandStack/CBCommandStack.h>

#include <CrossNative/CNComponent/CNComponent.h>
#include <CrossNative/CNDynamicHierarchy/CNDynamicHierarchy.h>

#include <CrossViews/SelectionModel/SelectionModelImp.h>
#include <CrossViews/HierarchicModel/HierarchicModel.h>

#include <IRMB/IRMBMatcherFactory/IRMBMatcherFactory.h>
#include "QtFileFinder.h"
#include "QtIRMBViewComponentFactory.h"
#include "QtViews/QtViewMatcherFactory/QtViewMatcherFactory.h"
#include "QtIRMBSolutionItemFactory.h"
#include "QtIRMBPropertiesModelFactory.h"

int main(int argc, char** argv) {
    SelectionModelImpPtr selectionModel = SelectionModelImp::getNewInstance();
    HierarchicModelPtr model = HierarchicModel::getNewInstance();
    CBCommandStackPtr commandStack = CBCommandStack::getNewInstance();


    QApplication a(argc, argv);

    IRMBMatcherFactoryPtr irmbMatcherFactory = IRMBMatcherFactory::getNewInstance();
    QtIRMBViewComponentFactoryPtr componentFactory = QtIRMBViewComponentFactory::getNewInstance();

    CNComponentPtr shell = componentFactory->makeShellComponent();
    CNComponentPtr menuBar = componentFactory->makeMenuBarComponent();
    CNComponentPtr solutionExplorer = componentFactory->makeSolutionExplorerComponent(selectionModel, model, QtIRMBSolutionItemFactory::getNewInstance());
    CNComponentPtr propertiesExplorer = componentFactory->makePropertiesExplorerComponent(selectionModel, model, QtIRMBPropertiesModelFactory::getNewInstance());
    CNComponentPtr editMenu = componentFactory->makeMenuComponent("Edit", "edit-menu");
    CNComponentPtr addMenu = componentFactory->makeMenuComponent("Add", "add-menu");
    CNComponentPtr undoMenuEntry = componentFactory->makeUndoActionComponent(commandStack);
    CNComponentPtr redoMenuEntry = componentFactory->makeRedoActionComponent(commandStack);
    CNComponentPtr removeMenuEntry = componentFactory->makeRemoveActionComponent(selectionModel, model, commandStack);
    CNComponentPtr stlMenuEntry = componentFactory->makeAddSTLFileActionComponent(commandStack, model, selectionModel,
                                                                                  irmbMatcherFactory->makeSTLFileParentTypeMatcher());
    CNComponentPtr gridGeneratorMenuEntry = componentFactory->makeGridGeneratorActionComponent(commandStack, model, selectionModel,
                                                                                               irmbMatcherFactory->makeGridGeneratorParentTypeMatcher());

    QtViewMatcherFactoryPtr viewMatcherFactory = QtViewMatcherFactory::getNewInstance();

    CNDynamicHierarchyPtr viewHierarchy = CNDynamicHierarchy::getNewInstance();
    viewHierarchy->load(shell, viewMatcherFactory->makeTopLevelMatcher());
    viewHierarchy->load(solutionExplorer, viewMatcherFactory->makeShellTypeMatcher());
    viewHierarchy->load(propertiesExplorer, viewMatcherFactory->makeShellTypeMatcher());
    viewHierarchy->load(menuBar, viewMatcherFactory->makeShellTypeMatcher());

    viewHierarchy->load(editMenu, viewMatcherFactory->makeMenuBarTypeMatcher());
    viewHierarchy->load(addMenu, viewMatcherFactory->makeMenuBarTypeMatcher());
    viewHierarchy->load(undoMenuEntry, viewMatcherFactory->makeTagMatcher("edit-menu"));
    viewHierarchy->load(redoMenuEntry, viewMatcherFactory->makeTagMatcher("edit-menu"));
    viewHierarchy->load(removeMenuEntry, viewMatcherFactory->makeTagMatcher("edit-menu"));
    viewHierarchy->load(stlMenuEntry, viewMatcherFactory->makeTagMatcher("add-menu"));
    viewHierarchy->load(gridGeneratorMenuEntry, viewMatcherFactory->makeTagMatcher("add-menu"));

    return a.exec();
}