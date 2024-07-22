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

#include "detectip_detectors_jsonip_com.hpp"

namespace DetectIP {
namespace Detectors {
    
    std::pair<std::string, std::string> JsonIpCom::detect() {
        std::pair<std::string, std::string> ips;
        
        for (size_t i = 0; i < 2; i++) {
            const auto response = get(i ? "https://jsonip.com" : "https://ipv4.jsonip.com");
            const auto doc = parseJson(response);
            const auto ipIt = doc->FindMember("ip");
            if (i) {
                ips.second = validateIPv6(ipIt->value.IsString() ? ipIt->value.GetString() : nullptr);
            } else {
                ips.first = validateIPv4(ipIt->value.IsString() ? ipIt->value.GetString() : nullptr);
            }
        }
        
        return ips;
    }
    
} // namespace Detectors
} // namespace DetectIP
