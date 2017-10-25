#ifndef COCOAIRMB_COCOAIRMBMENUENTRYLISTPROVIDER_H
#define COCOAIRMB_COCOAIRMBMENUENTRYLISTPROVIDER_H

#include <CrossViews/DynamicMenuPresenter/MenuEntryListProvider.h>

class SelectionModel;
class HierarchicModelAccess;
class CNComponentLoader;
class CNMatcher;

class CocoaIRMBMenuEntryListProvider;
typedef std::shared_ptr<CocoaIRMBMenuEntryListProvider> CocoaIRMBMenuEntryListProviderPtr;

class CocoaIRMBMenuEntryListProvider : public MenuEntryListProvider {
public:
    static CocoaIRMBMenuEntryListProviderPtr getNewInstance(std::shared_ptr<CNComponentLoader> componentLoader,
                                                         std::shared_ptr<CNMatcher> matcher,
                                                         std::shared_ptr<SelectionModel> selectionModel,
                                                         std::shared_ptr<HierarchicModelAccess> modelAccess);
    virtual ~CocoaIRMBMenuEntryListProvider();
protected:
    CocoaIRMBMenuEntryListProvider(std::shared_ptr<CNComponentLoader> componentLoader,
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

#endif //COCOAIRMB_COCOAIRMBMENUENTRYLISTPROVIDER_H