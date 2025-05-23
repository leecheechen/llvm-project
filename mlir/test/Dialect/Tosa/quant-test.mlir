// RUN: mlir-opt --tosa-test-quant-utils %s | FileCheck %s

// -----
// CHECK-LABEL: test_build_qtype
func.func @test_build_qtype(%arg0 : tensor<16x1x1x8x!quant.uniform<u8<1:255>:f32, 0.015680249780416489:128>>, %arg1: tensor<1xi8>, %arg2: tensor<1xi8>) -> tensor<16x1x1x8x!quant.uniform<u8<1:255>:f32, 0.015680249780416489:128>> {
  //  CHECK: tosa.negate
  %0 = "tosa.negate"(%arg0, %arg1, %arg2) : (tensor<16x1x1x8x!quant.uniform<u8<1:255>:f32, 0.015680249780416489:128>>, tensor<1xi8>, tensor<1xi8>) -> tensor<16x1x1x8x!quant.uniform<u8<1:255>:f32, 0.015680249780416489:128>>
  return %0 : tensor<16x1x1x8x!quant.uniform<u8<1:255>:f32, 0.015680249780416489:128>>
}

// -----
// CHECK-LABEL: test_build_mult_and_shift
func.func @test_build_mult_and_shift(%arg0: tensor<1x32x32x8x!quant.uniform<i8:f32, 0.015684768557548523>>, %arg1 : tensor<16x1x1x8x!quant.uniform<i8<-127:127>:f32, 0.015680249780416489>>, %arg2 : tensor<16xi32>) -> tensor<1x34x36x16x!quant.uniform<i32:f32, 0.078431375324726104>> {
  // CHECK: tosa.conv2d
  %input_zp = "tosa.const"() {values = dense<-1> : tensor<1xi8>} : () -> tensor<1xi8>
  %weight_zp = "tosa.const"() {values = dense<1> : tensor<1xi8>} : () -> tensor<1xi8>
  %0 = "tosa.conv2d"(%arg0, %arg1, %arg2, %input_zp, %weight_zp) {acc_type = i32, pad = array<i64: 1, 1, 2, 2>, dilation = array<i64: 2, 1>, stride = array<i64: 1, 1>} : (tensor<1x32x32x8x!quant.uniform<i8:f32, 0.015684768557548523>>, tensor<16x1x1x8x!quant.uniform<i8<-127:127>:f32, 0.015680249780416489>>, tensor<16xi32>, tensor<1xi8>, tensor<1xi8>) -> tensor<1x34x36x16x!quant.uniform<i32:f32, 0.078431375324726104>>
  return %0 : tensor<1x34x36x16x!quant.uniform<i32:f32, 0.078431375324726104>>

}
