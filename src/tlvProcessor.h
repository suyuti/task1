#ifndef _TLV_PROCESSOR_H_
#define _TLV_PROCESSOR_H_

#include <string>
#include <map>
#include <apr.h>
#include <apr_general.h>
#include <apr_file_io.h>


namespace TLV {

class Processor {
private:
    Processor() {}
public:
    Processor(apr_pool_t* pool) : pool_{pool} {}
    
    int process(const char* inputFileName, const char* outputFileName);

private:
    int addKey(const std::string& key);

private:
    apr_pool_t* pool_;
    std::map<std::string, int> keys_;
};

};

#endif // _TLV_PROCESSOR_H_
