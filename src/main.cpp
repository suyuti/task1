#include <cstdlib>
#include <apr.h>
#include <apr_general.h>
#include "tlvProcessor.h"

void onExit() 
{
    apr_terminate();
}

int main(int argc, char** argv) 
{
    apr_pool_t* pool;
    apr_file_t* out;

    apr_initialize();
    atexit(onExit);

    apr_pool_create(&pool, NULL);
    apr_file_open_stdout(&out, pool);
    apr_file_printf(out, "JSON-TLV Packer\n");
    apr_file_printf(out, "Input file : ../data/input\n");
    apr_file_printf(out, "Output file: ../data/output.tlv\n");

    TLV::Processor task(pool);

    task.process("../data/input", "../data/output.tlv");

    apr_file_printf(out, "Done.\n");

    apr_file_close(out);
    apr_pool_destroy(pool);

    return EXIT_SUCCESS;
}