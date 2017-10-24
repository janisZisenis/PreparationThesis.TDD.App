#include "CocoaGridGenerator.h"
#include <CrossNative/CNAcceptor/CNAcceptorImp.h>
#include <CocoaViews/NSViewBased/CocoaCentral/CocoaCentralVisitor.h>
#include <IRMB/GridGenerator/GridGenerator.h>
#import <Cocoa/Cocoa.h>
#import "NSVTKView.h"

#include "GridGenerator/grid/kernel/Grid.h"

#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPointData.h>
#include <vtkVertex.h>
#include <vtkUnstructuredGrid.h>
#include <vtkDoubleArray.h>
#include <vtkProperty.h>

CocoaGridGeneratorPtr CocoaGridGenerator::getNewInstance(GridGeneratorPtr gridGenerator) {
    return CocoaGridGeneratorPtr(new CocoaGridGenerator(gridGenerator));
}

CocoaGridGenerator::~CocoaGridGenerator() {}

CocoaGridGenerator::CocoaGridGenerator(GridGeneratorPtr gridGenerator)
        : acceptor(CNAcceptorImp<CocoaCentralVisitor, CocoaGridGenerator>::getNewInstance()),
          gridGenerator(gridGenerator),
          title(gridGenerator->getName()){
    this->view = [[NSVTKView alloc] init];
    [view initializeVTKSupport];

    Grid* grid = gridGenerator->generateGrid();

    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkVertex> vertex = vtkSmartPointer<vtkVertex>::New();

    vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    vtkSmartPointer<vtkDoubleArray> types = vtkSmartPointer<vtkDoubleArray>::New();

    int x, y, z;

    for(int i = 0; i < grid->size; i++) {
        grid->transIndexToCoords(i, x, y, z);
        points->InsertNextPoint(x, y, z);
        unstructuredGrid->SetPoints(points);
        vertex->GetPointIds()->SetId(0, i);
        unstructuredGrid->InsertNextCell(vertex->GetCellType(), vertex->GetPointIds());
        types->InsertNextValue((int)grid->field[i]);
    }
    unstructuredGrid->GetPointData()->SetScalars(types);

    vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputData(unstructuredGrid);

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetPointSize(3);

    [view getRenderer]->AddActor(actor);
    [view getRenderer]->SetBackground(222./255, 222./255, 222./255);

    [view setNeedsDisplay:YES];
}

void CocoaGridGenerator::accept(CNVisitorPtr visitor) {
    acceptor->accept(visitor, me());
}

CocoaGridGeneratorPtr CocoaGridGenerator::me() {
    return this->shared_from_this();
}

NSView *CocoaGridGenerator::getNSView() {
    return view;
}

std::string CocoaGridGenerator::getTitle() {
    return title;
}

