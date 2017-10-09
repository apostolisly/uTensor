#ifndef UTENSOR_ARRAY_TESTS
#define UTENSOR_ARRAY_TESTS

#include "ArrayOps.hpp"
#include "test.hpp"
#include "tensorIdxImporter.hpp"

class ArrayOpsTest : public Test {
public:
    void quantize_v2Test(void) {
        testStart("quantize_v2");
        TensorIdxImporter t_import;
        
        //reference inputs  /Users/neitan01/Documents/mbed/uTensor.git/TESTS/scripts/PRE-GEN/qA
        Tensor<float> a = t_import.float_import ("/fs/testData/qA/in/Cast_0.idx");
        Tensor<float> a_min = t_import.float_import("/fs/testData/qA/in/Min_0.idx");
        Tensor<float> a_max = t_import.float_import("/fs/testData/qA/in/Max_0.idx");

        //reference outputs
        Tensor<unsigned char> a_q_ref = t_import.ubyte_import("/fs/testData/qA/out/qA_0.idx");
        Tensor<float> a_min_q_ref = t_import.float_import("/fs/testData/qA/out/qA_1.idx");
        Tensor<float> a_max_q_ref = t_import.float_import("/fs/testData/qA/out/qA_2.idx");

        //Implementation goes here

        //modify the checks below:
        Tensor<unsigned char> a_q(a_q_ref.getShape());
        Tensor<float> a_min_q(a_min_q_ref.getShape());
        Tensor<float> a_max_q(a_max_q_ref.getShape());

        double result = meanPercentErr(a_q_ref, a_q) + meanPercentErr(a_min_q_ref, a_min_q) + meanPercentErr(a_max_q_ref, a_max_q);
        //passed(result < 0.0001);
        passed(result == 0);
    }

    void dequantizeTest(void) {
        testStart("dequantize");
        TensorIdxImporter t_import;

        //reference inputs
        Tensor<unsigned char> a = t_import.ubyte_import("/fs/testData/deQ/in/rQ_0.idx");
        Tensor<float> a_min = t_import.float_import("/fs/testData/deQ/in/rQ_1.idx");
        Tensor<float> a_max = t_import.float_import("/fs/testData/deQ/in/rQ_2.idx");

        //reference outputs
        Tensor<float> out_ref = t_import.float_import("/fs/testData/deQ/out/deQ_0.idx");

        //modify the checks below:
        Tensor<float> out(out_ref.getShape());

        double result = meanPercentErr(out_ref, out);
        //passed(result < 0.0001);
        passed(result == 0);
    }

    void reshapeTest(void) {
        testStart("reshape");
        TensorIdxImporter t_import;

        //reference inputs
        Tensor<float> ref_a = t_import.float_import("/fs/testData/ref_reshape/in/Const_0.idx");
        Tensor<int> ref_dim = t_import.int_import("/fs/testData/ref_reshape/in/Const_1_0.idx");

        //reference outputs
        Tensor<float> out_ref = t_import.float_import("/fs/testData/ref_reshape/out/ref_reshape_0.idx");

        //modify the checks below:
        Tensor<float> out(out_ref.getShape());

        double result = meanPercentErr(out_ref, out);
        //passed(result < 0.0001);
        passed(result == 0);
    }

    void runAll(void) {
        quantize_v2Test();
        dequantizeTest();
        reshapeTest();
    }
};


#endif //UTENSOR_ARRAY_TESTS