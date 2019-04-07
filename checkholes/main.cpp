#include<iostream>
#include<chrono>
#include<spdlog/spdlog.h>
#include<OpenMesh/Core/IO/MeshIO.hh>
#include<meshtype.h>
#include<boost/program_options.hpp>
#include<boost/filesystem.hpp>
#include<holefill.h>
#include<fstream>
namespace {
    const size_t SUCCESS = 0;
    const size_t ERROR_IN_COMMAND_LINE = 1;
    const size_t ERROR_UNHANDLED_EXCEPTION = 2;

} // namespace
auto console = spdlog::stdout_color_mt("console");

void checkholes(const mesh::mesh_type &a_mesh, bool export_holes) {
    console->info("analysing holes");
    Holefill holefill = Holefill(a_mesh);
    std::vector<Holefill::Hole> holes = holefill.get_holes();
    int cnt = 0;
    console->info("There are {0} holes in the mesh.",holes.size());
    if (export_holes) {
        for (Holefill::Hole hole : holes) {
            std::ofstream f;
            f.open(fmt::format("hole_{0}.xyz", cnt++));
            if (f.is_open()) {
                std::string coords = holefill.print_hole(hole);
                f << coords;
                f.close();
            }
        }
    }
}

int main(int argc, char **argv) {
    try {
        namespace po = boost::program_options;
        po::options_description desc("Options");
        desc.add_options()
                ("help", "Print help messages")
                ("input", po::value<std::string>(), "input mesh")
                ("export", "export as Meshlab xyz files");

        po::variables_map vm;
        try {
            po::store(po::parse_command_line(argc, argv, desc), vm);

            if (vm.count("help")) {
                std::cout << "Mesh holechecker app" << "\n" << desc << "\n";
                return SUCCESS;
            }

            po::notify(vm);
        } catch (po::error &e) {
            console->error("commandline error {0}", e.what());
            std::cout << desc << "\n";
            return ERROR_IN_COMMAND_LINE;
        }
        console->info("started");
        if (vm.count("input") == 0) {
            console->error("commandline error");
            return ERROR_IN_COMMAND_LINE;
        }
        std::string input = vm["input"].as<std::string>();
        boost::filesystem::path pt = input;
        if (!boost::filesystem::is_regular_file(pt)) {
            console->error("input file {0} does not exist.", input);
            return ERROR_IN_COMMAND_LINE;
        }
        console->info("check holes in {0}", input);

        OpenMesh::IO::Options opt = OpenMesh::IO::Options::Default;
        mesh::mesh_type a_mesh;
        a_mesh = mesh::load_mesh(input);
        auto start = std::chrono::system_clock::now();
        checkholes(a_mesh, vm.count("export"));
        auto end = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        console->info("time spend: {0} sec.", elapsed.count());
    } catch (std::exception &e) {
        console->error("Unhandled exception {0}", e.what());
        return ERROR_UNHANDLED_EXCEPTION;
    }
    return SUCCESS;
}
