#include "CreateGridGeneratorComponentStrategy.h"
#include "IRMB/GridGenerator/Implementation/GridGeneratorImp.h"
#include "IRMB/GridGenerator/Visitors/GridGeneratorComposingVisitor.h"
#include "IRMB/GridGenerator/Visitors/GridGeneratorDecomposingVisitor.h"
#include <CrossNative/CNComponent/CNComposable/CNComposable.h>
#include <CrossNative/CNComposer/CNVisitingComposer/CNVisitingComposer.h>

CreateGridGeneratorComponentStrategyPtr CreateQtGridGeneratorComponentStrategy::getNewInstance() {
    return CreateGridGeneratorComponentStrategyPtr(new CreateQtGridGeneratorComponentStrategy());
}
CreateQtGridGeneratorComponentStrategy::~CreateQtGridGeneratorComponentStrategy() {}
CreateQtGridGeneratorComponentStrategy::CreateQtGridGeneratorComponentStrategy() {}

CNComponentPtr CreateQtGridGeneratorComponentStrategy::createComponent() {
    static int i;

    GridGeneratorPtr gridGenerator = GridGeneratorImp::getNewInstance("MyFancyGridGenerator (" + std::to_string(i++) + ")", 10, 10, 10, 1, "D3Q7");
    GridGeneratorComposingVisitorPtr composingVisitor = GridGeneratorComposingVisitor::getNewInstance(gridGenerator);
    GridGeneratorDecomposingVisitorPtr decomposingVisitor = GridGeneratorDecomposingVisitor::getNewInstance(gridGenerator);
    CNComposerPtr composer = CNVisitingComposer::getNewInstance(composingVisitor, decomposingVisitor);

    return CNComposable::getNewInstance(gridGenerator, composer);
}
