#pragma once
#include <string>

namespace adpart_sim {

void SetCurrentConfigPath(std::string const &current_path);

class File {
   public:
    explicit File(std::string const &fullpath);

   public:
    std::string GetContent();

   public:
    // m_exists
    bool exists();
    // m_dirname
    std::string dirname();
    // m_basename
    std::string basename();
    // m_fullpath
    std::string fullpath();
    // m_filename
    std::string filename();
    // m_extension
    std::string extension();

   private:
    bool m_exists = false;
    std::string m_dirname = "empty_dirname";
    std::string m_basename = "empty_basename";
    std::string m_fullpath = "empty_fullpath";
    std::string m_filename = "empty_filename";
    std::string m_extension = "empty_extension";

   public:
    static bool Exists(std::string const &fullpath);
    static std::string ReadAll(std::string const &fullpath);
    static std::string Abspath(std::string const &fullpath);
    static std::string Dirname(std::string const &fullpath);
    static std::string Filename(std::string const &fullpath);
    static std::string Basename(std::string const &fullpath);
    static std::string Extension(std::string const &fullpath);
};

class Directory {
   public:
    explicit Directory(std::string fullpath);

   public:
    // m_exists
    bool exists();
    // m_dirname
    bool create();
    // m_dirname
    std::string dirname();
    // m_fullpath
    std::string fullpath();
    // m_parentpath
    std::string parentpath();

   private:
    bool m_exists = false;
    std::string m_dirname = "empty_dirname";
    std::string m_fullpath = "empty_fullpath";
    std::string m_parentpath = "empty_parentpath";

   public:
    static bool Create(std::string const &fullpath);
    static bool Exists(std::string const &fullpath);
    static std::string Dirname(std::string const &fullpath);
    static std::string Dirpath(std::string const &fullpath);
    static std::string Abspath(std::string const &fullpath);
};

}  // namespace adpart_sim
