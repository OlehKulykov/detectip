// MIT License
//
// Copyright (c) 2024 Oleh Kulykov
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#ifndef __DETECTIP_RAPIDJSON_HPP__
#define __DETECTIP_RAPIDJSON_HPP__ 1

#include <sstream>
#include <ostream>
#include <climits>
#include <exception>
#include <cstddef>
#include <memory>
#include <vector>
#include <string>

#define RAPIDJSON_NAMESPACE DetectIPRJ
#define RAPIDJSON_NO_SIZETYPEDEFINE 1
#define RAPIDJSON_HAS_STDSTRING 1

#if defined(__SSE4_2__)
#define RAPIDJSON_SSE42 1
#elif defined(__SSE2__)
#define RAPIDJSON_SSE2 1
#endif

namespace DetectIPRJ {
    
    typedef size_t SizeType;
    
} // namespace DetectIPRJ

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/allocators.h"
#include "rapidjson/encodings.h"

#include "rapidjson/reader.h"
#include "rapidjson/stream.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/schema.h"

namespace DetectIP {
    
    typedef DetectIPRJ::GenericDocument<DetectIPRJ::UTF8<>, DetectIPRJ::CrtAllocator> RJDocument;
    typedef DetectIPRJ::GenericValue<DetectIPRJ::UTF8<>, DetectIPRJ::CrtAllocator> RJValue;
    
} // namespace DetectIP

#endif // !__DETECTIP_RAPIDJSON_HPP__
