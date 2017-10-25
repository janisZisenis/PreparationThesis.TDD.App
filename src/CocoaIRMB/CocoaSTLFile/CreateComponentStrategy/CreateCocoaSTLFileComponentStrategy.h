#ifndef COCOAIRMB_CREATECOCOASTLFILESTRATEGY_H
#define COCOAIRMB_CREATECOCOASTLFILESTRATEGY_H

#include <CrossNative/TransActions/CNLoadAction/CNCreateComponentStrategy.h>

class STLFile;
class CNComposer;

class CreateCocoaSTLFileComponentStrategy;
typedef std::shared_ptr<CreateCocoaSTLFileComponentStrategy> CreateCocoaSTLFileComponentStrategyPtr;

class CreateCocoaSTLFileComponentStrategy : public CNCreateComponentStrategy {
public:
    static CreateCocoaSTLFileComponentStrategyPtr getNewInstance(std::shared_ptr<STLFile> stlFile);
    virtual ~CreateCocoaSTLFileComponentStrategy();
private:
    CreateCocoaSTLFileComponentStrategy(std::shared_ptr<STLFile> stlFile);

public:
    virtual std::shared_ptr<CNComponent> createComponent() override;

private:
    std::shared_ptr<STLFile> stlFile;
};

#endif //COCOAIRMB_CREATECOCOASTLFILESTRATEGY_H
