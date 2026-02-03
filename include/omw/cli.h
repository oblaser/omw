/*
author          Oliver Blaser
date            02.02.2026
copyright       MIT - Copyright (c) 2026 Oliver Blaser
*/

#ifndef IG_OMW_CLI_H
#define IG_OMW_CLI_H

#include <cstddef>
#include <string>
#include <vector>



namespace omw {

/*! \addtogroup grp_cli
 * @{
 */



namespace cli {

    size_t choice(const std::string& question, char opt0 = 'y', char opt1 = 'n', int def = -1);

    // size_t choice(const std::string& question, char opt0, char opt1, char opt2, int def = -1);
    // size_t choice(const std::string& question, const std::vector<char>& options, int def = -1);
    // size_t choice(const std::string& question, const char* options, int def = -1);

}



/*! @} */

} // namespace omw

#endif // IG_OMW_CLI_H
