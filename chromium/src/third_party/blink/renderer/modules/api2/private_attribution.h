

#ifndef THIRD_PARTY_BLINK_RENDERER_MODULES_API2_PRIVATE_ATTRIBUTION_H_
#define THIRD_PARTY_BLINK_RENDERER_MODULES_API2_PRIVATE_ATTRIBUTION_H_

#include "third_party/blink/renderer/modules/api2/private_attribution_types.h"

namespace blink {

class BudgetRequestOptions;
class BudgetDelegatorResponse;
class PrivateAttributionConversionOptions;

class PrivateAttribution {
 public:
  PrivateAttribution();
  virtual ~PrivateAttribution();

  virtual void GetDelegatedBudget(const BudgetRequestOptions& options);
  virtual void MeasureConversion(const PrivateAttributionConversionOptions& options);
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_MODULES_API2_PRIVATE_ATTRIBUTION_H_