#ifndef IRMB_GRIDGENERATORTYPEIDENTIFYINGVISITOR_H
#define IRMB_GRIDGENERATORTYPEIDENTIFYINGVISITOR_H

#include <CrossNative/CNMatcher/CNVisitingMatcher/CNIdentifyingVisitor.h>
#include "IRMB/GridGenerator/GridGeneratorVisitor.h"

class GridGeneratorTypeIdentifyingVisitor;
typedef std::shared_ptr<GridGeneratorTypeIdentifyingVisitor> GridGeneratorTypeIdentifyingVisitorPtr;

class GridGeneratorTypeIdentifyingVisitor : public CNIdentifyingVisitor, public GridGeneratorVisitor {
public:
    static GridGeneratorTypeIdentifyingVisitorPtr getNewInstance() {
        return GridGeneratorTypeIdentifyingVisitorPtr(new GridGeneratorTypeIdentifyingVisitor());
    }
    virtual ~GridGeneratorTypeIdentifyingVisitor() {}
private:
    GridGeneratorTypeIdentifyingVisitor() {}

public:
    virtual void visit(std::shared_ptr<GridGenerator> gridGenerator) override {}
    bool hasIdentified() override {
        return true;
    }
};

#endif //IRMB_GRIDGENERATORTYPEIDENTIFYINGVISITOR_H