#include <iostream>
#include "./json.hh"
#include "tlvProcessor.h"
#include "tlvEncoder.h"
#include "tlv.h"

using json = nlohmann::json;

namespace TLV {

/**
 * @brief Add keys into keys dictionary. please read Readme.md
 * 
 * @param key Storing key
 * @return int Returns dictionarty size
 */
int Processor::addKey(const std::string& key)
{
    int size = keys_.size();
    keys_.emplace(key, size + 1);
    return size+1;
}

/**
 * @brief JSON to TLV parsing and encoding method. Reads JSON lines, parses and encode into TLV structure and save.
 * 
 * @param inputFileName Input file name. This file contains JSON object lines.
 * @param outputFileName Output file name. This file will contain TLV structures. Please read Readme.md
 * @return int Returns 0 for success. Returns error code in case of error.
 */
int Processor::process(const char* inputFileName, const char* outputFileName)
{
    apr_file_t* input;
    char lineBuffer[1024] = {0x00};

    // 1. Open input file
    apr_status_t iStatus = apr_file_open(&input, inputFileName, APR_FOPEN_READ, 0, pool_);
    if (iStatus != APR_SUCCESS) {
        return -1;
    }

    // 2. Create a TLV encoder. Different encoder might be needed, file system, standart output, network etc.
    IEncoder* pEncoder = new TLV::TlvEncoder(pool_); // This is Apr file encoder
    if (pEncoder->open(outputFileName) != APR_SUCCESS) {
        apr_file_close(input);
        return -2;
    }

    // 3. Read input lines
    while (apr_file_gets(lineBuffer, sizeof(lineBuffer)/sizeof(char), input) == APR_SUCCESS) {
        // std::cout << lineBuffer << '\n'; // To see what is line
        
        // 4. Parse input JSON line
        auto jComplete = json::parse(std::string(lineBuffer));

        TLV::TlvBase* pTlv = nullptr;

        for (auto& item : jComplete.items()) { // Handle each feature of JSON line

            // 5. Add each key into key dictionary
            addKey(item.key());

            // 6. Create TLV instance regarding to its type. It is only simple solution that is needed to be refactored. It will created in each iteration.
            if (item.value().is_string()) {
                pTlv = new TLV::TlvString(item.value().get<std::string>());
            }
            else if (item.value().is_number_integer()) {
                pTlv = new TLV::TlvInteger(item.value().get<int>());
            }
            else if (item.value().is_boolean()) {
                pTlv = new TLV::TlvBoolean(item.value().get<bool>());
            }
            else {
                // Unknown/unsupported type, pass it
            }

            if (pTlv) {
                // 7. Call polymorphic encoding method
                pEncoder->encode(pTlv);

                delete pTlv;
                pTlv = nullptr;
            }
        }
    }
    // 8. Thats all
    pEncoder->close();  
    delete pEncoder;
    apr_file_close(input);


    // Comment out to print keys dictionary
    //for(auto&& k : keys_) {
    //    std::cout << "[" << k.first << "] " << k.second << "\n"; 
    //}

    return 0;
}

};
