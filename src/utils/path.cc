#include "utils/path.h"
#include <boost/filesystem.hpp>
#include <fstream>
#include "utils/logging.h"

using namespace std;

namespace adpart_sim {

static string current_config_path = "./";

void SetCurrentConfigPath(string const &current_path) { current_config_path = current_path; }

File::File(string const &fullpath) {
    m_fullpath = File::Abspath(fullpath);
    boost::filesystem::path path(m_fullpath);
    m_exists = boost::filesystem::exists(path) && boost::filesystem::is_regular_file(path);
    m_filename = path.filename().string();
    m_dirname = path.parent_path().string();
    m_extension = path.extension().string();
    m_basename = path.filename().stem().string();
}

bool File::exists() { return m_exists; }

string File::fullpath() { return m_fullpath; }

string File::filename() { return m_filename; }

string File::dirname() { return m_dirname; }

string File::basename() { return m_basename; }

string File::extension() { return m_extension; }

string File::GetContent() { return File::ReadAll(m_fullpath); }

bool File::Exists(string const &fullpath) {
    boost::filesystem::path path(fullpath);
    return boost::filesystem::exists(path) && boost::filesystem::is_regular_file(path);
}

string File::Abspath(string const &fullpath) {
    string real_path = fullpath;
    vector<string> current_path = {"$CURRENT_PATH", "${CURRENT_PATH}"};
    for (auto &item : current_path) {
        size_t pos = 0;
        while ((pos = real_path.find(item, pos)) != string::npos) {
            real_path = real_path.replace(pos, item.length(), current_config_path);
            pos += current_config_path.length();
        }
    }
    boost::filesystem::path path(real_path);
    if (!path.has_root_path()) {
        path = boost::filesystem::absolute(path);
    }
    return path.string();
}

string File::Dirname(string const &fullpath) {
    string abs_path = File::Abspath(fullpath);
    boost::filesystem::path path(abs_path);
    return path.parent_path().string();
}

string File::Filename(string const &fullpath) {
    boost::filesystem::path path(File::Abspath(fullpath));
    return path.filename().string();
}

string File::Basename(string const &fullpath) {
    boost::filesystem::path path(File::Abspath(fullpath));
    return path.filename().stem().string();
}

string File::Extension(string const &fullpath) {
    boost::filesystem::path path(File::Abspath(fullpath));
    return path.extension().string();
}

string File::ReadAll(string const &fullpath) {
    string content = "";
    ifstream file_stream(fullpath, ios::ate | ios::binary);
    if (File::Exists(fullpath) && file_stream) {
        streamsize size = file_stream.tellg();
        file_stream.seekg(0, ios::beg);
        content.resize(static_cast<size_t>(size));
        file_stream.read(&content[0], size);
    } else
        LOGW("File does not exist: " << fullpath);
    return content;
}

}  // namespace adpart_sim

namespace adpart_sim {

Directory::Directory(string fullpath) {
    m_fullpath = Directory::Abspath(fullpath);
    boost::filesystem::path path(m_fullpath);
    m_exists = boost::filesystem::exists(path) && boost::filesystem::is_directory(path);
    m_dirname = path.filename().string();
    m_parentpath = path.parent_path().string();
}

bool Directory::exists() { return m_exists; }

string Directory::dirname() { return m_dirname; }

string Directory::fullpath() { return m_fullpath; }

string Directory::parentpath() { return m_parentpath; }

bool Directory::create() { return Directory::Create(m_fullpath); }

string Directory::Dirname(string const &fullpath) { return File::Filename(fullpath); }

string Directory::Dirpath(string const &fullpath) { return File::Dirname(fullpath); }

string Directory::Abspath(string const &fullpath) { return File::Abspath(fullpath); }

bool Directory::Exists(string const &fullpath) {
    boost::filesystem::path path(fullpath);
    return boost::filesystem::exists(path) && boost::filesystem::is_directory(path);
}

bool Directory::Create(string const &fullpath) {
    boost::filesystem::path path(Abspath(fullpath));
    string parent_path = path.parent_path().string();
    if (!Exists(parent_path)) Create(parent_path);
    return boost::filesystem::create_directory(path);
}

}  // namespace adpart_sim
