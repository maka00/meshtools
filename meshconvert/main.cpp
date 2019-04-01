#include<iostream>
#include<chrono>
#include<spdlog/spdlog.h>
#include<OpenMesh/Core/IO/MeshIO.hh>
#include<meshtype.h>
#include<boost/program_options.hpp>
#include<boost/filesystem.hpp>

namespace
{
    const size_t SUCCESS = 0;
    const size_t ERROR_IN_COMMAND_LINE = 1;
    const size_t ERROR_UNHANDLED_EXCEPTION = 2;

} // namespace
auto console = spdlog::stdout_color_mt("console");

void convert(const std::string &from, const std::string &to) {
        mesh::mesh_type a_mesh;
        OpenMesh::IO::Options opt = OpenMesh::IO::Options::Default;
        a_mesh = mesh::load_mesh(from);
        if (opt.face_has_color() || opt.vertex_has_color())
            console->info("the mesh contains color information");

        if (a_mesh.n_faces() == 0) {
            console->error("error reading file {0}", from);
            return;
        }
        console->info("converting {0} vertices", a_mesh.n_vertices());
        opt += OpenMesh::IO::Options::Binary;
        mesh::store_mesh(a_mesh,to,opt);
}

int main(int argc, char** argv) {
    try {
        namespace po = boost::program_options;
        po::options_description desc("Options");
        desc.add_options()
                ("help", "Print help messages")
                ("input", po::value<std::string>(), "input mesh")
                ("output", po::value<std::string>(), "output mesh");

        po::variables_map vm;
        try {
            po::store(po::parse_command_line(argc, argv, desc), vm);

            if ( vm.count("help")  ) {
                std::cout << "Mesh converter app" << "\n" << desc << "\n";
                return SUCCESS;
            }

            po::notify(vm); 
        } catch (po::error& e) {
            console->error("commandline error {0}", e.what());
            std::cout << desc << "\n";
            return ERROR_IN_COMMAND_LINE;
        }
        auto start = std::chrono::system_clock::now();
        console->info("started");
        if ( vm.count("input") == 0 || vm.count("output") == 0 ) {
            console->error("commandline error");
            return ERROR_IN_COMMAND_LINE;
        }
        std::string input = vm["input"].as<std::string>();
        std::string output = vm["output"].as<std::string>();
        boost::filesystem::path pt = input;
        if (!boost::filesystem::is_regular_file(pt)) {
            console->error("input file {0} does not exist.", input);
            return ERROR_IN_COMMAND_LINE;
        }
        console->info("convert {0} to {1}", input, output);

        convert(input, output);
        auto end = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        console->info("time spend: {0} sec.", elapsed.count());
    } catch (std::exception& e) {
        console->error("Unhandled exception {0}", e.what());
        return ERROR_UNHANDLED_EXCEPTION;
    }
   return SUCCESS;
}