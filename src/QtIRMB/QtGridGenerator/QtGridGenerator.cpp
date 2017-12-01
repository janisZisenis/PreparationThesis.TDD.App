#include "QtGridGenerator.h"
#include <Hierarchies/CNAcceptor/CNAcceptorImp.h>
#include <Hierarchies/CNVisitor/CNVisitor.h>
#include <QtViews/QWidgetBased/QtCentral/QtCentralVisitor.h>
#include <QPushButton>

#include <IRMB/GridGenerator/GridGenerator.h>
#include <QWidget>
#include "QVTKWidget.h"
#include <GridGenerator/grid/kernel/Grid.h>

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
#include <vtkPolyData.h>
#include <vtkThresholdPoints.h>
#include <QHBoxLayout>
#include <QVBoxLayout>

QtGridGeneratorPtr QtGridGenerator::getNewInstance(GridGeneratorPtr gridGenerator) {
    return QtGridGeneratorPtr(new QtGridGenerator(gridGenerator));
}

QtGridGenerator::~QtGridGenerator() {
    delete widget;
}

QtGridGenerator::QtGridGenerator(GridGeneratorPtr gridGenerator)
        : acceptor(CNAcceptorImp<QtCentralVisitor, QtCentral>::getNewInstance()),
          view(new QWidget()),
          solidButton(new QPushButton("Show Solid Nodes")),
          fluidButton(new QPushButton("Show Fluid Nodes")),
          widget(new QVTKWidget()),
          gridGenerator(gridGenerator) {
    initialize();
    update();
}

void QtGridGenerator::initialize() {
    initializeView();
    connectToView();
}

QWidget *QtGridGenerator::getQWidget() {
    return view;
}

std::string QtGridGenerator::getTitle() {
    return view->windowTitle().toStdString();
}

void QtGridGenerator::accept(CNVisitorPtr visitor) {
    acceptor->accept(visitor, me());
}

void QtGridGenerator::update() {
    grid = gridGenerator->generateGrid();
    visualize();
}

void QtGridGenerator::visualize() {
    thresholdGrid();
    visualizeGrid();

    widget->repaint();
}

void QtGridGenerator::visualizeGrid() {
    vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputData(thresholdedGrid);

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetPointSize(3);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->SetBackground(222./255, 222./255, 222./255);

    widget->GetRenderWindow()->AddRenderer(renderer);
}

void QtGridGenerator::thresholdGrid() {
    vtkSmartPointer<vtkPoints> thresholdedPoints = getThresholdedPoints();

    thresholdedGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    vtkSmartPointer<vtkDoubleArray> types = vtkSmartPointer<vtkDoubleArray>::New();

    for(int i = 0; i < thresholdedPoints->GetNumberOfPoints(); i++) {
        thresholdedGrid->SetPoints(thresholdedPoints);
        vtkSmartPointer<vtkVertex> vertex = vtkSmartPointer<vtkVertex>::New();
        vertex->GetPointIds()->SetId(0, i);
        thresholdedGrid->InsertNextCell(vertex->GetCellType(), vertex->GetPointIds());

        types->InsertNextValue((int)grid->field[i]);
    }
}

vtkSmartPointer<vtkPoints> QtGridGenerator::getThresholdedPoints() {
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkIntArray> type = vtkSmartPointer<vtkIntArray>::New();
    type->SetNumberOfComponents(1);
    type->SetName("type");

    int x, y, z;
    for(int i = 0; i < grid->size; i++) {
        grid->transIndexToCoords(i, x, y, z);
        points->InsertNextPoint(x, y, z);
        type->InsertNextValue(grid->field[i]);
    }

    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
    polydata->SetPoints(points);
    polydata->GetPointData()->AddArray(type);

    vtkSmartPointer<vtkThresholdPoints> threshold = vtkSmartPointer<vtkThresholdPoints>::New();
    threshold->SetInputData(polydata);

    int upper = getUpperThresholdBoundary();
    int lower = getLowerThresholdBoundary();

    threshold->ThresholdBetween(getLowerThresholdBoundary(), getUpperThresholdBoundary());
    threshold->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, "type");
    threshold->Update();

    vtkPolyData* thresholdedPolydata = threshold->GetOutput();
    return thresholdedPolydata->GetPoints();
}

QtGridGeneratorPtr QtGridGenerator::me() {
    return this->shared_from_this();
}

void QtGridGenerator::initializeView() {
    view->setWindowTitle(QString::fromStdString(gridGenerator->getName()));

    solidButton->setCheckable(true);
    solidButton->setChecked(true);
    fluidButton->setCheckable(true);
    fluidButton->setChecked(true);

    QHBoxLayout* hLayout = new QHBoxLayout();
    QVBoxLayout* vLayout = new QVBoxLayout();
    hLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setContentsMargins(0, 0, 0, 0);

    hLayout->addWidget(solidButton);
    hLayout->addWidget(fluidButton);

    vLayout->addItem(hLayout);
    vLayout->addWidget(widget);
    view->setLayout(vLayout);
}

void QtGridGenerator::connectToView() {
    connect(solidButton, SIGNAL(clicked()), this, SLOT(onSolidButtonToggled()));
    connect(fluidButton, SIGNAL(clicked()), this, SLOT(onFluidButtonToggled()));
}

void QtGridGenerator::onSolidButtonToggled() {
    showSolidNodes = solidButton->isChecked();
    visualize();
}

void QtGridGenerator::onFluidButtonToggled() {
    showFluidNodes = fluidButton->isChecked();
    visualize();
}

int QtGridGenerator::getUpperThresholdBoundary() {
    if(showSolidNodes)
        return 2;
    if(showFluidNodes)
        return 1;

    return 0;
}

int QtGridGenerator::getLowerThresholdBoundary() {
    if(showFluidNodes)
        return -1;
    if(showFluidNodes)
        return 0;

    return 1;
}

