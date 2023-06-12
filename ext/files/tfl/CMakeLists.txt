cmake_minimum_required(VERSION 3.21)

project(tfl
  LANGUAGES CXX
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")

set(EXT ${CMAKE_SOURCE_DIR}/..)
set(USR_DIR ${EXT}/usr)
set(GEMMLOWP_DIR ${EXT}/gemmlowp)
set(RUY_DIR ${EXT}/ruy)

set(BASE_DIR ${CMAKE_SOURCE_DIR})
set(TFL_DIR ${BASE_DIR}/tensorflow/lite)

add_library(${PROJECT_NAME} STATIC

  ${TFL_DIR}/micro/debug_log.cc
  ${TFL_DIR}/micro/micro_time.cc
  ${TFL_DIR}/micro/system_setup.cc

  ${TFL_DIR}/kernels/kernel_util.cc
  ${TFL_DIR}/kernels/internal/quantization_util.cc
  ${TFL_DIR}/kernels/internal/portable_tensor_utils.cc
  ${TFL_DIR}/kernels/internal/common.cc
  ${TFL_DIR}/kernels/internal/tensor_utils.cc
  ${TFL_DIR}/kernels/internal/tensor_ctypes.cc
  ${TFL_DIR}/kernels/internal/reference/portable_tensor_utils.cc
  ${TFL_DIR}/kernels/internal/reference/comparisons.cc
  ${TFL_DIR}/micro/arena_allocator/recording_single_arena_buffer_allocator.cc
  ${TFL_DIR}/micro/arena_allocator/non_persistent_arena_buffer_allocator.cc
  ${TFL_DIR}/micro/arena_allocator/single_arena_buffer_allocator.cc
  ${TFL_DIR}/micro/arena_allocator/persistent_arena_buffer_allocator.cc
  ${TFL_DIR}/micro/memory_planner/non_persistent_buffer_planner_shim.cc
  ${TFL_DIR}/micro/memory_planner/greedy_memory_planner.cc
  ${TFL_DIR}/micro/memory_planner/linear_memory_planner.cc
  ${TFL_DIR}/micro/micro_profiler.cc
  ${TFL_DIR}/micro/test_helpers.cc
  ${TFL_DIR}/micro/micro_resource_variable.cc
  ${TFL_DIR}/micro/test_helper_custom_ops.cc
  ${TFL_DIR}/micro/micro_graph.cc
  ${TFL_DIR}/micro/mock_micro_graph.cc
  ${TFL_DIR}/micro/micro_log.cc
  ${TFL_DIR}/micro/micro_interpreter.cc
  ${TFL_DIR}/micro/micro_context.cc
  ${TFL_DIR}/micro/micro_allocator.cc
  ${TFL_DIR}/micro/micro_string.cc
  ${TFL_DIR}/micro/micro_utils.cc
  ${TFL_DIR}/micro/micro_op_resolver.cc
  ${TFL_DIR}/micro/micro_allocation_info.cc
  ${TFL_DIR}/micro/recording_micro_allocator.cc
  ${TFL_DIR}/micro/fake_micro_context.cc
  ${TFL_DIR}/micro/flatbuffer_utils.cc
  ${TFL_DIR}/micro/memory_helpers.cc
  ${TFL_DIR}/micro/tflite_bridge/flatbuffer_conversions_bridge.cc
  ${TFL_DIR}/micro/tflite_bridge/micro_error_reporter.cc
  ${TFL_DIR}/schema/schema_utils.cc
  ${TFL_DIR}/core/c/common.cc
  ${TFL_DIR}/core/api/op_resolver.cc
  ${TFL_DIR}/core/api/flatbuffer_conversions.cc
  ${TFL_DIR}/core/api/tensor_utils.cc
  ${TFL_DIR}/core/api/error_reporter.cc

  ${TFL_DIR}/micro/kernels/unidirectional_sequence_lstm.cc
  ${TFL_DIR}/micro/kernels/quantize.cc
  ${TFL_DIR}/micro/kernels/arg_min_max.cc
  ${TFL_DIR}/micro/kernels/squeeze.cc
  ${TFL_DIR}/micro/kernels/pooling_common.cc
  ${TFL_DIR}/micro/kernels/kernel_util.cc
  ${TFL_DIR}/micro/kernels/read_variable.cc
  ${TFL_DIR}/micro/kernels/dequantize_common.cc
  ${TFL_DIR}/micro/kernels/micro_tensor_utils.cc
  ${TFL_DIR}/micro/kernels/leaky_relu.cc
  ${TFL_DIR}/micro/kernels/log_softmax.cc
  ${TFL_DIR}/micro/kernels/elu.cc
  ${TFL_DIR}/micro/kernels/svdf.cc
  ${TFL_DIR}/micro/kernels/prelu_common.cc
  ${TFL_DIR}/micro/kernels/prelu.cc
  ${TFL_DIR}/micro/kernels/resize_bilinear.cc
  ${TFL_DIR}/micro/kernels/gather.cc
  ${TFL_DIR}/micro/kernels/expand_dims.cc
  ${TFL_DIR}/micro/kernels/var_handle.cc
  ${TFL_DIR}/micro/kernels/pooling.cc
  ${TFL_DIR}/micro/kernels/concatenation.cc
  ${TFL_DIR}/micro/kernels/batch_to_space_nd.cc
  ${TFL_DIR}/micro/kernels/embedding_lookup.cc
  ${TFL_DIR}/micro/kernels/elementwise.cc
  ${TFL_DIR}/micro/kernels/add_common.cc
  ${TFL_DIR}/micro/kernels/resize_nearest_neighbor.cc
  ${TFL_DIR}/micro/kernels/shape.cc
  ${TFL_DIR}/micro/kernels/conv.cc
  ${TFL_DIR}/micro/kernels/circular_buffer.cc
  ${TFL_DIR}/micro/kernels/depthwise_conv.cc
  ${TFL_DIR}/micro/kernels/sub.cc
  ${TFL_DIR}/micro/kernels/slice.cc
  ${TFL_DIR}/micro/kernels/lstm_eval_common.cc
  ${TFL_DIR}/micro/kernels/space_to_depth.cc
  ${TFL_DIR}/micro/kernels/ethosu.cc
  ${TFL_DIR}/micro/kernels/conv_common.cc
  ${TFL_DIR}/micro/kernels/call_once.cc
  ${TFL_DIR}/micro/kernels/strided_slice.cc
  ${TFL_DIR}/micro/kernels/softmax.cc
  ${TFL_DIR}/micro/kernels/split_v.cc
  ${TFL_DIR}/micro/kernels/cumsum.cc
  ${TFL_DIR}/micro/kernels/ceil.cc
  ${TFL_DIR}/micro/kernels/logistic_common.cc
  ${TFL_DIR}/micro/kernels/neg.cc
  ${TFL_DIR}/micro/kernels/activations_common.cc
  ${TFL_DIR}/micro/kernels/reduce_common.cc
  ${TFL_DIR}/micro/kernels/logical_common.cc
  ${TFL_DIR}/micro/kernels/leaky_relu_common.cc
  ${TFL_DIR}/micro/kernels/assign_variable.cc
  ${TFL_DIR}/micro/kernels/softmax_common.cc
  ${TFL_DIR}/micro/kernels/fill.cc
  ${TFL_DIR}/micro/kernels/space_to_batch_nd.cc
  ${TFL_DIR}/micro/kernels/quantize_common.cc
  ${TFL_DIR}/micro/kernels/if.cc
  ${TFL_DIR}/micro/kernels/depthwise_conv_common.cc
  ${TFL_DIR}/micro/kernels/maximum_minimum.cc
  ${TFL_DIR}/micro/kernels/tanh.cc
  ${TFL_DIR}/micro/kernels/round.cc
  ${TFL_DIR}/micro/kernels/pad.cc
  ${TFL_DIR}/micro/kernels/while.cc
  ${TFL_DIR}/micro/kernels/cast.cc
  ${TFL_DIR}/micro/kernels/floor.cc
  ${TFL_DIR}/micro/kernels/logical.cc
  ${TFL_DIR}/micro/kernels/fully_connected.cc
  ${TFL_DIR}/micro/kernels/select.cc
  ${TFL_DIR}/micro/kernels/fully_connected_common.cc
  ${TFL_DIR}/micro/kernels/split.cc
  ${TFL_DIR}/micro/kernels/mirror_pad.cc
  ${TFL_DIR}/micro/kernels/kernel_runner.cc
  ${TFL_DIR}/micro/kernels/circular_buffer_common.cc
  ${TFL_DIR}/micro/kernels/squared_difference.cc
  ${TFL_DIR}/micro/kernels/unpack.cc
  ${TFL_DIR}/micro/kernels/transpose.cc
  ${TFL_DIR}/micro/kernels/depth_to_space.cc
  ${TFL_DIR}/micro/kernels/div.cc
  ${TFL_DIR}/micro/kernels/lstm_eval.cc
  ${TFL_DIR}/micro/kernels/mul_common.cc
  ${TFL_DIR}/micro/kernels/transpose_conv.cc
  ${TFL_DIR}/micro/kernels/hard_swish_common.cc
  ${TFL_DIR}/micro/kernels/comparisons.cc
  ${TFL_DIR}/micro/kernels/activations.cc
  ${TFL_DIR}/micro/kernels/broadcast_args.cc
  ${TFL_DIR}/micro/kernels/sub_common.cc
  ${TFL_DIR}/micro/kernels/detection_postprocess.cc
  ${TFL_DIR}/micro/kernels/add_n.cc
  ${TFL_DIR}/micro/kernels/exp.cc
  ${TFL_DIR}/micro/kernels/zeros_like.cc
  ${TFL_DIR}/micro/kernels/floor_mod.cc
  ${TFL_DIR}/micro/kernels/hard_swish.cc
  ${TFL_DIR}/micro/kernels/floor_div.cc
  ${TFL_DIR}/micro/kernels/reduce.cc
  ${TFL_DIR}/micro/kernels/pack.cc
  ${TFL_DIR}/micro/kernels/logistic.cc
  ${TFL_DIR}/micro/kernels/add.cc
  ${TFL_DIR}/micro/kernels/gather_nd.cc
  ${TFL_DIR}/micro/kernels/svdf_common.cc
  ${TFL_DIR}/micro/kernels/broadcast_to.cc
  ${TFL_DIR}/micro/kernels/l2_pool_2d.cc
  ${TFL_DIR}/micro/kernels/mul.cc
  ${TFL_DIR}/micro/kernels/reshape.cc
  ${TFL_DIR}/micro/kernels/l2norm.cc
  ${TFL_DIR}/micro/kernels/dequantize.cc
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
  TF_LITE_STATIC_MEMORY
  TF_LITE_MCU_DEBUG_LOG
  #PROJECT_GENERATION
  #CMSIS_NN
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${BASE_DIR}
  ${USR_DIR}/include
  ${RUY_DIR}
)
