#ifndef QTIRMB_QTIRMBPROPERTIESMODELFACTORY_H
#define QTIRMB_QTIRMBPROPERTIESMODELFACTORY_H

#include <QtViews/QWidgetBased/QtPropertiesExplorer/QtPropertiesModelFactory.h>

class QtIRMBPropertiesModelFactory;
typedef std::shared_ptr<QtIRMBPropertiesModelFactory> QtIRMBPropertiesModelFactoryPtr;

class QtIRMBPropertiesModelFactory : public QtPropertiesModelFactory {
public:
    static QtIRMBPropertiesModelFactoryPtr getNewInstance();
    virtual ~QtIRMBPropertiesModelFactory();
protected:
    QtIRMBPropertiesModelFactory();

public:
    virtual QtPropertiesModel* makeQtPropertiesModel(std::shared_ptr<CNVisitable> visitable) override;
};

#endif //QTIRMB_QTIRMBPROPERTIESMODELFACTORY_H