// Copyright 2019 Endless Mobile, Inc.
// Portions copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <sys/types.h>

#include <optional>
#include <vector>

#include <nickle.h>

#include "base/base.h"
#include "base/unique_fd.h"

namespace zypak::sandbox::mimic_strategy {

std::optional<pid_t> HandleFork(nickle::Reader* reader, const unique_fd& sandbox_service_fd,
                                std::vector<unique_fd> fds);

}
