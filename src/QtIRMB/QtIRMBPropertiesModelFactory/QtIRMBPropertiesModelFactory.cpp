#include "QtIRMBPropertiesModelFactory.h"
#include <QtViews/QWidgetBased/QtPropertiesExplorer/QtPropertiesItem.h>
#include <QtViews/QWidgetBased/QtPropertiesExplorer/QtPropertiesModel.h>
#include <CrossNative/CNVisitor/CNVisitor.h>
#include <IRMB/STLFile/STLFileVisitor.h>
#include <IRMB/STLFile/STLFile.h>
#include <IRMB/GridGenerator/GridGenerator.h>
#include <IRMB/GridGenerator/GridGeneratorVisitor.h>

class QtPropertiesModelCreator;
typedef std::shared_ptr<QtPropertiesModelCreator> QtPropertiesModelCreatorPtr;
class QtPropertiesModelCreator
        : public CNVisitor,
          public STLFileVisitor,
          public GridGeneratorVisitor {
public:
    static QtPropertiesModelCreatorPtr getNewInstance() {
        return QtPropertiesModelCreatorPtr(new QtPropertiesModelCreator());
    }
    virtual ~QtPropertiesModelCreator() {}
private:
    QtPropertiesModelCreator() : propertiesModel(new QtPropertiesModel()) {}

public:
    void visit(STLFilePtr stlFile) override {
        propertiesModel->addItem(QtPropertiesItem::getNewInstance("Name", stlFile->getName()));
        propertiesModel->addItem(QtPropertiesItem::getNewInstance("Path", stlFile->getPath()));
    }
    void visit(GridGeneratorPtr gridGenerator) override {
        propertiesModel->addItem(QtPropertiesItem::getNewInstance("Name", gridGenerator->getName()));
        propertiesModel->addItem(QtPropertiesItem::getNewInstance("Length", std::to_string(gridGenerator->getLength())));
        propertiesModel->addItem(QtPropertiesItem::getNewInstance("Width", std::to_string(gridGenerator->getWidth())));
        propertiesModel->addItem(QtPropertiesItem::getNewInstance("Height", std::to_string(gridGenerator->getHeight())));
        propertiesModel->addItem(QtPropertiesItem::getNewInstance("Delta", std::to_string(gridGenerator->getDelta())));
        propertiesModel->addItem(QtPropertiesItem::getNewInstance("Distribution", gridGenerator->getDistribution()));
    }

    virtual QtPropertiesModel* getPropertiesModel() {
        return propertiesModel;
    }
private:
    QtPropertiesModel* propertiesModel;
};


QtIRMBPropertiesModelFactoryPtr QtIRMBPropertiesModelFactory::getNewInstance() {
    return QtIRMBPropertiesModelFactoryPtr(new QtIRMBPropertiesModelFactory());
}

QtIRMBPropertiesModelFactory::~QtIRMBPropertiesModelFactory() {}
QtIRMBPropertiesModelFactory::QtIRMBPropertiesModelFactory() {}

QtPropertiesModel* QtIRMBPropertiesModelFactory::makeQtPropertiesModel(CNVisitablePtr visitable) {
    QtPropertiesModelCreatorPtr modelCreator = QtPropertiesModelCreator::getNewInstance();

    try{
        visitable->accept(modelCreator);
    } catch(CNVisitableVisitorMismatchException& e) {
        throw UnknownTypeException();
    }

    return modelCreator->getPropertiesModel();
}