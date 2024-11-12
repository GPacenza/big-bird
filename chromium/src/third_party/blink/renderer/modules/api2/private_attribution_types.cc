#include "third_party/blink/renderer/modules/api2/private_attribution_types.h"

namespace blink {

AdTechBudgetConfig::AdTechBudgetConfig() :
     allocated_budget_(0.0) {}

FirstPartyBudgetAllocationOptions::FirstPartyBudgetAllocationOptions() {}

API2ReportRequest::API2ReportRequest() :
      minimum_budget_(0.0)
    , desired_budget_(0.0)
    , histogram_size_(0) {}


API2ReportResponse::API2ReportResponse() :
     is_sufficient_(false) {}

}  