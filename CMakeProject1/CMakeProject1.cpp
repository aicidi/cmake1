// CMakeProject1.cpp : 애플리케이션의 진입점을 정의합니다.
//

#include "CMakeProject1.h"
#include <fstream>

std::string read_setting(const std::string name)
{
    std::ifstream file(name);
    std::string setting;

    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            setting += line;
        }

        file.close();
    }

    return setting;
}

static const std::string k_type_names[] =
{ "Null", "False", "True", "Object", "Array", "String", "Number" };

int main()
{
    const auto setting = read_setting(R"(C:\CMakeProject1\CMakeSettings.json)");
    std::cout << setting << std::endl;

    YAML::Node yaml_node;

    rapidjson::Document doc;
    doc.Parse(setting.c_str());

    auto& conf = doc["configurations"][0];

    for (auto& obj : conf.GetObject())
    {
        auto type = k_type_names[obj.value.GetType()];
        auto name = obj.name.GetString();

        if (type == "String")
        {
            yaml_node[name] = obj.value.GetString();
        }
        else if (type == "Array" && obj.value[0].IsObject())
        {
            auto temp_node = YAML::Node();
            auto& variables = obj.value[0];

            for (auto& var : variables.GetObject())
            {
                temp_node[var.name.GetString()] = var.value.GetString();
            }

            yaml_node[name] = temp_node;
        }
        else if (type == "Array")
        {
            for (auto& item : obj.value.GetArray())
            {
                yaml_node[name].push_back(item.GetString());
            }
        }
    }

    std::ofstream fout("setting.yaml");
    fout << yaml_node;

    return 0;
}
