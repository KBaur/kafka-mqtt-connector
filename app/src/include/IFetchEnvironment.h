#ifndef __IFETCHENVIRONMENT_H__
#define __IFETCHENVIRONMENT_H__

#include <string>
#include <iostream>

namespace kb{
/**
 * @interface IFetchEnvironment
 * @details Interface to fetch environment variables
 * @date 2022
 * @author baurk
 */
class IFetchEnvironment{
    protected:
    std::string FetchEnvVariable(const std::string& p_name);
};
}
#endif