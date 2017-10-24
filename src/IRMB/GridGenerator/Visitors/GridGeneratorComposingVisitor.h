#ifndef IRMB_GRIDGENERATORCOMPOSINGVISITOR_H
#define IRMB_GRIDGENERATORCOMPOSINGVISITOR_H

#include <CrossNative/CNVisitor/CNVisitor.h>
#include "IRMB/STLFile/STLFileVisitor.h"

class GridGenerator;

class GridGeneratorComposingVisitor;
typedef std::shared_ptr<GridGeneratorComposingVisitor> GridGeneratorComposingVisitorPtr;

class GridGeneratorComposingVisitor
        : public CNVisitor,
          public STLFileVisitor {
public:
    static GridGeneratorComposingVisitorPtr getNewInstance(std::shared_ptr<GridGenerator> gridGenerator);
    virtual ~GridGeneratorComposingVisitor();
private:
    GridGeneratorComposingVisitor(std::shared_ptr<GridGenerator> gridGenerator);

public:
    virtual void visit(std::shared_ptr<STLFile> stlFile) override;
private:
    std::shared_ptr<GridGenerator> gridGenerator;
};

#endif //IRMB_GRIDGENERATORCOMPOSINGVISITOR_H
