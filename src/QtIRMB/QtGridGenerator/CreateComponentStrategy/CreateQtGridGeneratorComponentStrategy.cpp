#include "CreateQtGridGeneratorComponentStrategy.h"
#include <Hierarchies/CNComponent/CNComposable/CNComposable.h>
#include <Hierarchies/CNComposer/CNNullComposer.h>
#include "QtIRMB/QtGridGenerator/QtGridGenerator.h"

CreateQtGridGeneratorComponentStrategyPtr CreateQtGridGeneratorComponentStrategy::getNewInstance(std::shared_ptr<GridGenerator> gridGenerator) {
    return CreateQtGridGeneratorComponentStrategyPtr(new CreateQtGridGeneratorComponentStrategy(gridGenerator));
}
CreateQtGridGeneratorComponentStrategy::~CreateQtGridGeneratorComponentStrategy() {}
CreateQtGridGeneratorComponentStrategy::CreateQtGridGeneratorComponentStrategy(std::shared_ptr<GridGenerator> gridGenerator)
        : gridGenerator(gridGenerator) {}

CNComponentPtr CreateQtGridGeneratorComponentStrategy::createComponent() {
    QtGridGeneratorPtr qtGridGenerator = QtGridGenerator::getNewInstance(gridGenerator);
    CNComposerPtr composer = CNNullComposer::getNewInstance();
    return CNComposable::getNewInstance(qtGridGenerator, composer);
}
