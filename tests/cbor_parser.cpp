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
    TEST(DeployUI, TTL) {
        uint64_t minute = 60;
        uint64_t hour = 60 * minute;
        uint64_t day = 24 * hour;
        uint64_t week = 7*day;

        char buffer[100];
        auto err = parse_TTL(minute, buffer, sizeof(buffer));
        EXPECT_EQ(err, parser_ok);
        EXPECT_STREQ(buffer, "1m");

        err = parse_TTL(minute + 20, buffer, sizeof(buffer));
        EXPECT_EQ(err, parser_ok);
        EXPECT_STREQ(buffer, "1m 20s");

        err = parse_TTL(hour + minute + 20, buffer, sizeof(buffer));
        EXPECT_EQ(err, parser_ok);
        EXPECT_STREQ(buffer, "1h 1m 20s");

        err = parse_TTL(day, buffer, sizeof(buffer));
        EXPECT_EQ(err, parser_ok);
        EXPECT_STREQ(buffer, "1day");

        err = parse_TTL(day + hour + minute + 20, buffer, sizeof(buffer));
        EXPECT_EQ(err, parser_ok);
        EXPECT_STREQ(buffer, "1day 1h 1m 20s");

        err = parse_TTL(week + day + hour + minute + 20, buffer, sizeof(buffer));
        EXPECT_EQ(err, parser_ok);
        EXPECT_STREQ(buffer, "8days 1h 1m 20s");

    }

    TEST(DeployGen, tokentransfer) {
        uint8_t inBuffer[1000];
        const char *tmp = "017f747b67bd3fe63c2a736739dfe40156d622347346e70f68f51c178a75ce5537a087c0377901000040771b000000000002000000000000006bcc398e392003d4b8f76c522d2c348a802b0833f0a730ae25ecba7277f88097020000000f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f1010101010101010101010101010101010101010101010101010101010101010070000006d61696e6e65741ecf7adc0c92e68526e190bc2e678ee4d0a594acdffe16b3f845d44b1013b12a00000000000100000006000000616d6f756e74050000000400ca9a3b08050400000006000000616d6f756e74010000000008020000006964090000000100000000000000000d0506000000736f7572636522000000010202020202020202020202020202020202020202020202020202020202020202010d0c06000000746172676574210000002121212121212121212121212121212121212121212121212121212121212121070c01000000017f747b67bd3fe63c2a736739dfe40156d622347346e70f68f51c178a75ce5537019dd5966a72ede22e2e28a4b6c500ee12e561961a5a9ba7c8debd1d20d9c54ef7c74203a614aeafaa35ed0ac0eba737ddeae24cd26ee3fbf16e4d09c705fed308";

        auto inBufferLen = parseHexString(inBuffer, sizeof(inBuffer), tmp);

        parser_context_t ctx;
        auto err = parser_parse(&ctx, inBuffer, inBufferLen);
        EXPECT_EQ(err, parser_ok);

        err = parser_validate(&ctx);
        EXPECT_EQ(err, parser_ok);

    }

    TEST(DeployGen, delegate_byhashpayment) {
        uint8_t inBuffer[1000];
        const char *tmp = "02031b84c5567b126440995d3ed5aaba0565d71e1834604819ff9c17f5e9d5dd078fa087c0377901000080ee3600000000000200000000000000a214f01a236e5793eef21efe8bdb0f9ec7b95f20d0d4c149e9fc8a58d21647c303000000000000000000000000000000000000000000000000000000000000000000000001010101010101010101010101010101010101010101010101010101010101010202020202020202020202020202020202020202020202020202020202020202070000006d61696e6e65741014d6a144218d679dd2509953f567ad2d0d6952713a9226fd3a6499a9d6167e00000000000100000006000000616d6f756e74050000000400ca9a3b080101010101010101010101010101010101010101010101010101010101010101010800000064656c6567617465030000000900000064656c656761746f7221000000010101010101010101010101010101010101010101010101010101010101010101160900000076616c696461746f72210000000103030303030303030303030303030303030303030303030303030303030303031606000000616d6f756e740100000000080300000002031b84c5567b126440995d3ed5aaba0565d71e1834604819ff9c17f5e9d5dd078f02611d93753628c649c117c1ed9672666aa63ed063ee44579da2e6ff58a8a82f6e24c3fce56b91097aba9e1600d8ee61064a3362ae3a0a32ccd3d6acba0339f0cc013b6a27bcceb6a42d62a3a8d02a6f0d73653215771de243a63ac048a18b59da290150ea6e6a305a3ca68001ccecb8637bbbb6e4ffaae2fb52abcb86c09ec6e3044e23d3c7ff11b076ba6a69a46b9d7b53d435db3e3b872c8541b10b6ac5f790f208018139770ea87d175f56a35466c34c7ecccb8d8a91b4ee37a25df60f5b8fc9b394015f3e4c89498e6f00cfe847b6cfe4ee96038aeb3b66f212afe548fe62a0820eaf3e9e0709fbf44a4f3686538ce40c418f474bdcdd707cb8c1829c71336f872506";

        auto inBufferLen = parseHexString(inBuffer, sizeof(inBuffer), tmp);

        parser_context_t ctx;
        auto err = parser_parse(&ctx, inBuffer, inBufferLen);
        EXPECT_EQ(err, parser_ok);

        err = parser_validate(&ctx);
        EXPECT_EQ(err, parser_ok);

    }

    TEST(DeployGen, delegate_namepayment) {
        uint8_t inBuffer[5000];
        const char *tmp = "02031b84c5567b126440995d3ed5aaba0565d71e1834604819ff9c17f5e9d5dd078fa087c03779010000005c26050000000002000000000000000c71f546447d76240f6cb6a67e0c1d6bd327655734a7afcceefb2ecb6e97a29e0a0000000000000000000000000000000000000000000000000000000000000000000000010101010101010101010101010101010101010101010101010101010101010102020202020202020202020202020202020202020202020202020202020202020303030303030303030303030303030303030303030303030303030303030303040404040404040404040404040404040404040404040404040404040404040405050505050505050505050505050505050505050505050505050505050505050606060606060606060606060606060606060606060606060606060606060606070707070707070707070707070707070707070707070707070707070707070708080808080808080808080808080808080808080808080808080808080808080909090909090909090909090909090909090909090909090909090909090909070000006d61696e6e65745a098ca97f9a7795e24ddf5e3f190e6350de05db1bf494ca4cf5ed4e20f3af5700000000000100000006000000616d6f756e74050000000400ca9a3b08041100000064656c65676174652d636f6e747261637401010000000800000064656c6567617465030000000900000064656c656761746f7221000000010101010101010101010101010101010101010101010101010101010101010101160900000076616c696461746f72210000000103030303030303030303030303030303030303030303030303030303030303031606000000616d6f756e740100000000080a00000002031b84c5567b126440995d3ed5aaba0565d71e1834604819ff9c17f5e9d5dd078f0280b42cb4b78da7c36da0e50f01861e45550d2df84bf19413435378663832b0052c082810636e73ea311f16e3be205f3541e08f419cae766c577ed4d649160a94020362c0a046dacce86ddd0343c6d3c7c79c2208ba0d9c9cf24a6d046d21d21f90f702ce3719df403212396509bd8722c3a40083ff029478ab173b20000f9f10362be71b8e9f9b0bb40fbf41d3c8b5d87f06e94da7b4a690778269e49a6ba85ee2f84e013b6a27bcceb6a42d62a3a8d02a6f0d73653215771de243a63ac048a18b59da290132feb699d5058973d6b09f6a84fc4640b46d02d6242d6f7b7081161bf33a36dc6ec5b2910ae760c088120fa32753328465fff65689698e290ea63fee76d67a0c011398f62c6d1a457c51ba6a4b5f3dbd2f69fca93216218dc8997e416bd17d93ca011ad5d44821c56ad73c499706bd5c5770f8c90e26f5cc6466e986786a5767e0be1052f4409658791c07c2b998c73526067966d1fc72d2c7f73637e798fbdd7b000202531fe6068134503d2723133227c867ac8fa6c83c537e9a44c3c5bdbdcb1fe33702bce6eaa2187c98271ea94191aa633706e872a76b12794bdd0251027948b18c6329332da3f0671fffe66410822cf38366f7ba12b8c0559b9014b1a015a61d99be0202989c0b76cb563971fdc9bef31ec06c3560f3249d6ee9e5d83c57625596e05f6f02b66e2abd39db0e85a3675972a7d6867b0e76f3131c86e4cb8ac25481b22e8a9c036721b3e242e209b21df93d80c47ba63e71acf0612572d0d4b520e507af2848020256b328b30c8bf5839e24058747879408bdb36241dc9c2e7c619faa12b292096702f64eccc9ec9ba12f6b1125f9bd6b060dd01a86a44d3b4d79d75e7ccf9194ee6a77e9239caaadec021c643c5173201c2dd3c0aacee115d64857597080985024e4018139770ea87d175f56a35466c34c7ecccb8d8a91b4ee37a25df60f5b8fc9b394015fb552cd057bf53c76cc11a4cb2489df85fec890faf1904aa24f0c03be0230cf74988b99f14a459685935bcaa02717ee9dfec871a650da61a0798edefed25801018a875fff1eb38451577acd5afee405456568dd7c89e090863a0557bc7af49f1701c49311e23fefafaec6769043bc5b7ad656ac9941c17f00bea6799143255e427d741c54a0d87e621574d785960d4f64fb7c5701b39dc904460c36c66ba68d4f0c01ca93ac1705187071d67b83c7ff0efe8108e8ec4530575d7726879333dbdabe7c01379d48c3a702490bfb32b5e64a934ee33ba53ab9dcbb34f24583cbab6d44a9d91f5279650375205b15fc3a0fa247ee0c1bed0ef6d034cd0f2ccadcd6ad4e240f";

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
