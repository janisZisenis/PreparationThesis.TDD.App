#ifndef IRMB_CREATESTLFILECOMPONENTSTRATEGY_H
#define IRMB_CREATESTLFILECOMPONENTSTRATEGY_H

#include <CrossViews/TransActions/CNLoadAction/CNCreateComponentStrategy.h>

class FileFinder;
class STLFileComponent;
class CNComposer;

class CreateSTLFileComponentStrategy;
typedef std::shared_ptr<CreateSTLFileComponentStrategy> CreateSTLFileComponentStrategyPtr;

class CreateSTLFileComponentStrategy : public CNCreateComponentStrategy {
public:
    static CreateSTLFileComponentStrategyPtr getNewInstance(std::shared_ptr<FileFinder> fileFinder);
    virtual ~CreateSTLFileComponentStrategy();
private:
    CreateSTLFileComponentStrategy(std::shared_ptr<FileFinder> fileFinder);

public:
    virtual std::shared_ptr<CNComponent> createComponent() override;

private:
    std::shared_ptr<FileFinder> fileFinder;
};

#endif //IRMB_CREATESTLFILECOMPONENTSTRATEGY_H
