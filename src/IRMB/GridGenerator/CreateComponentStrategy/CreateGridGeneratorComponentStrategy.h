#ifndef IRMB_CREATEGRIDGENERATORSTRATEGY_H
#define IRMB_CREATEGRIDGENERATORSTRATEGY_H

#include <CrossNative/TransActions/CNLoadAction/CNCreateComponentStrategy.h>

class GridGenerator;
class CNComposer;

class CreateQtGridGeneratorComponentStrategy;
typedef std::shared_ptr<CreateQtGridGeneratorComponentStrategy> CreateGridGeneratorComponentStrategyPtr;

class CreateQtGridGeneratorComponentStrategy : public CNCreateComponentStrategy {
public:
    static CreateGridGeneratorComponentStrategyPtr getNewInstance();
    virtual ~CreateQtGridGeneratorComponentStrategy();
private:
    CreateQtGridGeneratorComponentStrategy();

public:
    virtual std::shared_ptr<CNComponent> createComponent() override;
};

#endif //IRMB_CREATEGRIDGENERATORSTRATEGY_H
