// Copyright 2024 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef IOS_CHROME_BROWSER_SHARED_MODEL_PROFILE_PROFILE_IOS_FORWARD_H_
#define IOS_CHROME_BROWSER_SHARED_MODEL_PROFILE_PROFILE_IOS_FORWARD_H_

// Include this header in .h files instead of forward-declaring `ProfileIOS` or
// `ProfileIOS`. This allows migration of the class name to proceed
// without touching hundreds of files at once.
// TODO(crbug.com/359821785): Remove this header and replace all usages with a
// normal forward-declaration of `ProfileIOS` once the migration is complete.

class ProfileIOS;

#endif  // IOS_CHROME_BROWSER_SHARED_MODEL_PROFILE_PROFILE_IOS_FORWARD_H_
