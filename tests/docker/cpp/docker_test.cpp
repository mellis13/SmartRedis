#include "client.h"

int main(int argc, char* argv[]) {

    SmartRedis::Client client(false);

    std::vector<double> data = {1.0, 2.0, 3.0};
    std::vector<size_t> dims = {3};
    client.put_tensor("cpp_docker_tensor", data.data(), dims,
                      SRTensorTypeDouble, SRMemLayoutContiguous);
    return 0;
}
