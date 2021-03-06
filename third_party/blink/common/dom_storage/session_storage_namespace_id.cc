// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/public/common/dom_storage/session_storage_namespace_id.h"

#include <algorithm>

#include "base/guid.h"
#include "base/logging.h"

namespace blink {

SessionStorageNamespaceId AllocateSessionStorageNamespaceId() {
  std::string guid = base::GenerateGUID();
  std::replace(guid.begin(), guid.end(), '-', '_');
  // The database deserialization code makes assumptions based on this length.
  DCHECK_EQ(guid.size(), kSessionStorageNamespaceIdLength);
  return guid;
}

}  // namespace blink
