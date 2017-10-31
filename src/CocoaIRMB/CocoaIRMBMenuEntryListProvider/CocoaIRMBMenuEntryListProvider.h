#ifndef COCOAIRMB_COCOAIRMBMENUENTRYLISTPROVIDER_H
#define COCOAIRMB_COCOAIRMBMENUENTRYLISTPROVIDER_H

#include <CrossViews/CNDynamicMenuPresenter/CNVisitableListProvider.h>

class CNSelectionModel;
class CNHierarchicComponentAccess;
class CNComponentLoader;
class CNMatcher;

class CocoaIRMBMenuEntryListProvider;
typedef std::shared_ptr<CocoaIRMBMenuEntryListProvider> CocoaIRMBMenuEntryListProviderPtr;

class CocoaIRMBMenuEntryListProvider : public CNVisitableListProvider {
public:
    static CocoaIRMBMenuEntryListProviderPtr getNewInstance(std::shared_ptr<CNComponentLoader> componentLoader,
                                                         std::shared_ptr<CNMatcher> matcher,
                                                         std::shared_ptr<CNSelectionModel> selectionModel,
                                                         std::shared_ptr<CNHierarchicComponentAccess> modelAccess);
    virtual ~CocoaIRMBMenuEntryListProvider();
protected:
    CocoaIRMBMenuEntryListProvider(std::shared_ptr<CNComponentLoader> componentLoader,
                                std::shared_ptr<CNMatcher> matcher,
                                std::shared_ptr<CNSelectionModel> selectionModel,
                                std::shared_ptr<CNHierarchicComponentAccess> modelAccess);

public:
    const std::vector<std::shared_ptr<CNVisitable> > getVisitables() override;

private:
    std::shared_ptr<CNMatcher> matcher;
    std::shared_ptr<CNComponentLoader> componentLoader;
    std::shared_ptr<CNSelectionModel> selectionModel;
    std::shared_ptr<CNHierarchicComponentAccess> modelAccess;
};

#endif //COCOAIRMB_COCOAIRMBMENUENTRYLISTPROVIDER_H