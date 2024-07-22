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

#include "detectip_detectors_ipy_ch.hpp"
#include "detectip_detectors_iplocation_net.hpp"
#include "detectip_detectors_ipinfo_io.hpp"
#include "detectip_detectors_bigdatacloud.hpp"
#include "detectip_detectors_my_ip_io.hpp"
#include "detectip_detectors_ipify_org.hpp"
#include "detectip_detectors_jsonip_com.hpp"
#include "detectip_detectors_ip_api_com.hpp"
#include "detectip_detectors_seeip_org.hpp"

static std::vector<std::pair<std::string, std::string> > detectIPs() {
    using namespace DetectIP;
    using namespace DetectIP::Detectors;
    
    std::vector<std::pair<std::string, std::string> > ips;
    
    for (size_t i = 0; i < 9; i++) {
        std::shared_ptr<Detector> detector;
        switch (i) {
            case 0: detector = std::make_shared<IpyCh>(); break;
            case 1: detector = std::make_shared<IpLocationNet>(); break;
            case 2: detector = std::make_shared<IpInfoIo>(); break;
            case 3: detector = std::make_shared<BigDataCloud>(); break;
            case 4: detector = std::make_shared<IpifyOrg>(); break;
            case 5: detector = std::make_shared<MyIpIo>(); break;
            case 6: detector = std::make_shared<JsonIpCom>(); break;
            case 7: detector = std::make_shared<IpApiCom>(); break;
            case 8: detector = std::make_shared<SeeipOrg>(); break;
            default: continue;
        }
        try {
            ips.push_back(detector->detect());
        } catch (std::exception & exception) {
            std::flush(std::cerr) << "Exception: " << exception.what() << std::endl;
        }
    }
    
    return ips;
}

int main(int argc, char* argv[]) {
    auto ips = detectIPs();
    for (const auto & ip : ips) {
        if (!ip.first.empty()) {
            std::flush(std::cout) << "v4: " << ip.first.c_str() << " ";
        }
        if (!ip.second.empty()) {
            std::flush(std::cout) << "v6: " << ip.second.c_str() << " ";
        }
        std::flush(std::cout) << std::endl;
    }
    
    return 0;
}
