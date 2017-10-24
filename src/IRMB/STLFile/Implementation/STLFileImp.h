#ifndef IRMB_STLFILEIMP_H
#define IRMB_STLFILEIMP_H

#include "IRMB/STLFile/STLFile.h"
#include <string>

class CNAcceptor;

class STLFileImp;
typedef std::shared_ptr<STLFileImp> STLFileImpPtr;

class STLFileImp : public STLFile, public std::enable_shared_from_this<STLFileImp> {
public:
    static STLFileImpPtr getNewInstance(std::string path);
    virtual ~STLFileImp();
private:
    STLFileImp(std::string path);

public:
    virtual std::string getName() override;
    virtual std::string getPath() override;

    virtual void accept(CNVisitorPtr visitor) override;

    virtual std::vector<Triangle> getTriangles() override;
    virtual int getNumberOfTriangles() override;
    virtual BoundingBox getBoundingBox() override;

private:
    STLFileImpPtr me();

private:
    std::shared_ptr<CNAcceptor> acceptor;

    std::string name;
    std::string path;

    std::vector<Triangle> triangles;
    BoundingBox boundingBox;
};

#endif //IRMB_STLFILEIMP_H
