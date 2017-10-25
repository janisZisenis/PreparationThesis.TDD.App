#ifndef QTIRMB_QTIRMBMENUENTRYLISTPROVIDER_H
#define QTIRMB_QTIRMBMENUENTRYLISTPROVIDER_H

#include <CrossViews/DynamicMenuPresenter/MenuEntryListProvider.h>

class SelectionModel;
class HierarchicModelAccess;
class CNComponentLoader;
class CNMatcher;

class QtIRMBMenuEntryListProvider;
typedef std::shared_ptr<QtIRMBMenuEntryListProvider> QtIRMBMenuEntryListProviderPtr;

class QtIRMBMenuEntryListProvider : public MenuEntryListProvider {
public:
    static QtIRMBMenuEntryListProviderPtr getNewInstance(std::shared_ptr<CNComponentLoader> componentLoader,
                                                         std::shared_ptr<CNMatcher> matcher,
                                                         std::shared_ptr<SelectionModel> selectionModel,
                                                         std::shared_ptr<HierarchicModelAccess> modelAccess);
    virtual ~QtIRMBMenuEntryListProvider();
protected:
    QtIRMBMenuEntryListProvider(std::shared_ptr<CNComponentLoader> componentLoader,
                                std::shared_ptr<CNMatcher> matcher,
                                std::shared_ptr<SelectionModel> selectionModel,
                                std::shared_ptr<HierarchicModelAccess> modelAccess);

public:
    const std::vector<std::shared_ptr<CNVisitable>> getMenuEntryList() override;

private:
    std::shared_ptr<CNMatcher> matcher;
    std::shared_ptr<CNComponentLoader> componentLoader;
    std::shared_ptr<SelectionModel> selectionModel;
    std::shared_ptr<HierarchicModelAccess> modelAccess;
};

#endif //QTIRMB_QTIRMBMENUENTRYLISTPROVIDER_H