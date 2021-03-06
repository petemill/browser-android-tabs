// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_PUBLIC_COMMON_SERVICE_WORKER_SERVICE_WORKER_UTILS_H_
#define THIRD_PARTY_BLINK_PUBLIC_COMMON_SERVICE_WORKER_SERVICE_WORKER_UTILS_H_

#include "third_party/blink/public/common/common_export.h"

namespace blink {

// Specifies strategy to generate V8 eager code cache when a script is stored
// into CacheStorage by a service worker. Eager code cache is more exhaustive
// code cache and generated by specifing v8::ScriptCompiler::kEagerCompile.
// Refer to https://crbug.com/768705 for more details.
//
// The default strategy is |kDuringInstallEvent|.
//
// IMPORTANT NOTE: We have some other heuristics/mechanisms to generate
// (non eager) code cache outside service worker. This does NOT affect other
// code caching mechanisms.
enum class EagerCodeCacheStrategy {
  // Never generate eager code cache.
  kDontGenerate,
  // Generate eager code cache when Cache#put() is called in install event
  // handlers. The promise of Cache#put() is resolved after the code cache is
  // generated. Don't generate eager code cache outside install event handlers.
  kDuringInstallEvent,
  // This specifies the same behavior as |kDuringInstallEvent| but also
  // schedules an idle task to generate eager code cache if Cache#put()
  // is called outside install event handlers (e.g. fetch event handlers).
  // The promise of Cache#put() doesn't wait for cache generation when put()
  // is called outside install event handlers.
  kOnIdleTask,
};

BLINK_COMMON_EXPORT extern const char kServiceWorkerEagerCodeCacheStrategy[];

class ServiceWorkerUtils {
 public:
  // Whether the new service worker glue for NetworkService is enabled. Always
  // returns true as the glue is always enabled now.
  // TODO(crbug.com/715640): Remove this after non-NetS13nSW is removed.
  static bool BLINK_COMMON_EXPORT IsServicificationEnabled();

  static bool BLINK_COMMON_EXPORT IsImportedScriptUpdateCheckEnabled();

  static EagerCodeCacheStrategy BLINK_COMMON_EXPORT GetEagerCodeCacheStrategy();
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_PUBLIC_COMMON_SERVICE_WORKER_SERVICE_WORKER_UTILS_H_
