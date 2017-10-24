#ifndef IRMB_IRMBMATCHERFACTORY_H
#define IRMB_IRMBMATCHERFACTORY_H

#include <memory>
#include <vector>

class CNMatcherFactory;
class CNMatcher;
class CNMultiMatcher;

class CNIdentifyingVisitor;

class IRMBMatcherFactory;
typedef std::shared_ptr<IRMBMatcherFactory> IRMBMatcherFactoryPtr;

class IRMBMatcherFactory {
public:
    static IRMBMatcherFactoryPtr getNewInstance();
    virtual ~IRMBMatcherFactory();
protected:
    IRMBMatcherFactory();

public:
    virtual std::shared_ptr<CNMatcher> makeGridGeneratorParentTypeMatcher();
    virtual std::shared_ptr<CNMatcher> makeGridGeneratorChildTypeMatcher();

    virtual std::shared_ptr<CNMatcher> makeSTLFileParentTypeMatcher();
    virtual std::shared_ptr<CNMatcher> makeSTLFileChildTypeMatcher();

private:
    virtual std::shared_ptr<CNIdentifyingVisitor> makeSTLFileIdentifyingVisitor();
    virtual std::shared_ptr<CNIdentifyingVisitor> makeGridGeneratorIdentifyingVisitor();

    virtual std::shared_ptr<CNMatcher> makeCNNullMatcher();
    virtual std::shared_ptr<CNMatcher> makeCNVisitingMatcher(std::shared_ptr<CNIdentifyingVisitor> identifier);
    virtual std::shared_ptr<CNMatcher> makeCNMultiMatcher(std::vector< std::shared_ptr<CNMatcher> > matchers);

private:
    std::shared_ptr<CNMatcherFactory> matcherFactory;
};

#endif //IRMB_IRMBMATCHERFACTORY_H