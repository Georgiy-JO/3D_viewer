#include <benchmark/benchmark.h>
#include "s21_matrix.h"

namespace matrix {

S21Matrix CreateRandomMatrix(int rows, int cols) {
    S21Matrix mat(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mat(i, j) = static_cast<double>(rand()) / RAND_MAX * 100.0;
        }
    }
    return mat;
}

static void BM_MatrixConstructor(benchmark::State& state) {
    const int size = state.range(0);
    for (auto _ : state) {
        S21Matrix mat(size, size);
        benchmark::DoNotOptimize(mat);
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MatrixConstructor)
    ->RangeMultiplier(2)->Range(8, 512)->Complexity(benchmark::oN);

static void BM_MatrixCopy(benchmark::State& state) {
    const int size = state.range(0);
    S21Matrix mat = CreateRandomMatrix(size, size);
    for (auto _ : state) {
        S21Matrix copy(mat);
        benchmark::DoNotOptimize(copy);
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MatrixCopy)
    ->RangeMultiplier(2)->Range(8, 512)->Complexity(benchmark::oN);

static void BM_MatrixAddition(benchmark::State& state) {
    const int size = state.range(0);
    S21Matrix mat1 = CreateRandomMatrix(size, size);
    S21Matrix mat2 = CreateRandomMatrix(size, size);
    for (auto _ : state) {
        S21Matrix result = mat1 + mat2;
        benchmark::DoNotOptimize(result);
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MatrixAddition)
    ->RangeMultiplier(2)->Range(8, 512)->Complexity(benchmark::oN);

static void BM_MatrixMultiplication(benchmark::State& state) {
    const int size = state.range(0);
    S21Matrix mat1 = CreateRandomMatrix(size, size);
    S21Matrix mat2 = CreateRandomMatrix(size, size);
    for (auto _ : state) {
        S21Matrix result = mat1 * mat2;
        benchmark::DoNotOptimize(result);
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MatrixMultiplication)
    ->RangeMultiplier(2)->Range(8, 512)->Complexity(benchmark::oN);

static void BM_MatrixTranspose(benchmark::State& state) {
    const int size = state.range(0);
    S21Matrix mat = CreateRandomMatrix(size, size);
    for (auto _ : state) {
        S21Matrix result = mat.Transpose();
        benchmark::DoNotOptimize(result);
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MatrixTranspose)
    ->RangeMultiplier(2)->Range(8, 512)->Complexity(benchmark::oN);

static void BM_MatrixDeterminant(benchmark::State& state) {
    const int size = state.range(0);
    S21Matrix mat = CreateRandomMatrix(size, size);
    for (auto _ : state) {
        double det = mat.Determinant();
        benchmark::DoNotOptimize(det);
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MatrixDeterminant)
    ->RangeMultiplier(2)->Range(2, 512)->Complexity(benchmark::oN);

static void BM_MatrixInverse(benchmark::State& state) {
    const int size = state.range(0);
    S21Matrix mat = CreateRandomMatrix(size, size);

    for (int i = 0; i < size; ++i) {
        mat(i, i) += 100.0;
    }
    for (auto _ : state) {
        S21Matrix result = mat.InverseMatrix();
        benchmark::DoNotOptimize(result);
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MatrixInverse)
    ->RangeMultiplier(2)->Range(2, 64)->Complexity(benchmark::oN);

}  // namespace matrix

BENCHMARK_MAIN();
