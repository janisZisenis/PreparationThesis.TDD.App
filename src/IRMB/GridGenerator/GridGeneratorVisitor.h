#ifndef IRMB_GRIDGENERATORVISITOR_H
#define IRMB_GRIDGENERATORVISITOR_H

#include <memory>

class GridGenerator;

class GridGeneratorVisitor;
typedef std::shared_ptr<GridGeneratorVisitor> GridGeneratorVisitorPtr;

class GridGeneratorVisitor {
public:
    virtual void visit(std::shared_ptr<GridGenerator> gridGenerator) = 0;
};

#endif //IRMB_GRIDGENERATORVISITOR_H