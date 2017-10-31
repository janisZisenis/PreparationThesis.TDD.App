#ifndef QTIRMB_CREATEQTSTLFILESTRATEGY_H
#define QTIRMB_CREATEQTSTLFILESTRATEGY_H

#include <CrossViews/TransActions/CNLoadAction/CNCreateComponentStrategy.h>

class STLFile;
class CNComposer;

class CreateQtSTLFileComponentStrategy;
typedef std::shared_ptr<CreateQtSTLFileComponentStrategy> CreateQtSTLFileComponentStrategyPtr;

class CreateQtSTLFileComponentStrategy : public CNCreateComponentStrategy {
public:
    static CreateQtSTLFileComponentStrategyPtr getNewInstance(std::shared_ptr<STLFile> stlFile);
    virtual ~CreateQtSTLFileComponentStrategy();
private:
    CreateQtSTLFileComponentStrategy(std::shared_ptr<STLFile> stlFile);

public:
    virtual std::shared_ptr<CNComponent> createComponent() override;

private:
    std::shared_ptr<STLFile> stlFile;
};

#endif //QTIRMB_CREATEQTSTLFILESTRATEGY_H
