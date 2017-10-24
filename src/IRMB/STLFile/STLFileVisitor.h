#ifndef IRMB_STLFILEVISITOR_H
#define IRMB_STLFILEVISITOR_H

#include <memory>

class STLFile;

class STLFileVisitor;
typedef std::shared_ptr<STLFileVisitor> STLFileVisitorPtr;

class STLFileVisitor {
public:
    virtual void visit(std::shared_ptr<STLFile> stlFile) = 0;
};

#endif //IRMB_STLFILEVISITOR_H