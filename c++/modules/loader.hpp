#ifndef LOADER_HPP
#define LOADER_HPP

#include "profile.hpp"

class FASTASequenceLoader {
    public :
        static Profile* load(std::string filename, std::string alphabet);


    private :
        static std::string sanitize(std::string& sequence, std::string& alphabet);
};

#endif