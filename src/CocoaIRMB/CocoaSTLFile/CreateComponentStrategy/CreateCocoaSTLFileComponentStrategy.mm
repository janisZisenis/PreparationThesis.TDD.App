#include "CreateCocoaSTLFileComponentStrategy.h"
#include <CrossNative/CNComponent/CNComposable/CNComposable.h>
#include <CrossNative/CNComposer/CNNullComposer.h>
#include "CocoaIRMB/CocoaSTLFile/CocoaSTLFile.h"

CreateCocoaSTLFileComponentStrategyPtr CreateCocoaSTLFileComponentStrategy::getNewInstance(std::shared_ptr<STLFile> stlFile) {
    return CreateCocoaSTLFileComponentStrategyPtr(new CreateCocoaSTLFileComponentStrategy(stlFile));
}
CreateCocoaSTLFileComponentStrategy::~CreateCocoaSTLFileComponentStrategy() {}
CreateCocoaSTLFileComponentStrategy::CreateCocoaSTLFileComponentStrategy(std::shared_ptr<STLFile> stlFile)
        : stlFile(stlFile) {}

CNComponentPtr CreateCocoaSTLFileComponentStrategy::createComponent() {
    CocoaSTLFilePtr CocoaSTLFile = CocoaSTLFile::getNewInstance(stlFile);
    CNComposerPtr composer = CNNullComposer::getNewInstance();
    return CNComposable::getNewInstance(CocoaSTLFile, composer);
}
