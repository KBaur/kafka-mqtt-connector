#include "IFetchEnvironment.h"

namespace kb{
std::string IFetchEnvironment::FetchEnvVariable(const std::string& p_name)
{
    std::string variable="";
    try{
        variable = std::getenv(p_name.c_str());
#ifdef DEBUG
        std::cout << "["<<p_name<<"]" << " -> " << variable << std::endl;
#endif
    }catch(std::exception ex)
    {
        std::cerr << "Env variable with name " << p_name << "does not exist, closing program" << std::endl;
        exit(EXIT_FAILURE);
    }
    return variable;
}
}