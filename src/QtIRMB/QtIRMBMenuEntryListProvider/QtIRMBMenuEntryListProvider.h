#ifndef QTIRMB_QTIRMBMENUENTRYLISTPROVIDER_H
#define QTIRMB_QTIRMBMENUENTRYLISTPROVIDER_H

#include <CrossViews/CNDynamicMenuPresenter/CNComponentListProvider.h>

class CNSelectionModel;
class CNHierarchicComponentAccess;
class CNMatcher;
class CNComponentLoader;

class QtIRMBMenuEntryListProvider;
typedef std::shared_ptr<QtIRMBMenuEntryListProvider> QtIRMBMenuEntryListProviderPtr;

class QtIRMBMenuEntryListProvider : public CNComponentListProvider{
public:
    static QtIRMBMenuEntryListProviderPtr getNewInstance(std::shared_ptr<CNComponentLoader> componentLoader,
                                                         std::shared_ptr<CNMatcher> matcher,
                                                         std::shared_ptr<CNSelectionModel> selectionModel,
                                                         std::shared_ptr<CNHierarchicComponentAccess> modelAccess);
    virtual ~QtIRMBMenuEntryListProvider();
protected:
    QtIRMBMenuEntryListProvider(std::shared_ptr<CNComponentLoader> componentLoader,
                                std::shared_ptr<CNMatcher> matcher,
                                std::shared_ptr<CNSelectionModel> selectionModel,
                                std::shared_ptr<CNHierarchicComponentAccess> modelAccess);

public:
    const std::vector<std::shared_ptr<CNVisitable>> getMenuEntryList() override;

private:
    std::shared_ptr<CNMatcher> matcher;
    std::shared_ptr<CNComponentLoader> componentLoader;
    std::shared_ptr<CNSelectionModel> selectionModel;
    std::shared_ptr<CNHierarchicComponentAccess> modelAccess;
};

#endif //QTIRMB_QTIRMBMENUENTRYLISTPROVIDER_H