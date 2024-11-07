#ifndef THIRD_PARTY_BLINK_RENDERER_MODULES_API2_PRIVATE_ATTRIBUTION_TYPES_H_
#define THIRD_PARTY_BLINK_RENDERER_MODULES_API2_PRIVATE_ATTRIBUTION_TYPES_H_

namespace blink {

// Budget request options from ad-tech to first party
class BudgetRequestOptions {
 public:
  BudgetRequestOptions();

  double min_usable_budget() const { return min_usable_budget_; }
  void set_min_usable_budget(double value) { min_usable_budget_ = value; }
  
  double desired_budget() const { return desired_budget_; }
  void set_desired_budget(double value) { desired_budget_ = value; }

 private:
  double min_usable_budget_;
  double desired_budget_;
};

}  

#endif  