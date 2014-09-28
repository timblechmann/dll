// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "../shared_lib_path.hpp"

//[callplugcpp_tutorial8
#include <boost/dll/import_function.hpp>
#include <iostream>
#include "refcounting_api.hpp"

int main(int argc, char* argv[]) { 
    // argv[1] contains path to our plugin library 
    BOOST_ASSERT(argc >= 2);
    typedef my_refcounting_api*(func_t)();

    boost::shared_ptr<my_refcounting_api> plugin_instance;
    {
        boost::function<func_t> f = boost::dll::import_function_alias<func_t>(
            shared_lib_path(argv[1], L"refcounting_plugin"), "create_refc_plugin"
        );

        plugin_instance = adopt( f() );

        // `f` goes out of scope here and will be destroyed.
        // `plugin_instance` holds a reference to shared_library and it is safe to
        // use it.
    }

    std::cout << "Plugin name: " << plugin_instance->name() << ", location: " << plugin_instance->location() << std::endl;
}
//]