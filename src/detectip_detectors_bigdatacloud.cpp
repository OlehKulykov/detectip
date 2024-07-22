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


#include <memory>
#include <strings.h>

#include "detectip_detectors_bigdatacloud.hpp"

namespace DetectIP {
namespace Detectors {
    
    std::pair<std::string, std::string> BigDataCloud::detect() {
        std::pair<std::string, std::string> ips;
        
        for (size_t i = 0; i < 2; i++) {
            const auto response = get(i ? "https://api-bdc.net/data/client-ip" : "https://api.bigdatacloud.net/data/client-ip");
            const auto doc = parseJson(response);
            const auto ipIt = doc->FindMember("ipString");
            const auto typeIt = doc->FindMember("ipType");
            const char * typeStr = typeIt->value.IsString() ? typeIt->value.GetString() : "";
            if (!typeStr) {
                typeStr = "";
            }
            if (i) {
                if (::strcasecmp(typeStr, "ipv6") == 0) {
                    ips.second = validateIPv6(ipIt->value.IsString() ? ipIt->value.GetString() : nullptr);
                }
            } else if (::strcasecmp(typeStr, "ipv4") == 0) {
                ips.first = validateIPv4(ipIt->value.IsString() ? ipIt->value.GetString() : nullptr);
            }
        }
        
        return ips;
    }
    
} // namespace Detectors
} // namespace DetectIP
