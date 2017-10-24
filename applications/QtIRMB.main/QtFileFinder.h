#ifndef QTIRMB_QTFILEFINDER_H
#define QTIRMB_QTFILEFINDER_H

#include "IRMB/STLFile/CreateComponentStrategy/FileFinder.h"


class QtFileFinder;
typedef std::shared_ptr<QtFileFinder> QtFileFinderPtr;

class QtFileFinder : public FileFinder {
public:
    static QtFileFinderPtr getNewInstance();
    virtual ~QtFileFinder();
private:
    QtFileFinder();

public:
    virtual bool findFile() override;
    virtual std::string getFileName() override;

private:
    std::string foundFile;
};

#endif //QTIRMB_QTFILEFINDER_H