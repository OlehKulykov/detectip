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
#include <sstream>

#include "detectip_curl_downloader.hpp"
#include <curl/curl.h>

namespace DetectIP {
    
    size_t CURLDownloader::writeCallback(char * contents, size_t size, size_t nmemb, void * userp) noexcept {
        std::vector<uint8_t> & vector = *static_cast<std::vector<uint8_t> *>(userp);
        const size_t writeSize = size * nmemb;
        const size_t srcSize = vector.size();
        uint8_t * writePtr = nullptr;
        try {
            if (srcSize > 0) {
                vector.resize(srcSize + writeSize); // +1 included
                writePtr = vector.data() + (srcSize - 1);
            } else {
                vector.resize(writeSize + 1);
                writePtr = vector.data();
            }
            std::memcpy(writePtr, contents, writeSize);
        } catch (...) {
            return 0;
        }
        writePtr += writeSize;
        *writePtr = 0;
        return writeSize;
    }
    
    std::vector<uint8_t> CURLDownloader::get(const std::string & url) {
        cleanup();
        
        CURL * curl = curl_easy_init();
        if ( !(_impl = curl) ) {
            throw std::runtime_error("[CURL] init");
        }
        
        std::stringstream errorStream;
        const char * errorDescription;
        CURLcode res;
        
        if ( (res = curl_easy_setopt(curl, CURLOPT_URL, url.c_str())) != CURLE_OK ) {
            cleanup();
            errorStream << "[CURL] set url error code: " << res;
            if ( (errorDescription = curl_easy_strerror(res)) ) {
                errorStream << ", description: " << errorDescription;
            }
            errorStream << std::endl;
            throw std::runtime_error(errorStream.str());
        }
        if ( (res = curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30)) != CURLE_OK ) {
            cleanup();
            errorStream << "[CURL] set timeout error code: " << res;
            if ( (errorDescription = curl_easy_strerror(res)) ) {
                errorStream << ", description: " << errorDescription;
            }
            errorStream << std::endl;
            throw std::runtime_error(errorStream.str());
        }
        if ( (res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CURLDownloader::writeCallback)) != CURLE_OK ) {
            cleanup();
            errorStream << "[CURL] set write function error code: " << res;
            if ( (errorDescription = curl_easy_strerror(res)) ) {
                errorStream << ", description: " << errorDescription;
            }
            errorStream << std::endl;
            throw std::runtime_error(errorStream.str());
        }
        
        std::vector<uint8_t> responseData;
        
        if ( (res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData)) != CURLE_OK ) {
            cleanup();
            errorStream << "[CURL] set write data error code: " << res;
            if ( (errorDescription = curl_easy_strerror(res)) ) {
                errorStream << ", description: " << errorDescription;
            }
            errorStream << std::endl;
            throw std::runtime_error(errorStream.str());
        }
        if ( (res = curl_easy_perform(curl)) != CURLE_OK ) {
            cleanup();
            errorStream << "[CURL] perform error code: " << res << ", url: " << url;
            if ( (errorDescription = curl_easy_strerror(res)) ) {
                errorStream << ", description: " << errorDescription;
            }
            errorStream << std::endl;
            throw std::runtime_error(errorStream.str());
        }
        
        cleanup();
        
        return responseData;
    }
    
    void CURLDownloader::cleanup() noexcept {
        if (_impl) {
            curl_easy_cleanup(static_cast<CURL *>(_impl));
            _impl = nullptr;
        }
    }
    
    CURLDownloader::CURLDownloader() noexcept {
        if (_isRequireGlobalInit) {
            curl_global_init(CURL_GLOBAL_ALL);
            _isRequireGlobalInit = false;
        }
    }
    
    CURLDownloader::~CURLDownloader() noexcept {
        cleanup();
    }
    
    bool CURLDownloader::_isRequireGlobalInit = true;
    
} // namespace DetectIP
