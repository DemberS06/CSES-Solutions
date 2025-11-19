// generate_readme.cpp
// Generador de README para CSES-Solutions
// Produce una tabla Markdown con links a las carpetas del repo y badges de progreso.

#include <bits/stdc++.h>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

string url_encode(const string &s) {
    ostringstream o;
    for (unsigned char c : s) {
        if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            o << c;
        } else if (c == ' ') {
            o << "%20";
        } else if (c == '/') {
            o << "%2F";
        } else if (c == '+') {
            o << "%2B";
        } else if (c == '%') {
            o << "%25";
        } else {
            o << '%' << std::hex << std::uppercase << (int)c << std::dec;
        }
    }
    return o.str();
}

string badge_color(int solved, int total) {
    if (total == 0) return "lightgrey";
    if (solved >= total) return "brightgreen";
    double r = double(solved) / double(total);
    if (r >= 0.75) return "green";
    if (r >= 0.50) return "yellow";
    if (r >= 0.25) return "orange";
    return "red";
}

int count_sources_in_folder(const fs::path &folder) {
    if (!fs::exists(folder) || !fs::is_directory(folder)) return 0;
    int cnt = 0;
    try {
        for (auto const &entry : fs::recursive_directory_iterator(folder)) {
            if (!entry.is_regular_file()) continue;
            string ext = entry.path().extension().string();
            transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
            if (ext == ".cpp" || ext == ".cc" || ext == ".cxx" || ext == ".c") {
                ++cnt;
            }
        }
    } catch (const std::exception &e) {
        cerr << "Warning: error reading folder " << folder.string() << " : " << e.what() << '\n';
    }
    return cnt;
}

int main() {
    // Ajusta esto a tu repo / rama si es necesario:
    const string repo_url = "https://github.com/DemberS06/CSES-Solutions";
    const string branch = "main";

    vector<string> categories = {
        "Introductory_Problems",
        "Sorting_and_Searching",
        "Dynamic_Programming",
        "Graph_Algorithms",
        "Range_Queries",
        "Tree_Algorithms",
        "Mathematics",
        "String_Algorithms",
        "Geometry",
        "Advanced_Techniques",
        "Sliding_Window_Problems",
        "Interactive_Problems",
        "Bitwise_Operations",
        "Construction_Problems",
        "Advanced_Graph_Problems",
        "Counting_Problems",
        "Additional_Problems_I",
        "Additional_Problems_II"
    };

    map<string,int> totals = {
        {"Introductory_Problems", 24},
        {"Sorting_and_Searching", 35},
        {"Dynamic_Programming", 23},
        {"Graph_Algorithms", 36},
        {"Range_Queries", 25},
        {"Tree_Algorithms", 16},
        {"Mathematics", 37},
        {"String_Algorithms", 21},
        {"Geometry", 16},
        {"Advanced_Techniques", 25},
        {"Sliding_Window_Problems", 11},
        {"Interactive_Problems", 6},
        {"Bitwise_Operations", 11},
        {"Construction_Problems", 8},
        {"Advanced_Graph_Problems", 28},
        {"Counting_Problems", 18},
        {"Additional_Problems_I", 30},
        {"Additional_Problems_II", 30}
    };

    map<string,int> solved;
    int total_solved = 0;
    int total_problems = 0;
    for (auto &cat : categories) {
        fs::path p = fs::path(cat);
        int c = count_sources_in_folder(p);
        solved[cat] = c;
        total_solved += c;
        total_problems += totals[cat];
    }

    ofstream out("README.md");
    if (!out.is_open()) {
        cerr << "No se pudo crear README.md\n";
        return 1;
    }

    out << "# CSES Solutions\n\n";
    out << "This repository contains my accepted solutions to the **CSES Problem Set**, written in **C++**.\n\n";

    // Badge total
    {
        ostringstream badge;
        badge << "https://img.shields.io/badge/Solutions-";
        badge << url_encode(to_string(total_solved) + "/" + to_string(total_problems));
        badge << "-blue?style=for-the-badge";
        out << "<p align=\"center\">\n  <img src=\"" << badge.str() << "\" />\n</p>\n\n";
    }

    out << "---\n\n";
    out << "## Progress by Category\n\n";

    // Tabla Markdown con enlaces a carpetas y badges (los badges también apuntan a la carpeta)
    out << "| Category | Progress |\n";
    out << "|---|---:|\n";

    for (auto &cat : categories) {
        int s = solved[cat];
        int t = totals[cat];
        string color = badge_color(s, t);

        string folder_link = repo_url + "/tree/" + branch + "/" + url_encode(cat);

        ostringstream badge_url;
        badge_url << "https://img.shields.io/badge/"
                << url_encode(cat) << "-" << s << "/" << t << "-" << color
                << "?style=flat-square";

        out << "| [" << cat << "](" << folder_link << ") "
            << "| [![](" << badge_url.str() << ")](" << folder_link << ") |\n";
    }

    out << "\n---\n\n";
    out << "## About This Repository\n\n";
    out << "All solutions are implemented in **C++** using modern competitive programming techniques.\n\n";

    out << "## Folder Structure\n\n";
    out << "```\nCSES-Solutions/\n";
    for (auto &cat : categories) {
        out << "├── " << cat << "\n";
    }
    out << "```\n\n";

    out << "## License\nMIT License.\n\n";
    out << "## Author\n**Juan Pablo (Dember) Salinas**\n";

    out.close();

    cout << "README.md generado correctamente.\n";
    cout << "Total solved: " << total_solved << " / " << total_problems << "\n";
    for (auto &cat : categories) {
        cout << cat << " : " << solved[cat] << " / " << totals[cat] << "\n";
    }

    return 0;
}
