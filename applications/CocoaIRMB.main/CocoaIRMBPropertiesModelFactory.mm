#include "CocoaIRMBPropertiesModelFactory.h"
#include "CocoaViews/NSViewBased/CocoaPropertiesExplorer/CocoaPropertiesItem.h"
#include "CocoaViews/NSViewBased/CocoaPropertiesExplorer/CocoaPropertiesModel.h"
#include <CrossNative/CNVisitor/CNVisitor.h>
#include <IRMB/STLFile/STLFileVisitor.h>
#include <IRMB/STLFile/STLFile.h>
#include <IRMB/GridGenerator/GridGenerator.h>
#include <IRMB/GridGenerator/GridGeneratorVisitor.h>

class CocoaPropertiesModelCreator;
typedef std::shared_ptr<CocoaPropertiesModelCreator> CocoaPropertiesModelCreatorPtr;
class CocoaPropertiesModelCreator
        : public CNVisitor,
          public STLFileVisitor,
          public GridGeneratorVisitor {
public:
    static CocoaPropertiesModelCreatorPtr getNewInstance() {
        return CocoaPropertiesModelCreatorPtr(new CocoaPropertiesModelCreator());
    }
    virtual ~CocoaPropertiesModelCreator() {}
private:
    CocoaPropertiesModelCreator() {
        propertiesModel = [[CocoaPropertiesModel alloc] initWithTableView:nil];
    }

public:
    void visit(STLFilePtr stlFile) override {
        [propertiesModel addItem:[[CocoaPropertiesItem alloc] initWithProperty:"Name" value:stlFile->getName()]];
        [propertiesModel addItem:[[CocoaPropertiesItem alloc] initWithProperty:"Path" value:stlFile->getPath()]];
        [propertiesModel addItem:[[CocoaPropertiesItem alloc] initWithProperty:"Number Of Triangles" value:std::to_string(stlFile->getNumberOfTriangles())]];
        [propertiesModel addItem:[[CocoaPropertiesItem alloc] initWithProperty:"x Dimensions" value:"[" + std::to_string(stlFile->getBoundingBox().minX) + ", " + std::to_string(stlFile->getBoundingBox().maxX) + "]"]];
        [propertiesModel addItem:[[CocoaPropertiesItem alloc] initWithProperty:"y Dimensions" value:"[" + std::to_string(stlFile->getBoundingBox().minY) + ", " + std::to_string(stlFile->getBoundingBox().maxY) + "]"]];
        [propertiesModel addItem:[[CocoaPropertiesItem alloc] initWithProperty:"z Dimensions" value:"[" + std::to_string(stlFile->getBoundingBox().minZ) + ", " + std::to_string(stlFile->getBoundingBox().maxZ) + "]"]];
    }
    void visit(GridGeneratorPtr gridGenerator) override {
        [propertiesModel addItem:[[CocoaPropertiesItem alloc] initWithProperty:"Name" value:gridGenerator->getName()]];
        [propertiesModel addItem:[[CocoaPropertiesItem alloc] initWithProperty:"Length" value:std::to_string(gridGenerator->getLength())]];
        [propertiesModel addItem:[[CocoaPropertiesItem alloc] initWithProperty:"Width" value:std::to_string(gridGenerator->getWidth())]];
        [propertiesModel addItem:[[CocoaPropertiesItem alloc] initWithProperty:"Height" value:std::to_string(gridGenerator->getHeight())]];
        [propertiesModel addItem:[[CocoaPropertiesItem alloc] initWithProperty:"Delta" value:std::to_string(gridGenerator->getDelta())]];
        [propertiesModel addItem:[[CocoaPropertiesItem alloc] initWithProperty:"Distribution" value:gridGenerator->getDistribution()]];
    }

    virtual CocoaPropertiesModel* getPropertiesModel() {
        return propertiesModel;
    }
private:
    CocoaPropertiesModel* propertiesModel;
};


CocoaIRMBPropertiesModelFactoryPtr CocoaIRMBPropertiesModelFactory::getNewInstance() {
    return CocoaIRMBPropertiesModelFactoryPtr(new CocoaIRMBPropertiesModelFactory());
}

CocoaIRMBPropertiesModelFactory::~CocoaIRMBPropertiesModelFactory() {}
CocoaIRMBPropertiesModelFactory::CocoaIRMBPropertiesModelFactory() {}

CocoaPropertiesModel* CocoaIRMBPropertiesModelFactory::makeCocoaPropertiesModel(CNVisitablePtr visitable) {
    CocoaPropertiesModelCreatorPtr modelCreator = CocoaPropertiesModelCreator::getNewInstance();

    try{
        visitable->accept(modelCreator);
    } catch(CNVisitableVisitorMismatchException& e) {
        throw UnknownTypeException();
    }

    return modelCreator->getPropertiesModel();
}