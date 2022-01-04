#include "c_client.h"
#include "stdio.h"
#include "srexception.h"
#include "sr_enums.h"

int main(int argc, char* argv[]) {

    void* client = NULL;

    SRError return_code = SRNoError;
    return_code = SmartRedisCClient(false, &client);

    if (return_code != SRNoError) {
        return -1;
    }

    char* key = "c_docker_tensor";
    size_t key_length = strlen(key);

    double tensor[3] = {1.0, 2.0, 3.0};
    SRTensorType type = SRTensorTypeDouble;
    SRMemoryLayout layout = SRMemLayoutContiguous;
    size_t dims[1] = {3};
    size_t n_dims = 1;

    return_code = put_tensor(client, key, key_length,
                            (void*)(&tensor), &dims, n_dims, type, layout);

    if (return_code != SRNoError) {
        return -1;
    }

    return 0;
}
