#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

struct Clue {
    std::string description;
    int importance;
};

std::vector<Clue> bubble_sort(std::vector<Clue>& v) {
    for (int i = 0; i < v.size(); ++i) {
        for (int j = 0; j < v.size() - 1 - i; ++j) {
            if (v[j].importance < v[j + 1].importance) {
                std::swap(v[j], v[j + 1]);
            }
        }
    }
    return v;
}

int findMax(std::vector<Clue>& clues, int index) {
    if (index == clues.size() - 1) {
        return clues[index].importance;
    }

    int max = findMax(clues, index + 1);
    return (clues[index].importance > max) ? clues[index].importance : max;

}

int main() {
    // №1 чтение файла
    std::set<std::string> cats;
    std::vector<std::string> descrs;
    std::vector<int> importances;
    std::map<std::string, std::vector<Clue>> grouped_clues;

    std::string category;
    std::string description;
    int importance;
    int counts = 0;

    std::map<std::string, int> m;

    std::ifstream clues("C:\\Users\\Asus\\Desktop\\c++\\clues.txt");

    while (clues >> category >> description >> importance) {
      cats.insert(category);
      descrs.push_back(description);
      importances.push_back(importance);
      grouped_clues[category].push_back({description, importance}); // для сортировки по категориям

      m[category] += 1; // для подсчета улик
      counts++; // для общего количества улик

    }

    std::cout << "=== ДЕТЕКТИВНОЕ АГЕНТСТВО ===" << std::endl << std::endl;
    std::cout << "Прочитано улик: " << counts << std::endl << std::endl;

    // № 2 Группировка по категориям

    std::cout << "Категории: " << std::endl;

    for (auto const& [name, count] : m) {
        std::cout << "  - " << name << ": " << count << " улики" << std::endl;
    }

    std::cout << std::endl;

    // № 3 Уникальные категории

    std::cout << "Уникальные категории (алфавитный порядок): " << std::endl << "  ";

    for (const auto& cat : cats) {
        std::cout << cat << ", ";
    }

    std::cout << std::endl << std::endl;

    // № 4 Сортировка улик(сортировка пузырьком) по категориям

    std::cout << " === Топ улик по категориям === " << std::endl << std::endl;

    for (const auto& cat : cats) {
        grouped_clues[cat] = bubble_sort(grouped_clues[cat]); // сортируем улики в каждой категории

        std::cout << "[" << cat << "]" << std::endl;
        int i = 0;
        for (const auto& clue : grouped_clues[cat]) {
            std::cout << "  " << ++i << ". " << clue.description << " (важность: " << clue.importance << ")" << std::endl;
        }
        std::cout << std::endl;
    }
    // №5 Самая важная улика

    std::cout << "=== Самая важная улика ===" << std::endl << std::endl;
    int max_importance = 0;
    std::string max_cat;

    for (const auto& cat : cats) {
        int cat_max = findMax(grouped_clues[cat], 0);
        if (cat_max > max_importance) {
            max_importance = cat_max;
            max_cat = cat;
        }
    }
    std::cout << "Самая важная улика находится в категории: " << std::endl;
    std::cout << "Категория: " << max_cat << std::endl;
    std::cout << "Важность: " << max_importance << std::endl << std::endl;

    // №6 Поиск по категории

    std::string search_cat;
    std::cout << "Введите категорию для поиска улик: ";
    std::cin >> search_cat;

    for (const auto& clue : grouped_clues[search_cat]) {
        std::cout << "  - " << clue.description << " (важность: " << clue.importance << ")" << std::endl;
    }
    std::cout << std::endl;

    // №7 Расчет средней важности для каждой категории

    std::cout << "=== Средняя важность по категориям ===" << std::endl << std::endl;

    for (const auto& cat : cats) {
        std::cout << "[" << cat << "]" << std::endl;
        int sm = 0;
        for (const auto& clue : grouped_clues[cat]) {
            sm += clue.importance;
        }
        std::cout << "Средняя важность: " << sm / grouped_clues[cat].size() << std::endl;
        std::cout << std::endl;
    }

    // №8 Запись в файл отчета
    std::cout << "=== Запись отчета в файл ===" << std::endl << std::endl;
    std::ofstream clues2("report.txt");

    std::cout << "Отчет сохранен в report.txt" << std::endl;

    clues2 << "=== ДЕТЕКТИВНОЕ АГЕНТСТВО ===" << std::endl << std::endl;
    clues2 << "Прочитано улик: " << counts << std::endl << std::endl;


    clues2 << "Категории: " << std::endl;

    for (auto const& [name, count] : m) {
        clues2 << "  - " << name << ": " << count << " улики" << std::endl;
    }

    clues2 << std::endl;

    clues2 << "Уникальные категории (алфавитный порядок): " << std::endl << "  ";

    for (const auto& cat : cats) {
        clues2 << cat << ", ";
    }

    clues2 << std::endl << std::endl;

    clues2 << " === Топ улик по категориям === " << std::endl << std::endl;

    for (const auto& cat : cats) {
        grouped_clues[cat] = bubble_sort(grouped_clues[cat]); // сортируем улики в каждой категории

        clues2 << "[" << cat << "]" << std::endl;
        int i = 0;
        for (const auto& clue : grouped_clues[cat]) {
            clues2 << "  " << ++i << ". " << clue.description << " (важность: " << clue.importance << ")" << std::endl;
        }
        clues2 << std::endl;
    }

    clues2 << "=== Самая важная улика ===" << std::endl << std::endl;

    clues2 << "Самая важная улика находится в категории: " << std::endl;
    clues2 << "Категория: " << max_cat << std::endl;
    clues2 << "Важность: " << max_importance << std::endl << std::endl;

    for (const auto& clue : grouped_clues[search_cat]) {
        clues2 << "  - " << clue.description << " (важность: " << clue.importance << ")" << std::endl;
    }
    
    clues2 << std::endl;

    for (const auto& cat : cats) {
        clues2 << "[" << cat << "]" << std::endl;
        int sm = 0;
        for (const auto& clue : grouped_clues[cat]) {
            sm += clue.importance;
        }
        clues2 << "Средняя важность: " << (double)sm / grouped_clues[cat].size() << std::endl;
        clues2 << std::endl;
    }

    clues2.close();
    return 0;
}