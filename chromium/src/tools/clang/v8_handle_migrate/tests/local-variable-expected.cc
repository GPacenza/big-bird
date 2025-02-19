// Copyright 2024 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Test file for the v8_handle_migrate clang tool.

#include "base/handles.h"
#include "base/objects.h"

using v8::internal::DirectHandle;
using v8::internal::Handle;
using v8::internal::HeapObject;

void consume_handle(Handle<HeapObject> o);
void consume_direct(DirectHandle<HeapObject> o);

void local_variable() {
  DirectHandle<HeapObject> h1;
  Handle<HeapObject> h2;
  consume_direct(h1);
  consume_direct(h2);
  consume_handle(h2);
}
