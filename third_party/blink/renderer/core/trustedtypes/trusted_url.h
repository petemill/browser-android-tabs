// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_TRUSTEDTYPES_TRUSTED_URL_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_TRUSTEDTYPES_TRUSTED_URL_H_

#include "third_party/blink/renderer/core/core_export.h"
#include "third_party/blink/renderer/platform/bindings/script_wrappable.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

namespace blink {

class CORE_EXPORT TrustedURL final : public ScriptWrappable {
  DEFINE_WRAPPERTYPEINFO();

 public:
  static TrustedURL* Create(const String& url) {
    return MakeGarbageCollected<TrustedURL>(url);
  }

  TrustedURL(const String& url);

  // TrustedURL.idl
  String toString() const;

 private:
  const String url_;
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_TRUSTEDTYPES_TRUSTED_URL_H_
