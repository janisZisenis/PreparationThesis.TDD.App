#include "GridGeneratorDecomposingVisitor.h"

#include "IRMB/GridGenerator/GridGenerator.h"
#include "IRMB/STLFile/STLFile.h"

GridGeneratorDecomposingVisitorPtr GridGeneratorDecomposingVisitor::getNewInstance(GridGeneratorPtr gridGenerator) {
    return GridGeneratorDecomposingVisitorPtr(new GridGeneratorDecomposingVisitor(gridGenerator));
}

GridGeneratorDecomposingVisitor::~GridGeneratorDecomposingVisitor() {}

GridGeneratorDecomposingVisitor::GridGeneratorDecomposingVisitor(GridGeneratorPtr gridGenerator) : gridGenerator(gridGenerator) {}

void GridGeneratorDecomposingVisitor::visit(STLFilePtr stlFile) {
    gridGenerator->removeSTLFile(stlFile);
}
