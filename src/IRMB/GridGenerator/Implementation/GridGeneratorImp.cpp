#include "GridGeneratorImp.h"
#include "IRMB/GridGenerator/GridGeneratorVisitor.h"
#include <Hierarchies/CNAcceptor/CNAcceptorImp.h>
#include "GridGenerator/grid/kernel/GridKernelCPU.h"
#include "GridGenerator/utilities/Transformator.h"
#include "GridGenerator/utilities/io/STLReaderWriter.h"
#include "GridGenerator/stl/Triangle.h"
#include "IRMB/STLFile/STLFile.h"
#include <iostream>

GridGeneratorImpPtr GridGeneratorImp::getNewInstance(std::string name, double length, double width, double height, double delta, std::string distribution) {
    return GridGeneratorImpPtr(new GridGeneratorImp(name, length, width, height, delta, distribution));
}
GridGeneratorImp::~GridGeneratorImp() {}
GridGeneratorImp::GridGeneratorImp(std::string name, double length, double width, double height, double delta, std::string distribution)
        : acceptor(CNAcceptorImp<GridGeneratorVisitor, GridGenerator>::getNewInstance()),
          name(name), length(length), width(width), height(height), delta(delta), distribution(distribution) {}

std::string GridGeneratorImp::getName() {
    return name;
}

void GridGeneratorImp::addSTLFile(std::shared_ptr<STLFile> stlFile) {
    stlFiles.push_back(stlFile);
}
void GridGeneratorImp::removeSTLFile(std::shared_ptr<STLFile> stlFile) {
    std::vector< std::shared_ptr<STLFile> >::iterator it = std::find(stlFiles.begin(), stlFiles.end(), stlFile);
    if(it != stlFiles.end()) stlFiles.erase(it);
}

void GridGeneratorImp::accept(CNVisitorPtr visitor) {
    acceptor->accept(visitor, me());
}

double GridGeneratorImp::getLength() { return length; }
double GridGeneratorImp::getWidth() { return width; }
double GridGeneratorImp::getHeight() { return height; }
double GridGeneratorImp::getDelta() { return delta; }
std::string GridGeneratorImp::getDistribution() { return distribution; }
Grid* GridGeneratorImp::generateGrid() {

    BoundingBox b(0, 0, 0, 0, 0, 0);

    if(stlFiles.size() > 0) {
        BoundingBox localB = stlFiles[0]->getBoundingBox();
        b.minX = localB.minX;
        b.minY = localB.minY;
        b.minZ = localB.minZ;

        b.maxX = localB.maxX;
        b.maxY = localB.maxY;
        b.maxZ = localB.maxZ;
    }

    for(int i = 1; i < stlFiles.size(); i++) {
        BoundingBox localB = stlFiles[i]->getBoundingBox();
        b.minX = std::min(b.minX,localB.minX);
        b.minY = std::min(b.minY, localB.minY);
        b.minZ = std::min(b.minZ, localB.minZ);

        b.maxX = std::max(b.maxX,localB.maxX);
        b.maxY = std::max(b.maxY, localB.maxY);
        b.maxZ = std::max(b.maxZ, localB.maxZ);
    }

    int margin = 5;
    b = BoundingBox(b.minX - margin, b.maxX + margin, b.minY - margin, b.maxY + margin, b.minZ - margin, b.maxZ + margin);

    length = b.maxX - b.minX;
    width = b.maxY - b.minY;
    height = b.maxZ - b.minZ;

    Transformator trans;
    gridKernel = std::make_shared<GridKernelCPU>(b, trans, distribution, false);

    for(int i = 0; i < stlFiles.size(); i++)
        gridKernel->meshGrid(stlFiles[i]->getTriangles().data(), stlFiles[i]->getNumberOfTriangles());

    return &gridKernel->grid;
}

GridGeneratorImpPtr GridGeneratorImp::me() {
    return this->shared_from_this();
}
