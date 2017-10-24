#include "STLFileImp.h"
#include "IRMB/STLFile/STLFileVisitor.h"
#include <CrossNative/CNAcceptor/CNAcceptorImp.h>

#include <boost/filesystem.hpp>
#include "GridGenerator/utilities/io/STLReaderWriter.h"
#include "GridGenerator/utilities/Transformator.h"

STLFileImpPtr STLFileImp::getNewInstance(std::string path) {
    return STLFileImpPtr(new STLFileImp(path));
}

STLFileImp::~STLFileImp() {}

STLFileImp::STLFileImp(std::string path)
        : acceptor(CNAcceptorImp<STLFileVisitor, STLFile>::getNewInstance()),
          path(path) {
    static int i;

    boost::filesystem::path p(path);
    this->name = p.stem().string() + " (" + std::to_string(i++) +")";

    Transformator trans;
    triangles = STLReaderWriter::readSTL(getPath(), trans);

    for(int i = 0; i < getNumberOfTriangles(); i++) {
        Triangle t = triangles[i];
        if(t.v1.x < boundingBox.minX) boundingBox.minX = (int)t.v1.x;
        if(t.v2.x < boundingBox.minX) boundingBox.minX = (int)t.v2.x;
        if(t.v3.x < boundingBox.minX) boundingBox.minX = (int)t.v3.x;

        if(t.v1.y < boundingBox.minY) boundingBox.minY = (int)t.v1.y;
        if(t.v2.y < boundingBox.minY) boundingBox.minY = (int)t.v2.y;
        if(t.v3.y < boundingBox.minY) boundingBox.minY = (int)t.v3.y;

        if(t.v1.z < boundingBox.minZ) boundingBox.minZ = (int)t.v1.z;
        if(t.v2.z < boundingBox.minZ) boundingBox.minZ = (int)t.v2.z;
        if(t.v3.z < boundingBox.minZ) boundingBox.minZ = (int)t.v3.z;

        if(t.v1.x > boundingBox.maxX) boundingBox.maxX = (int)t.v1.x;
        if(t.v2.x > boundingBox.maxX) boundingBox.maxX = (int)t.v2.x;
        if(t.v3.x > boundingBox.maxX) boundingBox.maxX = (int)t.v3.x;

        if(t.v1.y > boundingBox.maxY) boundingBox.maxY = (int)t.v1.y;
        if(t.v2.y > boundingBox.maxY) boundingBox.maxY = (int)t.v2.y;
        if(t.v3.y > boundingBox.maxY) boundingBox.maxY = (int)t.v3.y;

        if(t.v1.z > boundingBox.maxZ) boundingBox.maxZ = (int)t.v1.z;
        if(t.v2.z > boundingBox.maxZ) boundingBox.maxZ = (int)t.v2.z;
        if(t.v3.z > boundingBox.maxZ) boundingBox.maxZ = (int)t.v3.z;
    }
}

std::string STLFileImp::getName() {
    return name;
}
std::string STLFileImp::getPath() {
    return path;
}

void STLFileImp::accept(CNVisitorPtr visitor) {
    acceptor->accept(visitor, me());
}

std::vector<Triangle> STLFileImp::getTriangles() {
    return triangles;
}

STLFileImpPtr STLFileImp::me() {
    return this->shared_from_this();
}

int STLFileImp::getNumberOfTriangles() {
    return (int) triangles.size();
}

BoundingBox STLFileImp::getBoundingBox() {
    return boundingBox;
}
