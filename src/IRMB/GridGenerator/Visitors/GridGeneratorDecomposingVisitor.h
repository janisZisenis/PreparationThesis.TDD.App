#ifndef IRMB_GRIDGENERATORDECOMPOSINGVISITOR_H
#define IRMB_GRIDGENERATORDECOMPOSINGVISITOR_H

#include <CrossNative/CNVisitor/CNVisitor.h>
#include "IRMB/STLFile/STLFileVisitor.h"

class GridGenerator;

class GridGeneratorDecomposingVisitor;
typedef std::shared_ptr<GridGeneratorDecomposingVisitor> GridGeneratorDecomposingVisitorPtr;

class GridGeneratorDecomposingVisitor
        : public CNVisitor,
          public STLFileVisitor {
public:
    static GridGeneratorDecomposingVisitorPtr getNewInstance(std::shared_ptr<GridGenerator> gridGenerator);
    virtual ~GridGeneratorDecomposingVisitor();
private:
    GridGeneratorDecomposingVisitor(std::shared_ptr<GridGenerator> gridGenerator);

public:
    virtual void visit(std::shared_ptr<STLFile> stlFile) override;
private:
    std::shared_ptr<GridGenerator> gridGenerator;
};

#endif //IRMB_GRIDGENERATORDECOMPOSINGVISITOR_H
