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


#include <sstream>
#include <memory>
#include <ctype.h>

#include "detectip_detectors_dyndns_com.hpp"

namespace DetectIP {
namespace Detectors {
    
    Detector::Result DynDnsCom::detect() {
        Detector::Result ips;
        
        const auto config = this->config();
        if (!config) {
            throw std::runtime_error("No config");
        }
        
        {
            auto response = GET(config->get("k", "a").c_str());
            response.push_back(0);
            const char * cStr = reinterpret_cast<const char *>(response.data());
            while (*cStr) {
                if (::isdigit(*cStr) != 0) {
                    int i0 = -1, i1 = -1, i2 = -1, i3 = -1;
                    if (::sscanf(cStr, "%i.%i.%i.%i", &i0, &i1, &i2, &i3) == 4) {
                        if ((i0 >= 0) && (i0 < 256) && (i1 >= 0) && (i1 < 256) &&
                            (i2 >= 0) && (i2 < 256) && (i3 >= 0) && (i3 < 256)) {
                            char buff[128] = { 0 };
                            snprintf(buff, 128, "%i.%i.%i.%i", i0, i1, i2, i3);
                            auto str = validateIPv4(buff);
                            if (!str.empty()) {
                                ips.first = std::move(str);
                                break;
                            }
                        }
                    }
                }
                cStr++;
            }
        }
        
        return ips;
    }
    
} // namespace Detectors
} // namespace DetectIP
