// RUN: mlir-opt %s -transform-interpreter -split-input-file -verify-diagnostics

func.func @conv1d_nwc_wcf_dyn_ch_dim(%input: memref<4x6x?xf32>, %filter: memref<1x?x8xf32>, %output: memref<4x2x8xf32>) {
  // expected-error @+1 {{Attempted to vectorize, but failed}}
  linalg.conv_1d_nwc_wcf
    {dilations = dense<1> : tensor<1xi64>, strides = dense<3> : tensor<1xi64>}
    ins(%input, %filter : memref<4x6x?xf32>, memref<1x?x8xf32>)
    outs(%output : memref<4x2x8xf32>)
  return
}

module attributes {transform.with_named_sequence} {
  transform.named_sequence @__transform_main(%arg1: !transform.any_op {transform.readonly}) {
    %0 = transform.structured.match ops{["linalg.conv_1d_nwc_wcf"]} in %arg1 : (!transform.any_op) -> !transform.any_op
    transform.structured.vectorize %0 : !transform.any_op
    transform.yield
  }
}

// -----

// Masked vectorisation of 1D depthwise CW convs is not yet supported

func.func @depthwise_conv1d_ncw_cw(%input: memref<3x?x4xf32>, %filter: memref<?x1xf32>, %output: memref<3x?x4xf32>) {
  // expected-error @+1 {{Attempted to vectorize, but failed}}
  linalg.depthwise_conv_1d_ncw_cw
    {dilations = dense<2> : tensor<1xi64>, strides = dense<1> : tensor<1xi64>}
    ins(%input, %filter : memref<3x?x4xf32>, memref<?x1xf32>)
    outs(%output : memref<3x?x4xf32>)
  return
}

module attributes {transform.with_named_sequence} {
  transform.named_sequence @__transform_main(%arg1: !transform.any_op {transform.readonly}) {
    %0 = transform.structured.match ops{["linalg.depthwise_conv_1d_ncw_cw"]} in %arg1 : (!transform.any_op) -> !transform.any_op
    transform.structured.vectorize %0 vector_sizes [3, 4, 5, 1] : !transform.any_op
    transform.yield
  }
}

// -----

func.func @depthwise_conv1d_nwc_wc_dyn_w_dim(%input: memref<3x?x4xf32>, %filter: memref<?x4xf32>, %output: memref<3x?x4xf32>) {
  // expected-error @+1 {{Attempted to vectorize, but failed}}
  linalg.depthwise_conv_1d_nwc_wc
    {dilations = dense<2> : tensor<1xi64>, strides = dense<1> : tensor<1xi64>}
    ins(%input, %filter : memref<3x?x4xf32>, memref<?x4xf32>)
    outs(%output : memref<3x?x4xf32>)
  return
}

module attributes {transform.with_named_sequence} {
  transform.named_sequence @__transform_main(%arg1: !transform.any_op {transform.readonly}) {
    %0 = transform.structured.match ops{["linalg.depthwise_conv_1d_nwc_wc"]} in %arg1 : (!transform.any_op) -> !transform.any_op
    transform.structured.vectorize %0 vector_sizes [3, 2, 4, 2] : !transform.any_op
    transform.yield
  }
}

// -----

func.func @depthwise_conv1d_nwc_wc_dyn_ch_dim(%input: memref<3x5x?xf32>, %filter: memref<2x?xf32>, %output: memref<3x2x?xf32>) {
  // expected-error @+1 {{Attempted to vectorize, but failed}}
  linalg.depthwise_conv_1d_nwc_wc
    ins(%input, %filter : memref<3x5x?xf32>, memref<2x?xf32>)
    outs(%output : memref<3x2x?xf32>)
  return
}

module attributes {transform.with_named_sequence} {
  transform.named_sequence @__transform_main(%arg1: !transform.any_op {transform.readonly}) {
    %0 = transform.structured.match ops{["linalg.depthwise_conv_1d_nwc_wc"]} in %arg1 : (!transform.any_op) -> !transform.any_op
    transform.structured.vectorize %0 : !transform.any_op
    transform.yield
  }
}

// -----

func.func @depthwise_conv1d_nwc_wc_dyn_w_dim(%input: memref<3x?x3xf32>, %filter: memref<2x3xf32>, %output: memref<3x?x3xf32>) {
  // expected-error @+1 {{Attempted to vectorize, but failed}}
  linalg.depthwise_conv_1d_nwc_wc
    ins(%input, %filter : memref<3x?x3xf32>, memref<2x3xf32>)
    outs(%output : memref<3x?x3xf32>)
  return
}

module attributes {transform.with_named_sequence} {
  transform.named_sequence @__transform_main(%arg1: !transform.any_op {transform.readonly}) {
    %0 = transform.structured.match ops{["linalg.depthwise_conv_1d_nwc_wc"]} in %arg1 : (!transform.any_op) -> !transform.any_op
    transform.structured.vectorize %0 : !transform.any_op
    transform.yield
  }
}

// -----

func.func @conv1d_dyn_w_dim(%input: tensor<?xf32>, %filter: tensor<4xf32>, %output: tensor<?xf32>) -> tensor<?xf32> {
  // expected-error @+1 {{Attempted to vectorize, but failed}}
  %0 = linalg.conv_1d ins(%input, %filter : tensor<?xf32>, tensor<4xf32>)
                     outs(%output : tensor<?xf32>) -> tensor<?xf32>
  return %0 : tensor<?xf32>
}

module attributes {transform.with_named_sequence} {
  transform.named_sequence @__transform_main(%arg1: !transform.any_op {transform.readonly}) {
    %0 = transform.structured.match ops{["linalg.conv_1d"]} in %arg1 : (!transform.any_op) -> !transform.any_op
    transform.structured.vectorize %0 : !transform.any_op
    transform.yield
  }
}

// -----

func.func @test_pack_no_vectorize_dynamic_shape(%arg0: tensor<?xf32>, %arg1: tensor<4x16xf32>) -> tensor<4x16xf32> {
  %pad = arith.constant 0.000000e+00 : f32
  // expected-error @+1 {{Attempted to vectorize, but failed}}
  %pack = tensor.pack %arg0 padding_value(%pad : f32) inner_dims_pos = [0] inner_tiles = [16] into %arg1 : tensor<?xf32> -> tensor<4x16xf32>
  return %pack : tensor<4x16xf32>
}

module attributes {transform.with_named_sequence} {
  transform.named_sequence @__transform_main(%arg0: !transform.any_op {transform.readonly}) {
    %0 = transform.structured.match ops{["tensor.pack"]} in %arg0 : (!transform.any_op) -> !transform.any_op
    transform.structured.vectorize %0 : !transform.any_op
    transform.yield
  }
}

// -----

func.func @linalg_reduce_scalable(%input: tensor<?xf32>,
                                  %acc: tensor<f32>) -> tensor<f32> {

  // expected-error @+1 {{Attempted to vectorize, but failed}}
  %0 = linalg.reduce ins(%input : tensor<?xf32>) outs(%acc : tensor<f32>) dimensions = [0]
  (%in: f32, %init: f32) {
    %0 = arith.addf %in, %init : f32
    linalg.yield %0 : f32
  }
  return %0 : tensor<f32>
}

module attributes {transform.with_named_sequence} {
  transform.named_sequence @__transform_main(%arg1: !transform.any_op {transform.readonly}) {
    %0 = transform.structured.match ops{["linalg.reduce"]} in %arg1 : (!transform.any_op) -> !transform.any_op
    transform.structured.vectorize %0 vector_sizes [[4]] : !transform.any_op
    transform.yield
  }
}

// -----

func.func @linalg_generic_scalable_reduction_dim(%input: tensor<?x?xf32>,
                                                 %acc: tensor<?xf32>) -> tensor<?xf32> {

  // expected-error @+1 {{Attempted to vectorize, but failed}}
  %0 = linalg.generic { indexing_maps = [affine_map<(d0, d1) -> (d0, d1)>,
                                         affine_map<(d0, d1) -> (d0)>],
                        iterator_types = ["parallel", "reduction"] }
    ins(%input : tensor<?x?xf32>)
    outs(%acc : tensor<?xf32>) {
    ^bb(%in: f32, %out: f32) :
      %0 = arith.addf %in, %out : f32
      linalg.yield %0 : f32
    } -> tensor<?xf32>
  return %0 : tensor<?xf32>
}

module attributes {transform.with_named_sequence} {
  transform.named_sequence @__transform_main(%arg1: !transform.any_op {transform.readonly}) {
    %0 = transform.structured.match ops{["linalg.generic"]} in %arg1 : (!transform.any_op) -> !transform.any_op
    transform.structured.vectorize %0 vector_sizes [1, [4]] : !transform.any_op
    transform.yield
  }
}

// -----

func.func @linalg_matmul_scalable_leading_parallel_dim(%A: memref<?x?xf32>, %B: memref<?x?xf32>, %C: memref<?x?xf32>) {
  // expected-error @+1 {{Attempted to vectorize, but failed}}
  linalg.matmul ins(%A, %B: memref<?x?xf32>, memref<?x?xf32>)
            outs(%C: memref<?x?xf32>)
  return
}

module attributes {transform.with_named_sequence} {
  transform.named_sequence @__transform_main(%arg1: !transform.any_op {transform.readonly}) {
    %matmul = transform.structured.match ops{["linalg.matmul"]} in %arg1 : (!transform.any_op) -> !transform.any_op
    transform.structured.vectorize %matmul vector_sizes [[8], 16, 4] : !transform.any_op
    transform.yield
  }
}
