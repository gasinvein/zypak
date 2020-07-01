// Copyright 2019 Endless Mobile, Inc.
// Portions copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <array>
#include <vector>

#include "base/base.h"
#include "base/unique_fd.h"

namespace zypak {

// Utilities for reading and writing data to a socket.
// 'fds' is always a vector of file descriptors being passed over a socket.
class Socket {
 public:
  struct ReadOptions {
    ReadOptions() {}

    std::vector<unique_fd>* fds = nullptr;
    pid_t* pid = nullptr;
  };

  static ssize_t Read(int fd, std::vector<std::byte>* buffer, ReadOptions options = {});
  static ssize_t Read(int fd, std::byte* buffer, size_t size, ReadOptions options = {});

  template <size_t N>
  static ssize_t Read(int fd, std::array<std::byte, N>* buffer, ReadOptions options = {}) {
    return Read(fd, buffer->data(), N, std::move(options));
  }

  struct WriteOptions {
    WriteOptions() {}

    const std::vector<int>* fds = nullptr;
  };

  static bool Write(int fd, const std::byte* buffer, size_t length, WriteOptions options = {});
  static bool Write(int fd, const std::vector<std::byte>& buffer, WriteOptions options = {});
  static bool Write(int fd, std::string_view buffer, WriteOptions options = {});

  template <size_t N>
  static bool Write(int fd, const std::array<std::byte, N>& buffer, WriteOptions options = {}) {
    return Write(fd, buffer.data(), N, std::move(options));
  }

  struct Pipe {
    unique_fd read;
    unique_fd write;
  };
  static std::optional<Pipe> OpenPipe();

  static std::optional<std::pair<unique_fd, unique_fd>> OpenSocketPair();

  static bool EnableReceivePid(int fd);
};

}  // namespace zypak
