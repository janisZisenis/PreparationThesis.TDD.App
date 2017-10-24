#ifndef COCOAIRMB_COCOAIRMBPROPERTIESMODELFACTORY_H
#define COCOAIRMB_COCOAIRMBPROPERTIESMODELFACTORY_H

#include <CocoaViews/NSViewBased/CocoaPropertiesExplorer/CocoaPropertiesModelFactory.h>

class CocoaIRMBPropertiesModelFactory;
typedef std::shared_ptr<CocoaIRMBPropertiesModelFactory> CocoaIRMBPropertiesModelFactoryPtr;

class CocoaIRMBPropertiesModelFactory : public CocoaPropertiesModelFactory {
public:
    static CocoaIRMBPropertiesModelFactoryPtr getNewInstance();
    virtual ~CocoaIRMBPropertiesModelFactory();
protected:
    CocoaIRMBPropertiesModelFactory();

public:
    virtual CocoaPropertiesModel* makeCocoaPropertiesModel(std::shared_ptr<CNVisitable> visitable) override;
};

#endif //COCOAIRMB_COCOAIRMBPROPERTIESMODELFACTORY_H