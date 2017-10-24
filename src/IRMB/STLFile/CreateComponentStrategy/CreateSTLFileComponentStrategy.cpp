#include "CreateSTLFileComponentStrategy.h"
#include "IRMB/STLFile/Implementation/STLFileImp.h"
#include <CrossNative/CNComponent/CNComposable/CNComposable.h>
#include <CrossNative/CNComposer/CNNullComposer.h>
#include "FileFinder.h"

CreateSTLFileComponentStrategyPtr CreateSTLFileComponentStrategy::getNewInstance(FileFinderPtr fileFinder) {
    return CreateSTLFileComponentStrategyPtr(new CreateSTLFileComponentStrategy(fileFinder));
}
CreateSTLFileComponentStrategy::~CreateSTLFileComponentStrategy() {}
CreateSTLFileComponentStrategy::CreateSTLFileComponentStrategy(FileFinderPtr fileFinder) : fileFinder(fileFinder) {}

CNComponentPtr CreateSTLFileComponentStrategy::createComponent() {
    if(!fileFinder->findFile())
        throw CreationCanceledException();

    STLFilePtr stlFile = STLFileImp::getNewInstance(fileFinder->getFileName());
    CNComposerPtr composer = CNNullComposer::getNewInstance();

    return CNComposable::getNewInstance(stlFile, composer);
}
