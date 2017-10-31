#ifndef QTIRMB_CREATEQTGRIDGENERATORSTRATEGY_H
#define QTIRMB_CREATEQTGRIDGENERATORSTRATEGY_H

#include <CrossViews/TransActions/CNLoadAction/CNCreateComponentStrategy.h>

class GridGenerator;
class CNComposer;

class CreateQtGridGeneratorComponentStrategy;
typedef std::shared_ptr<CreateQtGridGeneratorComponentStrategy> CreateQtGridGeneratorComponentStrategyPtr;

class CreateQtGridGeneratorComponentStrategy : public CNCreateComponentStrategy {
public:
    static CreateQtGridGeneratorComponentStrategyPtr getNewInstance(std::shared_ptr<GridGenerator> gridGenerator);
    virtual ~CreateQtGridGeneratorComponentStrategy();
private:
    CreateQtGridGeneratorComponentStrategy(std::shared_ptr<GridGenerator> gridGenerator);

public:
    virtual std::shared_ptr<CNComponent> createComponent() override;

private:
    std::shared_ptr<GridGenerator> gridGenerator;
};

#endif //QTIRMB_CREATEQTGRIDGENERATORSTRATEGY_H
