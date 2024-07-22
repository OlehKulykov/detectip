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


#ifndef __DETECTIP_DETECTOR_HPP__
#define __DETECTIP_DETECTOR_HPP__ 1

#include <string>

namespace DetectIP {
    
    class Detector {
    protected:
        std::string validateIPv4(const char * ipv4);
        std::string validateIPv6(const char * ipv6);
        std::pair<std::string, std::string>validate(const char * ipv4, const char * ipv6 = nullptr) {
            return std::pair<std::string, std::string>(validateIPv4(ipv4), validateIPv6(ipv6));
        }
        
    public:
        virtual std::pair<std::string, std::string> detect() = 0;
        
        virtual ~Detector() noexcept = default;
    };
    
} // namespace DetectIP

#endif // !__DETECTIP_DETECTOR_HPP__
