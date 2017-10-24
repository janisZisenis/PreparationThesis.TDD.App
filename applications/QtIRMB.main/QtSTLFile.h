#ifndef QTIRMB_QTSTLFILE_H
#define QTIRMB_QTSTLFILE_H

#include <QtViews/QWidgetBased/QtCentral/QtCentral.h>

class CNAcceptor;

class QVTKWidget;
class STLFile;

class QtSTLFile;
typedef std::shared_ptr<QtSTLFile> QtSTLFilePtr;

class QtSTLFile : public QtCentral, public std::enable_shared_from_this<QtSTLFile> {
public:
    static QtSTLFilePtr getNewInstance(std::shared_ptr<STLFile> stlFile);
    virtual ~QtSTLFile();
protected:
    QtSTLFile(std::shared_ptr<STLFile> stlFile);

public:
    QWidget *getQWidget() override;
    std::string getTitle() override;

    virtual void accept(CNVisitorPtr visitor) override;
private:
    QtSTLFilePtr me();

private:
    std::shared_ptr<CNAcceptor> acceptor;

    std::shared_ptr<STLFile> stlFile;
    QVTKWidget* widget;
};

#endif //QTIRMB_QTSTLFILE_H