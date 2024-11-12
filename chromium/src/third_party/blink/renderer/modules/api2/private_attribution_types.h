#ifndef THIRD_PARTY_BLINK_RENDERER_MODULES_API2_PRIVATE_ATTRIBUTION_TYPES_H_
#define THIRD_PARTY_BLINK_RENDERER_MODULES_API2_PRIVATE_ATTRIBUTION_TYPES_H_

#include <string>
#include <vector>
#include <map>

// Ad-tech origin? 

namespace blink {

class AdTechBudgetConfig {
 public:
  AdTechBudgetConfig();
  
  const std::string& ad_tech_origin() const { return ad_tech_origin_; }
  void set_ad_tech_origin(const std::string& value) { ad_tech_origin_ = value; }
  
  double allocated_budget() const { return allocated_budget_; }
  void set_allocated_budget(double value) { allocated_budget_ = value; }

 private:
  std::string ad_tech_origin_;
  double allocated_budget_;
};

class FirstPartyBudgetAllocationOptions {
 public:
  FirstPartyBudgetAllocationOptions();
  
  const std::vector<AdTechBudgetConfig>& ad_tech_budgets() const { 
    return ad_tech_budgets_; 
  }
  void set_ad_tech_budgets(const std::vector<AdTechBudgetConfig>& value) {
    ad_tech_budgets_ = value;
  }
  
  const std::string& aggregator() const { return aggregator_; }
  void set_aggregator(const std::string& value) { aggregator_ = value; }

 private:
  std::vector<AdTechBudgetConfig> ad_tech_budgets_;
  std::string aggregator_;
};

class API2ReportRequest {
 public:
  API2ReportRequest();
  
  double minimum_budget() const { return minimum_budget_; }
  void set_minimum_budget(double value) { minimum_budget_ = value; }
  
  double desired_budget() const { return desired_budget_; }
  void set_desired_budget(double value) { desired_budget_ = value; }
  
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
  double minimum_budget_;
  double desired_budget_;
  unsigned long histogram_size_;
  std::vector<std::string> impression_sites_;
  std::vector<std::string> intermediary_sites_;
  std::vector<std::string> conversion_sites_;
};

class API2ReportResponse {
 public:
  API2ReportResponse();
  
  const std::string& encrypted_epsilon() const { return encrypted_epsilon_; }
  void set_encrypted_epsilon(const std::string& value) { encrypted_epsilon_ = value; }
  bool is_sufficient() const { return is_sufficient_; }
  void set_is_sufficient(bool value) { is_sufficient_ = value; }

 private:
  std::string encrypted_epsilon_;
  bool is_sufficient_;
};

} 

#endif 