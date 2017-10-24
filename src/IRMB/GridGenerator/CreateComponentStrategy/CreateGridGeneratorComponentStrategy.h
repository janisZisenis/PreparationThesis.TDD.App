#ifndef IRMB_CREATEGRIDGENERATORSTRATEGY_H
#define IRMB_CREATEGRIDGENERATORSTRATEGY_H

#include <CrossViews/TransActions/AddAction/CreateComponentStrategy.h>

class GridGenerator;
class CNComposer;

class CreateGridGeneratorComponentStrategy;
typedef std::shared_ptr<CreateGridGeneratorComponentStrategy> CreateGridGeneratorComponentStrategyPtr;

class CreateGridGeneratorComponentStrategy : public CreateComponentStrategy {
public:
    static CreateGridGeneratorComponentStrategyPtr getNewInstance();
    virtual ~CreateGridGeneratorComponentStrategy();
private:
    CreateGridGeneratorComponentStrategy();

public:
    virtual std::shared_ptr<CNComponent> createComponent() override;
};

#endif //IRMB_CREATEGRIDGENERATORSTRATEGY_H
