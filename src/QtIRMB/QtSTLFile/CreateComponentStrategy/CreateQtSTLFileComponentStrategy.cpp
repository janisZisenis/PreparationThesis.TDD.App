#include "CreateQtSTLFileComponentStrategy.h"
#include <CrossNative/CNComponent/CNComposable/CNComposable.h>
#include <CrossNative/CNComposer/CNNullComposer.h>
#include "QtIRMB/QtSTLFile/QtSTLFile.h"

CreateQtSTLFileComponentStrategyPtr CreateQtSTLFileComponentStrategy::getNewInstance(std::shared_ptr<STLFile> stlFile) {
    return CreateQtSTLFileComponentStrategyPtr(new CreateQtSTLFileComponentStrategy(stlFile));
}
CreateQtSTLFileComponentStrategy::~CreateQtSTLFileComponentStrategy() {}
CreateQtSTLFileComponentStrategy::CreateQtSTLFileComponentStrategy(std::shared_ptr<STLFile> stlFile)
        : stlFile(stlFile) {}

CNComponentPtr CreateQtSTLFileComponentStrategy::createComponent() {
    QtSTLFilePtr qtSTLFile = QtSTLFile::getNewInstance(stlFile);
    CNComposerPtr composer = CNNullComposer::getNewInstance();
    return CNComposable::getNewInstance(qtSTLFile, composer);
}
