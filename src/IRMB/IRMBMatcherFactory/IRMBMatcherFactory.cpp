#include "IRMBMatcherFactory.h"
#include <CrossNative/CNMatcherFactory/CNMatcherFactory.h>
#include <CrossNative/CNMatcher/CNMatcher.h>

#include <IRMB/STLFile/Visitors/STLFileTypeIdentifyingVisitor.h>
#include <IRMB/GridGenerator/Visitors/GridGeneratorTypeIdentifyingVisitor.h>

IRMBMatcherFactoryPtr IRMBMatcherFactory::getNewInstance() {
    return IRMBMatcherFactoryPtr(new IRMBMatcherFactory());
}
IRMBMatcherFactory::~IRMBMatcherFactory() {}
IRMBMatcherFactory::IRMBMatcherFactory() : matcherFactory(CNMatcherFactory::getNewInstance()){}

CNMatcherPtr IRMBMatcherFactory::makeGridGeneratorParentTypeMatcher() {
    return makeCNNullMatcher();
}

CNMatcherPtr IRMBMatcherFactory::makeGridGeneratorChildTypeMatcher() {
    return makeCNVisitingMatcher(makeSTLFileIdentifyingVisitor());
}

CNMatcherPtr IRMBMatcherFactory::makeSTLFileParentTypeMatcher() {
    return makeCNVisitingMatcher(makeGridGeneratorIdentifyingVisitor());
}

CNMatcherPtr IRMBMatcherFactory::makeSTLFileChildTypeMatcher() {
    return makeCNNullMatcher();
}

CNIdentifyingVisitorPtr IRMBMatcherFactory::makeSTLFileIdentifyingVisitor() {
    return STLFileTypeIdentifyingVisitor::getNewInstance();
}

CNIdentifyingVisitorPtr IRMBMatcherFactory::makeGridGeneratorIdentifyingVisitor() {
    return GridGeneratorTypeIdentifyingVisitor::getNewInstance();
}

CNMatcherPtr IRMBMatcherFactory::makeCNNullMatcher() {
    return matcherFactory->makeCNNullMatcher();
}

CNMatcherPtr IRMBMatcherFactory::makeCNMultiMatcher(std::vector<CNMatcherPtr> matchers) {
    return matcherFactory->makeCNMultiMatcher(matchers);
}

CNMatcherPtr IRMBMatcherFactory::makeCNVisitingMatcher(CNIdentifyingVisitorPtr identifier) {
    return matcherFactory->makeCNVisitingMatcher(identifier);
}
