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


#include <string>

#include "detectip_detector.hpp"

#include <arpa/inet.h>

namespace DetectIP {

    std::string Detector::validateIPv4(const char * ipv4) {
        if (ipv4) {
            struct in_addr result = { 0 };
            if (::inet_pton(AF_INET, ipv4, &result) == 1) {
                return std::string(ipv4);
            }
        }
        return std::string();
    }
    
    std::string Detector::validateIPv6(const char * ipv6) {
        if (ipv6) {
            struct in6_addr result = { 0 };
            if (::inet_pton(AF_INET6, ipv6, &result) == 1) {
                std::string s(ipv6);
                std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){
                    return std::tolower(c);
                });
                return s;
            }
        }
        return std::string();
    }
    
} // namespace DetectIP

