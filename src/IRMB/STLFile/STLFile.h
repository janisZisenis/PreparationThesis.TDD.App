#ifndef IRMB_STLFILE_H
#define IRMB_STLFILE_H

#include <CrossNative/CNVisitable/CNVisitable.h>
#include <vector>
#include "GridGenerator/stl/Triangle.h"
#include "GridGenerator/stl/BoundingBox.h"

class STLFile;
typedef std::shared_ptr<STLFile> STLFilePtr;

class STLFile : public virtual CNVisitable {
public:
    virtual ~STLFile() {};
protected:
    STLFile() {};

public:
    virtual std::string getName() = 0;
    virtual std::string getPath() = 0;
    virtual std::vector<Triangle> getTriangles() = 0;
    virtual int getNumberOfTriangles() = 0;
    virtual BoundingBox getBoundingBox() = 0;
};

#endif //IRMB_STLFILE_H