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
#include <ostream>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "detectip_detectors_dyndns_com.hpp"
#include "detectip_detectors_whatismyip_com.hpp"
#include "detectip_detectors_ipy_ch.hpp"
#include "detectip_detectors_iplocation_net.hpp"
#include "detectip_detectors_ipinfo_io.hpp"
#include "detectip_detectors_bigdatacloud.hpp"
#include "detectip_detectors_my_ip_io.hpp"
#include "detectip_detectors_ipify_org.hpp"
#include "detectip_detectors_jsonip_com.hpp"
#include "detectip_detectors_ip_api_com.hpp"
#include "detectip_detectors_seeip_org.hpp"
#include "detectip_config.hpp"

static std::vector<std::pair<std::string, std::string> > detectIPs(void) {
    
    std::vector<DetectIP::Detector::Result> allIPs;
    const auto config = std::make_shared<DetectIP::Config>();
    
    allIPs.reserve(10);
    for (size_t i = 0; i < 11; i++) {
        std::shared_ptr<DetectIP::Detector> detector;
        switch (i) {
            case 0: detector = std::make_shared<DetectIP::Detectors::DynDnsCom>(); break;
//            case 1: detector = std::make_shared<DetectIP::Detectors::WhatIsMyIpCom>(); break;
            case 2: detector = std::make_shared<DetectIP::Detectors::IpyCh>(); break;
            case 3: detector = std::make_shared<DetectIP::Detectors::IpLocationNet>(); break;
            case 4: detector = std::make_shared<DetectIP::Detectors::IpInfoIo>(); break;
            case 5: detector = std::make_shared<DetectIP::Detectors::BigDataCloud>(); break;
            case 6: detector = std::make_shared<DetectIP::Detectors::IpifyOrg>(); break;
            case 7: detector = std::make_shared<DetectIP::Detectors::MyIpIo>(); break;
            case 8: detector = std::make_shared<DetectIP::Detectors::JsonIpCom>(); break;
            case 9: detector = std::make_shared<DetectIP::Detectors::IpApiCom>(); break;
            case 10: detector = std::make_shared<DetectIP::Detectors::SeeipOrg>(); break;
            default: continue;
        }
        try {
            detector->setConfig(config);
            auto res = detector->detect();
            if (!res.first.empty() || !res.second.empty()) {
                allIPs.emplace_back(std::move(res));
            }
        } catch (std::exception & exception) {
            std::flush(std::cerr) << "Exception: " << exception.what() << std::endl;
        }
    }
    
    if (allIPs.empty()) {
        return std::vector<DetectIP::Detector::Result>();
    }
    
    std::sort(allIPs.begin(), allIPs.end(), [](const DetectIP::Detector::Result & a, const DetectIP::Detector::Result & b) {
        int av = a.first.empty() ? 0 : -10;
        int bv = b.first.empty() ? 0 : -10;
        av -= (a.second.empty() ? 0 : 1);
        bv -= (b.second.empty() ? 0 : 1);
        return (av < bv);
    });
    
    struct CompactResult final {
        std::string ipv4;
        std::string ipv6;
        int sortVal;
    };
    std::vector<CompactResult> compactResults;
    
    for (auto & ip : allIPs) {
        CompactResult * data = compactResults.data();
        bool processed = false;
        if (data) {
            for (size_t i = 0, n = compactResults.size(); (!processed && (i < n)); i++) {
                if ((data->ipv4 == ip.first) || (data->ipv6 == ip.second)) {
                    data->sortVal--;
                    if (data->ipv4.empty() && !ip.first.empty()) {
                        data->ipv4 = std::move(ip.first);
                    }
                    if (data->ipv6.empty() && !ip.second.empty()) {
                        data->ipv6 = std::move(ip.second);
                    }
                    processed = true;
                }
                data++;
            }
        }
        if (!processed) {
            CompactResult compRes;
            compRes.sortVal = -1;
            compRes.ipv4 = std::move(ip.first);
            compRes.ipv6 = std::move(ip.second);
            compactResults.emplace_back(std::move(compRes));
        }
    }
    allIPs.clear(); // Some data moved -> clear all
    
    if (compactResults.empty()) {
        return std::vector<DetectIP::Detector::Result>();
    }
    
    std::sort(compactResults.begin(), compactResults.end(), [](const CompactResult & a, const CompactResult & b) {
        return (a.sortVal < b.sortVal);
    });
    
    std::vector<DetectIP::Detector::Result> ips;
    ips.reserve(compactResults.size());
    
    for (auto & compRes : compactResults) {
        ips.emplace_back(std::move(compRes.ipv4), std::move(compRes.ipv6));
    }
    
    return ips;
}

int main(int argc, char* argv[]) {
    DetectIP::HTTPRequestable::globalInit();
    
    auto ips = detectIPs();
    for (const auto & ip : ips) {
        if (!ip.first.empty()) {
            std::flush(std::cout) << "v4: " << ip.first.c_str() << ", ";
        }
        if (!ip.second.empty()) {
            std::flush(std::cout) << "v6: " << ip.second.c_str() << " ";
        }
        std::flush(std::cout) << std::endl;
    }
    
    
    DetectIP::HTTPRequestable::globalDeinit();
    return EXIT_SUCCESS;
}
