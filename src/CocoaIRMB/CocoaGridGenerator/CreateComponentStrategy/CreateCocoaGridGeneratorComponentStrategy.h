#ifndef COCOAIRMB_CREATECOCOAGRIDGENERATORSTRATEGY_H
#define COCOAIRMB_CREATECOCOAGRIDGENERATORSTRATEGY_H

#include <CrossViews/TransActions/CNLoadAction/CNCreateComponentStrategy.h>

class GridGenerator;
class CNComposer;

class CreateCocoaGridGeneratorComponentStrategy;
typedef std::shared_ptr<CreateCocoaGridGeneratorComponentStrategy> CreateCocoaGridGeneratorComponentStrategyPtr;

class CreateCocoaGridGeneratorComponentStrategy : public CNCreateComponentStrategy {
public:
    static CreateCocoaGridGeneratorComponentStrategyPtr getNewInstance(std::shared_ptr<GridGenerator> gridGenerator);
    virtual ~CreateCocoaGridGeneratorComponentStrategy();
private:
    CreateCocoaGridGeneratorComponentStrategy(std::shared_ptr<GridGenerator> gridGenerator);

public:
    virtual std::shared_ptr<CNComponent> createComponent() override;

private:
    std::shared_ptr<GridGenerator> gridGenerator;
};

#endif //COCOAIRMB_CREATECOCOAGRIDGENERATORSTRATEGY_H
