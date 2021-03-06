// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_SERVICES_DEVICE_SYNC_CRYPTAUTH_CLIENT_H_
#define CHROMEOS_SERVICES_DEVICE_SYNC_CRYPTAUTH_CLIENT_H_

#include <memory>
#include <string>

#include "base/callback_forward.h"
#include "base/macros.h"
#include "chromeos/services/device_sync/network_request_error.h"
#include "net/traffic_annotation/network_traffic_annotation.h"

namespace cryptauth {
class GetMyDevicesRequest;
class GetMyDevicesResponse;
class FindEligibleUnlockDevicesRequest;
class FindEligibleUnlockDevicesResponse;
class SendDeviceSyncTickleRequest;
class SendDeviceSyncTickleResponse;
class ToggleEasyUnlockRequest;
class ToggleEasyUnlockResponse;
class SetupEnrollmentRequest;
class SetupEnrollmentResponse;
class FinishEnrollmentRequest;
class FinishEnrollmentResponse;
class FindEligibleForPromotionRequest;
class FindEligibleForPromotionResponse;
}  // namespace cryptauth

namespace cryptauthv2 {
class SyncKeysRequest;
class SyncKeysResponse;
class EnrollKeysRequest;
class EnrollKeysResponse;
}  // namespace cryptauthv2

namespace chromeos {

namespace device_sync {

// Interface for making API requests to the CryptAuth service, which
// manages cryptographic credentials (ie. public keys) for a user's devices.
// Implmentations shall only processes a single request, so create a new
// instance for each request you make. DO NOT REUSE.
// For documentation on each API call, see
// chromeos/services/device_sync/proto/cryptauth_api.proto
class CryptAuthClient {
 public:
  typedef base::Callback<void(NetworkRequestError)> ErrorCallback;

  virtual ~CryptAuthClient() {}

  // GetMyDevices
  typedef base::Callback<void(const cryptauth::GetMyDevicesResponse&)>
      GetMyDevicesCallback;
  virtual void GetMyDevices(const cryptauth::GetMyDevicesRequest& request,
                            const GetMyDevicesCallback& callback,
                            const ErrorCallback& error_callback,
                            const net::PartialNetworkTrafficAnnotationTag&
                                partial_traffic_annotation) = 0;

  // FindEligibleUnlockDevices
  typedef base::Callback<void(
      const cryptauth::FindEligibleUnlockDevicesResponse&)>
      FindEligibleUnlockDevicesCallback;
  virtual void FindEligibleUnlockDevices(
      const cryptauth::FindEligibleUnlockDevicesRequest& request,
      const FindEligibleUnlockDevicesCallback& callback,
      const ErrorCallback& error_callback) = 0;

  // FindEligibleForPromotion
  typedef base::Callback<void(
      const cryptauth::FindEligibleForPromotionResponse&)>
      FindEligibleForPromotionCallback;
  virtual void FindEligibleForPromotion(
      const cryptauth::FindEligibleForPromotionRequest& request,
      const FindEligibleForPromotionCallback& callback,
      const ErrorCallback& error_callback) = 0;

  // SendDeviceSyncTickle
  typedef base::Callback<void(const cryptauth::SendDeviceSyncTickleResponse&)>
      SendDeviceSyncTickleCallback;
  virtual void SendDeviceSyncTickle(
      const cryptauth::SendDeviceSyncTickleRequest& request,
      const SendDeviceSyncTickleCallback& callback,
      const ErrorCallback& error_callback,
      const net::PartialNetworkTrafficAnnotationTag&
          partial_traffic_annotation) = 0;

  // ToggleEasyUnlock
  typedef base::Callback<void(const cryptauth::ToggleEasyUnlockResponse&)>
      ToggleEasyUnlockCallback;
  virtual void ToggleEasyUnlock(
      const cryptauth::ToggleEasyUnlockRequest& request,
      const ToggleEasyUnlockCallback& callback,
      const ErrorCallback& error_callback) = 0;

  // SetupEnrollment
  typedef base::Callback<void(const cryptauth::SetupEnrollmentResponse&)>
      SetupEnrollmentCallback;
  virtual void SetupEnrollment(const cryptauth::SetupEnrollmentRequest& request,
                               const SetupEnrollmentCallback& callback,
                               const ErrorCallback& error_callback) = 0;

  // FinishEnrollment
  typedef base::Callback<void(const cryptauth::FinishEnrollmentResponse&)>
      FinishEnrollmentCallback;
  virtual void FinishEnrollment(
      const cryptauth::FinishEnrollmentRequest& request,
      const FinishEnrollmentCallback& callback,
      const ErrorCallback& error_callback) = 0;

  // SyncKeys (CryptAuth v2 Enrollment)
  typedef base::Callback<void(const cryptauthv2::SyncKeysResponse&)>
      SyncKeysCallback;
  virtual void SyncKeys(const cryptauthv2::SyncKeysRequest& request,
                        const SyncKeysCallback& callback,
                        const ErrorCallback& error_callback) = 0;

  // EnrollKeys (CryptAuth v2 Enrollment)
  typedef base::Callback<void(const cryptauthv2::EnrollKeysResponse&)>
      EnrollKeysCallback;
  virtual void EnrollKeys(const cryptauthv2::EnrollKeysRequest& request,
                          const EnrollKeysCallback& callback,
                          const ErrorCallback& error_callback) = 0;

  // Returns the access token used to make the request. If no request has been
  // made yet, this function will return an empty string.
  virtual std::string GetAccessTokenUsed() = 0;
};

// Interface for creating CryptAuthClient instances. Because each
// CryptAuthClient instance can only be used for one API call, a factory makes
// it easier to make multiple requests in sequence or in parallel.
class CryptAuthClientFactory {
 public:
  virtual ~CryptAuthClientFactory() {}

  virtual std::unique_ptr<CryptAuthClient> CreateInstance() = 0;
};

}  // namespace device_sync

}  // namespace chromeos

#endif  // CHROMEOS_SERVICES_DEVICE_SYNC_CRYPTAUTH_CLIENT_H_
