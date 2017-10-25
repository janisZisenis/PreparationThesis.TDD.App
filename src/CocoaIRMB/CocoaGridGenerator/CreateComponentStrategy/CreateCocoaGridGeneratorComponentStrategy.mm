#include "CreateCocoaGridGeneratorComponentStrategy.h"
#include <CrossNative/CNComponent/CNComposable/CNComposable.h>
#include <CrossNative/CNComposer/CNNullComposer.h>
#include "CocoaIRMB/CocoaGridGenerator/CocoaGridGenerator.h"

CreateCocoaGridGeneratorComponentStrategyPtr CreateCocoaGridGeneratorComponentStrategy::getNewInstance(std::shared_ptr<GridGenerator> gridGenerator) {
    return CreateCocoaGridGeneratorComponentStrategyPtr(new CreateCocoaGridGeneratorComponentStrategy(gridGenerator));
}
CreateCocoaGridGeneratorComponentStrategy::~CreateCocoaGridGeneratorComponentStrategy() {}
CreateCocoaGridGeneratorComponentStrategy::CreateCocoaGridGeneratorComponentStrategy(std::shared_ptr<GridGenerator> gridGenerator)
        : gridGenerator(gridGenerator) {}

CNComponentPtr CreateCocoaGridGeneratorComponentStrategy::createComponent() {
    CocoaGridGeneratorPtr CocoaGridGenerator = CocoaGridGenerator::getNewInstance(gridGenerator);
    CNComposerPtr composer = CNNullComposer::getNewInstance();
    return CNComposable::getNewInstance(CocoaGridGenerator, composer);
}
