
#ifndef CONTENT_BROWSER_ATTRIBUTION_REPORTING_ATTRIBUTION_STORAGE_PDSLIB_H_
#define CONTENT_BROWSER_ATTRIBUTION_REPORTING_ATTRIBUTION_STORAGE_PDSLIB_H_

#include <stdint.h>

#include <memory>
#include <optional>
#include <set>
#include <string>
#include <vector>

#include "base/containers/enum_set.h"
#include "base/containers/span.h"
#include "base/files/file_path.h"
#include "base/sequence_checker.h"
#include "base/thread_annotations.h"
#include "base/types/expected.h"
#include "content/browser/attribution_reporting/aggregatable_debug_rate_limit_table.h"
#include "content/browser/attribution_reporting/aggregatable_result.mojom-forward.h"
#include "content/browser/attribution_reporting/attribution_report.h"
#include "content/browser/attribution_reporting/event_level_result.mojom-forward.h"
#include "content/browser/attribution_reporting/rate_limit_table.h"
#include "content/browser/attribution_reporting/stored_source.h"
#include "content/common/content_export.h"
#include "content/public/browser/attribution_data_model.h"
#include "content/public/browser/storage_partition.h"
#include "sql/database.h"
#include "sql/transaction.h"
#include "third_party/blink/public/mojom/aggregation_service/aggregatable_report.mojom-forward.h"
#include "third_party/pdslib/src/events/simple_events.rs.h"

namespace base {
class Time;
class TimeDelta;
class Uuid;
}  // namespace base

namespace content {

class StorableSource;

class CONTENT_EXPORT AttributionStoragePdsLib {
  public:
    AttributionStoragePdsLib();
    
    [[nodiscard]] std::optional<StoredSource> InsertSource(
      const StorableSource& source,
      base::Time source_time,
      int num_attributions,
      bool event_level_active,
      double randomized_response_rate,
      StoredSource::AttributionLogic attribution_logic,
      base::Time aggregatable_report_window_time);

};

}  // namespace content

#endif  // CONTENT_BROWSER_ATTRIBUTION_REPORTING_ATTRIBUTION_STORAGE_PDSLIB_H_