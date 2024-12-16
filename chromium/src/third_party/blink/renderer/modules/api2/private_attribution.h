#ifndef THIRD_PARTY_BLINK_RENDERER_MODULES_API2_PRIVATE_ATTRIBUTION_H_
#define THIRD_PARTY_BLINK_RENDERER_MODULES_API2_PRIVATE_ATTRIBUTION_H_

#include "third_party/blink/renderer/modules/api2/private_attribution_types.h"
#include "third_party/blink/renderer/platform/bindings/script_wrappable.h"
#include "third_party/blink/renderer/platform/heap/garbage_collected.h"
#include "third_party/blink/renderer/platform/heap/member.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

namespace blink {

class ExecutionContext;
class AdTechBudgetConfig;
class FirstPartyBudgetAllocationOptions;
class API2ReportRequest;
class API2ReportResponse;

class PrivateAttribution final : public ScriptWrappable {
  DEFINE_WRAPPERTYPEINFO();

 public:
  explicit PrivateAttribution(ExecutionContext*);
  ~PrivateAttribution() override;

  virtual void ConfigureAdTechBudgets(
      const FirstPartyBudgetAllocationOptions& options);

  // Ad-tech requests report
  virtual void RequestAPI2Report(const API2ReportRequest& options);

  // garbage collection
  void Trace(Visitor*) const override;

 private:
  // Store the execution context for security checks
  Member<ExecutionContext> execution_context_;
  
  // Budget management state
  // TODO: Add data structures to track budget allocations
};

}  