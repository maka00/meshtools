#include<iostream>
#include<chrono>
#include<spdlog/spdlog.h>
#include<application.h>

#include<boost/program_options.hpp>

namespace {
    const size_t SUCCESS = 0;
    const size_t ERROR_IN_COMMAND_LINE = 1;
    const size_t ERROR_UNHANDLED_EXCEPTION = 2;

} // namespace
auto logger = spdlog::stdout_color_mt("logger");

int main(int argc, char **argv) {
    logger->info("application started");
    namespace po = boost::program_options;
    po::options_description desc("Options");
    desc.add_options()
            ("help", "Print help messages")
            ("dir", po::value<std::string>(), "input directory");

    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);

        if (vm.count("help")) {
            std::cout << "MeshUI app" << "\n" << desc << "\n";
            return SUCCESS;
        }

        po::notify(vm);
    } catch (po::error &e) {
        logger->error("commandline error {0}", e.what());
        std::cout << desc << "\n";
        return ERROR_IN_COMMAND_LINE;
    }
    std::string dir;
    if (vm.count("dir")) {
        dir = vm["dir"].as<std::string>();
    } else
        dir = ".";
   try {
        application app("Mesh App", 1280, 720);
        app.set_workdir(dir);
        app.run();

    } catch (application_exception &a) {
        logger->error(a.what());
    } catch (std::exception &e) {
        logger->error(e.what());
    }
    logger->info("application finished");
    return SUCCESS;
}



