#ifndef QTIRMB_QTGRIDGENERATOR_H
#define QTIRMB_QTGRIDGENERATOR_H

#include <QtViews/QWidgetBased/QtCentral/QtCentral.h>

class CNAcceptor;

class GridGenerator;
class QVTKWidget;

class QtGridGenerator;
typedef std::shared_ptr<QtGridGenerator> QtGridGeneratorPtr;

class QtGridGenerator : public QtCentral, public std::enable_shared_from_this<QtGridGenerator> {
public:
    static QtGridGeneratorPtr getNewInstance(std::shared_ptr<GridGenerator> gridGenerator);
    virtual ~QtGridGenerator();

protected:
    QtGridGenerator(std::shared_ptr<GridGenerator> gridGenerator);

public:
    QWidget *getQWidget() override;
    std::string getTitle() override;

    virtual void accept(CNVisitorPtr visitor) override;
private:
    virtual QtGridGeneratorPtr me();

private:
    std::shared_ptr<CNAcceptor> acceptor;

    QVTKWidget* widget;
    std::shared_ptr<GridGenerator> gridGenerator;
};

#endif //QTIRMB_QTGRIDGENERATOR_H