/***************************************************************************************************

  Zyan Disassembler Library (Zydis)

  Original Author : Florian Bernd

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.

***************************************************************************************************/

/**
 * @file
 * @brief   Defines the immutable and storage-efficient `ZydisShortString` struct, which is used to
 *          store strings in the generated tables.
 */

#ifndef ZYDIS_SHORTSTRING_H
#define ZYDIS_SHORTSTRING_H

#include "../ZydisExportConfig.h"
#include "../Zycore/Defines.h"
#include "../Zycore/Types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/* Enums and types                                                                                */
/* ============================================================================================== */

#pragma pack(push, 1)

/**
 * @brief   Defines the `ZydisShortString` struct.
 *
 * This compact struct is mainly used for internal string-tables to save up some bytes.
 *
 * All fields in this struct should be considered as "private". Any changes may lead to unexpected
 * behavior.
 */
typedef struct ZydisShortString_
{
    /**
     * @brief   The buffer that contains the actual (null-terminated) string.
    */
    const char* data;
    /**
     * @brief   The length (number of characters) of the string (without 0-termination).
    */
    ZyanU8 size;
} ZydisShortString;

#pragma pack(pop)

/* ============================================================================================== */
/* Macros                                                                                         */
/* ============================================================================================== */

/**
 * @brief   Declares a `ZydisShortString` from a static C-style string.
 *
 * @param   string  The C-string constant.
 */
#define ZYDIS_MAKE_SHORTSTRING(string) \
    { string, sizeof(string) - 1 }

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_SHORTSTRING_H */
