//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03, c++11, c++14, c++17, c++20

#include <benchmark/benchmark.h>
#include <functional>

template <bool Opaque>
static void BM_invoke(benchmark::State& state) {
  std::move_only_function<void()> func = [] {};

  for (auto _ : state) {
    if constexpr (Opaque)
      benchmark::DoNotOptimize(func);
    func();
  }
}
BENCHMARK(BM_invoke<false>)->Name("move_only_function call (transparent)");
BENCHMARK(BM_invoke<true>)->Name("move_only_function call (opaque)");

static void BM_move_assign(benchmark::State& state) {
  std::move_only_function<void()> func1 = [] {};
  std::move_only_function<void()> func2;

  for (auto _ : state) {
    benchmark::DoNotOptimize(func1);
    benchmark::DoNotOptimize(func2);
    func2 = std::move(func1);
    benchmark::DoNotOptimize(func1);
    benchmark::DoNotOptimize(func2);
    func1 = std::move(func2);
  }
}
BENCHMARK(BM_move_assign)->Name("operator=(move_only_function&&)");

BENCHMARK_MAIN();
