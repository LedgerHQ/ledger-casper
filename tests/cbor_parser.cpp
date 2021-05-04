/*******************************************************************************
*   (c) 2019 Zondax GmbH
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
********************************************************************************/

#include "gtest/gtest.h"
#include <string>
#include <cbor.h>
#include <hexutils.h>
#include <zxmacros.h>
#include "parser.h"

// Basic CBOR test cases generated with http://cbor.me/

namespace {
    TEST(DeployParserTest, MinimalListTest) {
        uint8_t inBuffer[1000];
        const char *tmp = "02030f0fb9a244ad31a369ee02b7abfbbb0bfa3812b9a39ed93346d03d67d412d1774cbaf9747501000080ee36000000000001000000000000004811966d37fe5674a8af4001884ea0d9042d1c06668da0c963769c3a01ebd08f0100000001010101010101010101010101010101010101010101010101010101010101010e0000006361737065722d6578616d706c657725c391ccf5053bbe48b6a99843ceef4b342e72cc1daf195d1bcfa8d805f0d8020e0000006361737065722d6578616d706c65130000006578616d706c652d656e7472792d706f696e7401000000080000007175616e7469747904000000e803000001050100000006000000616d6f756e7404000000e8030000010100000002030f0fb9a244ad31a369ee02b7abfbbb0bfa3812b9a39ed93346d03d67d412d177012dbf03817a51794a8e19e0724884075e6d1fbec326b766ecfa6658b41f81290da85e23b24e88b1c8d9761185c961daee1adab0649912a6477bcd2e69bd91bd08";

        auto inBufferLen = parseHexString(inBuffer, sizeof(inBuffer), tmp);

        parser_context_t ctx;
        auto err = parser_parse(&ctx, inBuffer, inBufferLen);
        EXPECT_EQ(err, parser_ok);

        err = parser_validate(&ctx);
        EXPECT_EQ(err, parser_ok);

    }

    TEST(CLTypeTests, Array) {
        uint8_t inBuffer[1000];
        const char *tmp = "01d9bf2148748a85c89da5aad8ee0b0fc2d105fd39d41a4c796536354f0ae2900ca856a4d37501000080ee36000000000001000000000000009ee5ec4efe8d2d1eceb5ddb16711dc8be6d1a371c3b62119b868d8b2e8c5cf500100000001010101010101010101010101010101010101010101010101010101010101010e0000006361737065722d6578616d706c65043b7a3e19791d4315b514c068111ad021bdee997b11228914d5650b87b228ba020e0000006361737065722d6578616d706c65130000006578616d706c652d656e7472792d706f696e7401000000080000007175616e7469747904000000e803000001050100000004000000746573740a0000000a0a0a0a0a0a0a0a0a0a0f0a00000000000000";

        auto inBufferLen = parseHexString(inBuffer, sizeof(inBuffer), tmp);

        parser_context_t ctx;
        auto err = parser_parse(&ctx, inBuffer, inBufferLen);
        EXPECT_EQ(err, parser_ok);

        err = parser_validate(&ctx);
        EXPECT_EQ(err, parser_ok);
    }


    TEST(DeployParserTest, ContractByHash) {
        uint8_t inBuffer[1000];
        const char *tmp = "02030f0fb9a244ad31a369ee02b7abfbbb0bfa3812b9a39ed93346d03d67d412d1774cbaf9747501000080ee36000000000001000000000000005ecf9b7c916e59d106dc0f205fe8ade59c26bd321c5e90b44c970fd30402a2930100000001010101010101010101010101010101010101010101010101010101010101010e0000006361737065722d6578616d706c655dd440a64c305581ecf8f4dfaee0ed538817a0bdf2857a4ed6a6f4530ef14488010f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f130000006578616d706c652d656e7472792d706f696e7401000000080000007175616e7469747904000000e803000001050100000006000000616d6f756e7404000000e8030000010100000002030f0fb9a244ad31a369ee02b7abfbbb0bfa3812b9a39ed93346d03d67d412d177012dbf03817a51794a8e19e0724884075e6d1fbec326b766ecfa6658b41f81290da85e23b24e88b1c8d9761185c961daee1adab0649912a6477bcd2e69bd91bd08";

        auto inBufferLen = parseHexString(inBuffer, sizeof(inBuffer), tmp);

        parser_context_t ctx;
        auto err = parser_parse(&ctx, inBuffer, inBufferLen);
        EXPECT_EQ(err, parser_ok);

        err = parser_validate(&ctx);
        EXPECT_EQ(err, parser_ok);

    }

    TEST(DeployParserTest, ContractVersionedByHash) {
        uint8_t inBuffer[1000];
        const char *tmp = "02030f0fb9a244ad31a369ee02b7abfbbb0bfa3812b9a39ed93346d03d67d412d1774cbaf9747501000080ee3600000000000100000000000000e159c9ed050bdc2600b070d7a29e436ee53e62896ef830473cf1a669bc8b16440100000001010101010101010101010101010101010101010101010101010101010101010e0000006361737065722d6578616d706c65141722ad47b6c586e2e03825e4e0e2190f107321e9cca3d8bd692b5f8f11a984020e0000006361737065722d6578616d706c65130000006578616d706c652d656e7472792d706f696e7401000000080000007175616e7469747904000000e803000001030f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0190340000070000006578616d706c650100000006000000616d6f756e7404000000e8030000010100000002030f0fb9a244ad31a369ee02b7abfbbb0bfa3812b9a39ed93346d03d67d412d177012dbf03817a51794a8e19e0724884075e6d1fbec326b766ecfa6658b41f81290da85e23b24e88b1c8d9761185c961daee1adab0649912a6477bcd2e69bd91bd08";

        auto inBufferLen = parseHexString(inBuffer, sizeof(inBuffer), tmp);

        parser_context_t ctx;
        auto err = parser_parse(&ctx, inBuffer, inBufferLen);
        EXPECT_EQ(err, parser_ok);

        err = parser_validate(&ctx);
        EXPECT_EQ(err, parser_ok);

    }

    TEST(DeployParserTest, ContractVersionedByName) {
        uint8_t inBuffer[1000];
        const char *tmp = "02030f0fb9a244ad31a369ee02b7abfbbb0bfa3812b9a39ed93346d03d67d412d1774cbaf9747501000080ee36000000000001000000000000001cd0229f526223ed6cf64b2559962f65fad578bbf81d1ecbb38d74dc03f9701e0100000001010101010101010101010101010101010101010101010101010101010101010e0000006361737065722d6578616d706c652be8ca5bfe306b6f83b519dc8671b11cb71fa5cc7b6f09c4eac1be41bbf5e7e9020e0000006361737065722d6578616d706c65130000006578616d706c652d656e7472792d706f696e7401000000080000007175616e7469747904000000e803000001040e0000006361737065722d6578616d706c650190340000070000006578616d706c650100000006000000616d6f756e7404000000e8030000010100000002030f0fb9a244ad31a369ee02b7abfbbb0bfa3812b9a39ed93346d03d67d412d177012dbf03817a51794a8e19e0724884075e6d1fbec326b766ecfa6658b41f81290da85e23b24e88b1c8d9761185c961daee1adab0649912a6477bcd2e69bd91bd08";

        auto inBufferLen = parseHexString(inBuffer, sizeof(inBuffer), tmp);

        parser_context_t ctx;
        auto err = parser_parse(&ctx, inBuffer, inBufferLen);
        EXPECT_EQ(err, parser_ok);

        err = parser_validate(&ctx);
        EXPECT_EQ(err, parser_ok);

    }

    TEST(DeployParserTest, ContractVersionedByHash_versionNone) {
        uint8_t inBuffer[1000];
        const char *tmp = "01d9bf2148748a85c89da5aad8ee0b0fc2d105fd39d41a4c796536354f0ae2900ca856a4d37501000080ee3600000000000100000000000000407c289687246eba34843a500603178764ac0e18247d7a11ff1770b00174663c0100000001010101010101010101010101010101010101010101010101010101010101010e0000006361737065722d6578616d706c6533f21d563daac1ebe6fccd3b1a96d3460495e54fb7ba470eb51d8606c6d5a6ce020e0000006361737065722d6578616d706c65130000006578616d706c652d656e7472792d706f696e7401000000080000007175616e7469747904000000e803000001050100000006000000616d6f756e740400000018fcffff010200000001d9bf2148748a85c89da5aad8ee0b0fc2d105fd39d41a4c796536354f0ae2900c01b47e4b8ccc377c300909ac2f6ab286371de4ac62325d92643af82292692ccb994e3c726d020d4179aaaef59fec3eb7d4b59fcf6c9540d8cb529ceac823534c0902026a04ab98d9e4774ad806e302dddeb63bea16b5cb5f223ee77478e861bb583eb302494565e2e1e38eca1fb56fbc29fc32bb9ee30c0a7b1d9bb5004df4ce9fa715ac6c498c07cfbcf535f03f6837f2e5e4d2075d32ebefb7bc0dba214c2162e486c2";

        auto inBufferLen = parseHexString(inBuffer, sizeof(inBuffer), tmp);

        parser_context_t ctx;
        auto err = parser_parse(&ctx, inBuffer, inBufferLen);
        EXPECT_EQ(err, parser_ok);

        err = parser_validate(&ctx);
        EXPECT_EQ(err, parser_ok);

    }

    TEST(CBORParserTest, MinimalListTest) {
        // [1,2,3]
        uint8_t inBuffer[100];
        const char *tmp = "83010203";
        auto inBufferLen = parseHexString(inBuffer, sizeof(inBuffer), tmp);

        CborParser parser;
        CborValue it;
        CborError err;

        err = cbor_parser_init(inBuffer, inBufferLen, 0, &parser, &it);
        EXPECT_EQ(err, CborNoError);
        size_t arrLen;
        err = cbor_value_get_array_length(&it, &arrLen);
        EXPECT_EQ(err, CborNoError);
        EXPECT_EQ(arrLen, 3);

        // Manually iterate
        EXPECT_FALSE(cbor_value_at_end(&it));

        CborType type = cbor_value_get_type(&it);
        EXPECT_EQ(type, CborArrayType);
        EXPECT_TRUE(cbor_value_is_container(&it));

        /// Enter container and iterate along items
        CborValue contents;
        err = cbor_value_enter_container(&it, &contents);
        EXPECT_EQ(err, CborNoError);

        int64_t val;
        // item = 1
        type = cbor_value_get_type(&contents);
        EXPECT_EQ(type, CborIntegerType);
        err = cbor_value_get_int64(&contents, &val);
        EXPECT_EQ(err, CborNoError);
        EXPECT_EQ(val, 1);
        err = cbor_value_advance_fixed(&contents);
        EXPECT_EQ(err, CborNoError);

        // item = 2
        type = cbor_value_get_type(&contents);
        EXPECT_EQ(type, CborIntegerType);
        err = cbor_value_get_int64(&contents, &val);
        EXPECT_EQ(err, CborNoError);
        EXPECT_EQ(val, 2);
        err = cbor_value_advance_fixed(&contents);
        EXPECT_EQ(err, CborNoError);

        // item = 3
        type = cbor_value_get_type(&contents);
        EXPECT_EQ(type, CborIntegerType);
        err = cbor_value_get_int64(&contents, &val);
        EXPECT_EQ(err, CborNoError);
        EXPECT_EQ(val, 3);
        err = cbor_value_advance_fixed(&contents);
        EXPECT_EQ(err, CborNoError);

        // Close container
        err = cbor_value_leave_container(&it, &contents);
        EXPECT_EQ(err, CborNoError);
    }

    TEST(CBORParserTest, MinimalDictTest) {
        // { "x" : 1, "y" : 2, "z" : "test" }
        uint8_t inBuffer[100];
        const char *tmp = "A3617801617902617A6474657374";
        auto inBufferLen = parseHexString(inBuffer, sizeof(inBuffer), tmp);

        CborParser parser;
        CborValue it;
        CborError err = cbor_parser_init(inBuffer, inBufferLen, 0, &parser, &it);
        EXPECT_EQ(err, CborNoError);

        // Manually iterate
        EXPECT_FALSE(cbor_value_at_end(&it));

        CborType type = cbor_value_get_type(&it);
        EXPECT_EQ(type, CborMapType);
        EXPECT_TRUE(cbor_value_is_container(&it));
        size_t mapLen;
        err = cbor_value_get_map_length(&it, &mapLen);
        EXPECT_EQ(err, CborNoError);
        EXPECT_EQ(mapLen, 3);

        /// Enter container and iterate along items
        CborValue contents;
        err = cbor_value_enter_container(&it, &contents);
        EXPECT_EQ(err, CborNoError);

        size_t key_len;
        uint64_t val;
        char buffer[100];
        MEMZERO(buffer, 100);

        // "x":1  key
        type = cbor_value_get_type(&contents);
        EXPECT_EQ(type, CborTextStringType);
        key_len = sizeof(buffer);
        err = _cbor_value_copy_string(&contents, buffer, &key_len, nullptr);
        EXPECT_EQ(err, CborNoError);
        EXPECT_EQ(key_len, 1);
        EXPECT_EQ(strlen((const char *) buffer), 1);
        EXPECT_STREQ(buffer, "x");
        err = cbor_value_advance(&contents);         // easier than advance_fixed, performance hit is small
        EXPECT_EQ(err, CborNoError);

        // "x":1  value
        type = cbor_value_get_type(&contents);
        EXPECT_EQ(type, CborIntegerType);
        err = cbor_value_get_uint64(&contents, &val);
        EXPECT_EQ(err, CborNoError);
        EXPECT_EQ(val, 1);
        err = cbor_value_advance(&contents);         // easier than advance_fixed, performance hit is small
        EXPECT_EQ(err, CborNoError);

        // "y":2  key
        type = cbor_value_get_type(&contents);
        EXPECT_EQ(type, CborTextStringType);
        EXPECT_EQ(err, CborNoError);
        key_len = sizeof(buffer);
        err = _cbor_value_copy_string(&contents, buffer, &key_len, nullptr);
        EXPECT_EQ(err, CborNoError);
        EXPECT_EQ(key_len, 1);
        EXPECT_EQ(strlen((const char *) buffer), 1);
        EXPECT_STREQ(buffer, "y");
        err = cbor_value_advance(&contents);         // easier than advance_fixed, performance hit is small
        EXPECT_EQ(err, CborNoError);

        // "y":2  value
        type = cbor_value_get_type(&contents);
        EXPECT_EQ(type, CborIntegerType);
        err = cbor_value_get_uint64(&contents, &val);
        EXPECT_EQ(err, CborNoError);
        EXPECT_EQ(val, 2);
        err = cbor_value_advance(&contents);         // easier than advance_fixed, performance hit is small
        EXPECT_EQ(err, CborNoError);

        // "z":"test"  key
        type = cbor_value_get_type(&contents);
        EXPECT_EQ(type, CborTextStringType);
        EXPECT_EQ(err, CborNoError);
        key_len = sizeof(buffer);
        err = _cbor_value_copy_string(&contents, buffer, &key_len, nullptr);
        EXPECT_EQ(err, CborNoError);
        EXPECT_EQ(key_len, 1);
        EXPECT_EQ(strlen((const char *) buffer), 1);
        EXPECT_STREQ(buffer, "z");
        err = cbor_value_advance(&contents);         // easier than advance_fixed, performance hit is small
        EXPECT_EQ(err, CborNoError);

        // "z":"test"  value
        type = cbor_value_get_type(&contents);
        EXPECT_EQ(type, CborTextStringType);
        EXPECT_EQ(err, CborNoError);
        key_len = sizeof(buffer);
        err = _cbor_value_copy_string(&contents, buffer, &key_len, nullptr);
        EXPECT_EQ(err, CborNoError);
        EXPECT_EQ(key_len, 4);
        EXPECT_EQ(strlen((const char *) buffer), 4);
        EXPECT_STREQ(buffer, "test");
        err = cbor_value_advance(&contents);         // easier than advance_fixed, performance hit is small
        EXPECT_EQ(err, CborNoError);

        // Close container
        err = cbor_value_leave_container(&it, &contents);
        EXPECT_EQ(err, CborNoError);
    }
}
