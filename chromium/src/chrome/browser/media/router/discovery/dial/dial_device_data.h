// Copyright 2012 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_ROUTER_DISCOVERY_DIAL_DIAL_DEVICE_DATA_H_
#define CHROME_BROWSER_MEDIA_ROUTER_DISCOVERY_DIAL_DIAL_DEVICE_DATA_H_

#include <string>
#include <string_view>

#include "base/time/time.h"
#include "net/base/ip_address.h"
#include "url/gurl.h"

namespace media_router {

// Dial device information that is used within the DialService and Registry on
// the IO thread. It is updated as new information arrives and a list of
// DialDeviceData is copied and sent to event listeners on the UI thread.
class DialDeviceData {
 public:
  DialDeviceData();
  DialDeviceData(const std::string& device_id,
                 const GURL& device_description_url,
                 const base::Time& response_time);
  DialDeviceData(const DialDeviceData& other);
  ~DialDeviceData();

  bool operator==(const DialDeviceData& other_data) const {
    return device_id_ == other_data.device_id_;
  }

  const std::string& device_id() const { return device_id_; }
  void set_device_id(std::string_view id) { device_id_ = id; }

  const std::string& label() const { return label_; }
  void set_label(std::string_view label) { label_ = label; }

  const GURL& device_description_url() const;
  void set_device_description_url(const GURL& url);

  const base::Time& response_time() const { return response_time_; }
  void set_response_time(const base::Time& response_time) {
    response_time_ = response_time;
  }

  int max_age() const { return max_age_; }
  void set_max_age(int max_age) { max_age_ = max_age; }
  bool has_max_age() const { return max_age_ > 0; }

  int config_id() const { return config_id_; }
  void set_config_id(int config_id) { config_id_ = config_id; }
  bool has_config_id() const { return config_id_ >= 0; }

  const net::IPAddress& ip_address() const { return ip_address_; }
  void set_ip_address(const net::IPAddress& ip_address);

  // Updates this DeviceData based on information from a new response in
  // |new_data|.  Returns |true| if a field was updated that is visible through
  // the DIAL API.
  bool UpdateFrom(const DialDeviceData& new_data);

  // Validates that |url| is a valid URL for this device - either a device
  // description URL, or a DIAL application URL.  The URL host must match the IP
  // address that the device is advertising SSDP on, and must not be publicly
  // routable.
  bool IsValidUrl(const GURL& url) const;

 private:
  // Hardware identifier from the DIAL response.  Not exposed to API clients.
  std::string device_id_;

  // Identifies this device to clients of the API as a proxy for the hardware
  // identifier.  Automatically generated by the DIAL registry.
  std::string label_;

  // The device description URL.
  GURL device_description_url_;

  // The time that the most recent response was received.
  base::Time response_time_;

  // The IP address that the device's SSDP advertisement was sent from.
  net::IPAddress ip_address_;

  // Optional (-1 means unset).
  int max_age_;

  // Optional (-1 means unset).
  int config_id_;
};

// TODO(mfoltz): Do we need this as well as ParsedDialDeviceDescriptionData?
struct DialDeviceDescriptionData {
 public:
  DialDeviceDescriptionData() = default;
  DialDeviceDescriptionData(const std::string& device_description,
                            const GURL& app_url);
  ~DialDeviceDescriptionData() = default;

  bool operator==(const DialDeviceDescriptionData& other_data) const;

  std::string device_description;
  GURL app_url;
};

}  // namespace media_router

#endif  // CHROME_BROWSER_MEDIA_ROUTER_DISCOVERY_DIAL_DIAL_DEVICE_DATA_H_
