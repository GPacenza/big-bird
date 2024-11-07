// third_party/blink/renderer/modules/api2/private_attribution_types.h

#ifndef THIRD_PARTY_BLINK_RENDERER_MODULES_API2_PRIVATE_ATTRIBUTION_TYPES_H_
#define THIRD_PARTY_BLINK_RENDERER_MODULES_API2_PRIVATE_ATTRIBUTION_TYPES_H_

#include <string>
#include <vector>
#include <map>

namespace blink {

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

class BudgetDelegatorResponse {
 public:
  BudgetDelegatorResponse();
  
  const std::string& encrypted_epsilon() const { return encrypted_epsilon_; }
  //void set_encrypted_epsilon() const { encrypted_epsilon_ = "some value"; }

 private:
  std::string encrypted_epsilon_;
};

class PrivateAttributionConversionOptions {
 public:
  PrivateAttributionConversionOptions();
  
  const std::string& aggregator() const { return aggregator_; }
  void set_aggregator(const std::string& value) { aggregator_ = value; }
  
  const std::map<std::string, std::string>& delegated_encrypted_epsilons() const {
    return delegated_encrypted_epsilons_;
  }
  void set_delegated_encrypted_epsilons(
      const std::map<std::string, std::string>& value) {
    delegated_encrypted_epsilons_ = value;
  }
  
  unsigned long histogram_size() const { return histogram_size_; }
  void set_histogram_size(unsigned long value) { histogram_size_ = value; }
  
  const std::vector<std::string>& impression_sites() const {
    return impression_sites_;
  }
  void set_impression_sites(const std::vector<std::string>& sites) {
    impression_sites_ = sites;
  }
  
  const std::vector<std::string>& intermediary_sites() const {
    return intermediary_sites_;
  }
  void set_intermediary_sites(const std::vector<std::string>& sites) {
    intermediary_sites_ = sites;
  }
  
  const std::vector<std::string>& conversion_sites() const {
    return conversion_sites_;
  }
  void set_conversion_sites(const std::vector<std::string>& sites) {
    conversion_sites_ = sites;
  }

 private:
  std::string aggregator_;
  std::map<std::string, std::string> delegated_encrypted_epsilons_;
  unsigned long histogram_size_;
  std::vector<std::string> impression_sites_;
  std::vector<std::string> intermediary_sites_;
  std::vector<std::string> conversion_sites_;
};

enum class PrivateAttributionLogic {
  kLastTouch
};

}  

#endif  