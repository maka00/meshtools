//
// Created by mk on 14.04.19.
//

#pragma once

#include<array>
#include<chrono>
#include<unordered_set>
#include<glm/glm.hpp>
#include<spdlog/spdlog.h>
#include<glad/glad.h>
#include<boost/filesystem.hpp>
#include<boost/range/iterator_range_core.hpp>
#include<boost/algorithm/string.hpp>
#include<boost/container/flat_set.hpp>

typedef std::array<glm::vec3, 2> bounding_rect_t;

inline bool is_in_rect(const bounding_rect_t &rect, const glm::vec3 &point) {
    const int UL = 0;
    const int LR = 1;
    if ((point.x <= rect[UL].x && point.x >= rect[LR].x) && (point.y <= rect[UL].y && point.y >= rect[LR].y) &&
        (point.z <= rect[UL].z && point.z >= rect[LR].z)) {
        return true;
    }
    return false;
}


inline void extend(bounding_rect_t &br, const glm::vec3 &point) {
    if (is_in_rect(br, point))
        return;

    const int UL = 0;
    const int LR = 1;
    if (br[UL].x < point.x) br[UL].x = point.x;
    if (br[LR].x > point.x) br[LR].x = point.x;
    if (br[UL].y < point.y) br[UL].y = point.y;
    if (br[LR].y > point.y) br[LR].y = point.y;
    if (br[UL].z < point.z) br[UL].z = point.z;
    if (br[LR].z > point.z) br[LR].z = point.z;
}


inline glm::vec3 get_centroid(const bounding_rect_t &rect) {
    const int UL = 0;
    const int LR = 1;

    return (rect[LR] + rect[UL]) / 2.0f;
}

inline void log_br(const bounding_rect_t &rect) {
    const int UL = 0;
    const int LR = 1;
    spdlog::get("logger")->info("BR=[({0},{1},{2}),({3},{4},{5})]", rect[UL].x, rect[UL].y, rect[UL].z, rect[LR].x,
                                rect[LR].y, rect[LR].z);
}

inline void log_vertex(const glm::vec3 &v) {
    spdlog::get("logger")->info("({0},{1},{2})", v.x, v.y, v.z);
}

// returns a vector of files for a given directory with an optional extension filter
// the filter has to be of the form: "ply|stl"
inline std::vector<std::string> get_directory_list(const std::string &dir, const std::string &filter = ".*") {
    auto parse_dir = [filter](const std::string &dir) {
        boost::container::flat_set<std::string> filters;
        boost::algorithm::split(filters, filter, boost::algorithm::is_any_of("|"));
        std::vector<std::string> files;
        for (auto &entry : boost::make_iterator_range(boost::filesystem::directory_iterator(dir))) {
            if (boost::filesystem::is_regular_file(entry) &&
                (filters.empty() || filters.count(boost::filesystem::extension(entry)) || filters.count(".*"))) {
                files.push_back(boost::filesystem::path(entry).string());
            }
        }
        std::sort(files.begin(), files.end());
        return files;
    };
    static std::vector<std::string> files{parse_dir(dir)};
    static std::chrono::time_point timer = std::chrono::system_clock::now();
    auto now = std::chrono::system_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - timer);
    if (elapsed.count() < 1)
        return files;
    timer = now;
    files.clear();
    files = parse_dir(dir);
    return files;
}

inline bool is_directory(const std::string &path) {
    return boost::filesystem::is_directory(path);
}