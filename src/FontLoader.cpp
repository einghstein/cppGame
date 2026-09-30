#include "FontLoader.h"

#include <cctype>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace FontLoader
{
namespace
{
namespace fs = std::filesystem;

std::vector<fs::path> fontDirectories(const char* executablePath)
{
    std::vector<fs::path> directories;
    std::error_code error;
    fs::path executableDir;

#if defined(__linux__)
    executableDir = fs::read_symlink("/proc/self/exe", error).parent_path();
#endif
    if (executableDir.empty() && executablePath != nullptr)
        executableDir = fs::absolute(executablePath, error).parent_path();

    if (!executableDir.empty())
    {
        directories.push_back(executableDir / "assets" / "fonts");
        directories.push_back(executableDir / "fonts");
    }

    directories.push_back(fs::current_path() / "assets" / "fonts");
    directories.push_back(fs::current_path() / "fonts");

    if (const char* home = std::getenv("HOME"))
    {
        directories.emplace_back(fs::path(home) / ".local/share/fonts");
        directories.emplace_back(fs::path(home) / ".fonts");
#if defined(__APPLE__)
        directories.emplace_back(fs::path(home) / "Library/Fonts");
#endif
    }

#if defined(__linux__)
    directories.emplace_back("/usr/share/fonts");
    directories.emplace_back("/usr/local/share/fonts");
#elif defined(_WIN32)
    if (const char* windows = std::getenv("WINDIR"))
        directories.emplace_back(fs::path(windows) / "Fonts");
    if (const char* localAppData = std::getenv("LOCALAPPDATA"))
        directories.emplace_back(fs::path(localAppData) / "Microsoft/Windows/Fonts");
#elif defined(__APPLE__)
    directories.emplace_back("/Library/Fonts");
    directories.emplace_back("/System/Library/Fonts");
#endif

    return directories;
}

bool isFontFile(const fs::path& path)
{
    std::string extension = path.extension().string();
    for (char& character : extension)
        character = static_cast<char>(std::tolower(static_cast<unsigned char>(character)));
    return extension == ".ttf" || extension == ".otf" || extension == ".ttc";
}

fs::path findFontPath(const char* executablePath)
{
    const auto directories = fontDirectories(executablePath);
    const std::vector<std::string> preferredNames = {
        "DejaVuSans.ttf", "LiberationSans-Regular.ttf", "NotoSans-Regular.ttf",
        "Arial.ttf", "FreeSans.ttf"
    };

    for (const auto& directory : directories)
    {
        for (const auto& name : preferredNames)
        {
            const auto candidate = directory / name;
            std::error_code error;
            if (fs::is_regular_file(candidate, error))
                return candidate;
        }
    }

    fs::path fallback;
    for (const auto& directory : directories)
    {
        std::error_code error;
        if (!fs::is_directory(directory, error))
            continue;

        for (fs::recursive_directory_iterator it(
                 directory, fs::directory_options::skip_permission_denied, error), end;
             it != end; it.increment(error))
        {
            if (error)
            {
                error.clear();
                continue;
            }

            std::error_code fileError;
            if (it->is_regular_file(fileError) && isFontFile(it->path()))
            {
                if (fallback.empty())
                    fallback = it->path();

                const auto filename = it->path().filename().string();
                for (const auto& preferred : preferredNames)
                {
                    if (filename == preferred)
                        return it->path();
                }
            }
        }
    }

    return fallback;
}
}

bool load(sf::Font& font, const char* executablePath)
{
    const auto fontPath = findFontPath(executablePath);
    if (fontPath.empty() || !font.openFromFile(fontPath.string()))
    {
        std::cerr << "Could not find a usable font. Install a system font or place one in "
                     "assets/fonts next to the application.\n";
        return false;
    }

    return true;
}
}
