#ifndef COCOALVICE_COCOAFILEFINDER_H
#define COCOALVICE_COCOAFILEFINDER_H

#include "IRMB/STLFile/CreateComponentStrategy/FileFinder.h"

class CocoaFileFinder;
typedef std::shared_ptr<CocoaFileFinder> CocoaFileFinderPtr;

class CocoaFileFinder : public FileFinder {
public:
    static CocoaFileFinderPtr getNewInstance();
    virtual ~CocoaFileFinder();
private:
    CocoaFileFinder();

public:
    virtual bool findFile() override;
    virtual std::string getFileName() override;

private:
    std::string foundFile;
};

#endif //COCOALVICE_COCOAFILEFINDER_H