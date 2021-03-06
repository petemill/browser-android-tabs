// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef IOS_WEB_PUBLIC_WEB_STATE_WEB_FRAME_UTIL_H_
#define IOS_WEB_PUBLIC_WEB_STATE_WEB_FRAME_UTIL_H_

#include <set>
#include <string>

namespace web {
class WebFrame;
class WebState;

// Returns the main WebFrame in |web_state|.
// Returns nullptr if |web_state| does not have a main frame.
WebFrame* GetMainWebFrame(WebState* web_state);

// Returns the ID of the main WebFrame in |web_state|.
// Returns "" if |web_state| does not have a main frame.
std::string GetMainWebFrameId(WebState* web_state);

// Returns the frame with ID |frame_id| in |web_state|.
// Returns nullptr if |web_state| does not have a frame with this ID.
WebFrame* GetWebFrameWithId(WebState* web_state, const std::string& frame_id);

// Returns the ID of |frame|. Returns std::string() if |frame| is nullptr.
std::string GetWebFrameId(WebFrame* frame);

// Returns all web frames in |web_state|.
std::set<WebFrame*> GetAllWebFrames(WebState* web_state);

}  // namespace web

#endif  // IOS_WEB_PUBLIC_WEB_STATE_WEB_FRAME_UTIL_H_
