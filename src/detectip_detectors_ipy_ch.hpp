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


#ifndef __DETECTIP_DETECTORS_IPY_CH_HPP__
#define __DETECTIP_DETECTORS_IPY_CH_HPP__ 1

#include <exception>

#include "detectip_curl_downloader.hpp"
#include "detectip_detector.hpp"
#include "detectip_rapid_json_parser.hpp"

namespace DetectIP {
namespace Detectors {
    
    class IpyCh final : public Detector, protected CURLDownloader, protected RapidJsonParser {
    public:
        /// IDetector
        virtual std::pair<std::string, std::string> detect() override final;
        
        IpyCh() = default;
        virtual ~IpyCh() noexcept = default;
    };
    
} // namespace Detectors
} // namespace DetectIP

#endif // !__DETECTIP_DETECTORS_IPY_CH_HPP__
