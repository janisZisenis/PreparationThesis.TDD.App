#include "CocoaSTLFile.h"
#include <CrossNative/CNAcceptor/CNAcceptorImp.h>
#include <CocoaViews/NSViewBased/CocoaCentral/CocoaCentralVisitor.h>
#include <IRMB/STLFile/Implementation/STLFileImp.h>
#import <Cocoa/Cocoa.h>
#import "NSVTKView.h"


#include <vtkPolyData.h>
#include <vtkSTLReader.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"

CocoaSTLFilePtr CocoaSTLFile::getNewInstance(STLFilePtr stlFile) {
    return CocoaSTLFilePtr(new CocoaSTLFile(stlFile));
}

CocoaSTLFile::~CocoaSTLFile() {}

CocoaSTLFile::CocoaSTLFile(STLFilePtr stlFile)
        : acceptor(CNAcceptorImp<CocoaCentralVisitor, CocoaSTLFile>::getNewInstance()),
          stlFile(stlFile),
          title(stlFile->getName()) {
    this->view = [[NSVTKView alloc] init];
    [view initializeVTKSupport];

    vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName(stlFile->getPath().c_str());
    reader->Update();

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(reader->GetOutputPort());

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    [view getRenderer]->AddActor(actor);
    [view getRenderer]->SetBackground(222./255, 222./255, 222./255);

    [view setNeedsDisplay:YES];
}

NSView *CocoaSTLFile::getNSView() {
    return view;
}

std::string CocoaSTLFile::getTitle() {
    return title;
}

CocoaSTLFilePtr CocoaSTLFile::me() {
    return this->shared_from_this();
}

void CocoaSTLFile::accept(CNVisitorPtr visitor) {
    acceptor->accept(visitor, me());
}
