// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_RASTER_TILE_TASK_H_
#define CC_RASTER_TILE_TASK_H_

#include <vector>

#include "cc/raster/task.h"

namespace cc {

class CC_EXPORT TileTask : public Task {
 public:
  typedef std::vector<scoped_refptr<TileTask>> Vector;

  const TileTask::Vector& dependencies() const { return dependencies_; }

  // `dependent` depends on `this`. A task may have at most one external
  // dependent.
  void SetExternalDependent(scoped_refptr<TileTask> dependent);
  scoped_refptr<TileTask>& external_dependent() { return external_dependent_; }

  // Called when an external task on which `this` depends has completed.
  // A task may have at most one external dependency, and may not mix internal
  // and external dependencies.
  void ExternalDependencyCompleted();

  // Indicates whether this TileTask can be run at the same time as other tasks
  // in the task graph. If false, this task will be scheduled with
  // TASK_CATEGORY_NONCONCURRENT_FOREGROUND. See comments in task_category.h.
  bool supports_concurrent_execution() const {
    return supports_concurrent_execution_ == SupportsConcurrentExecution::kYes;
  }

  // Indicates whether this TileTask can run at background thread priority. See
  // comments in task_category.h.
  bool supports_background_thread_priority() const {
    return supports_background_thread_priority_ ==
           SupportsBackgroundThreadPriority::kYes;
  }

  virtual bool IsRasterTask() const;

  // This function should be called from origin thread to process the completion
  // of the task.
  virtual void OnTaskCompleted() = 0;

  // This method should report true if the task contains image decodes that
  // might be for LCP candidates.
  virtual bool TaskContainsLCPCandidateImages() const;

  void DidComplete();
  bool HasCompleted() const;

 protected:
  enum class SupportsConcurrentExecution { kYes, kNo };
  enum class SupportsBackgroundThreadPriority { kYes, kNo };

  TileTask(SupportsConcurrentExecution supports_concurrent_execution,
           SupportsBackgroundThreadPriority supports_background_thread_priority,
           TileTask::Vector* dependencies = nullptr);
  ~TileTask() override;

  const SupportsConcurrentExecution supports_concurrent_execution_;
  const SupportsBackgroundThreadPriority supports_background_thread_priority_;
  TileTask::Vector dependencies_;
  // External task that depends on `this`.
  scoped_refptr<TileTask> external_dependent_;
  bool did_complete_ = false;
};

}  // namespace cc

#endif  // CC_RASTER_TILE_TASK_H_
