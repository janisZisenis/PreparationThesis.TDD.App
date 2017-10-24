#ifndef IRMB_STLFILETYPEIDENTIFYINGVISITOR_H
#define IRMB_STLFILETYPEIDENTIFYINGVISITOR_H

#include <CrossNative/CNMatcher/CNVisitingMatcher/CNIdentifyingVisitor.h>
#include "IRMB/STLFile/STLFileVisitor.h"

class STLFileTypeIdentifyingVisitor;
typedef std::shared_ptr<STLFileTypeIdentifyingVisitor> STLFileTypeIdentifyingVisitorPtr;

class STLFileTypeIdentifyingVisitor : public CNIdentifyingVisitor, public STLFileVisitor {
public:
    static STLFileTypeIdentifyingVisitorPtr getNewInstance() {
        return STLFileTypeIdentifyingVisitorPtr(new STLFileTypeIdentifyingVisitor());
    }
    virtual ~STLFileTypeIdentifyingVisitor() {}
private:
    STLFileTypeIdentifyingVisitor() {}

public:
    virtual void visit(std::shared_ptr<STLFile> stlFile) override {}
    bool hasIdentified() override {
        return true;
    }
};

#endif //IRMB_STLFILETYPEIDENTIFYINGVISITOR_H