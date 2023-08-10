#pragma once

#include "json.hpp"
using json = nlohmann::ordered_json;

void CreateGameSettingsFile();
json GetGameSettings();
void SaveGameSettings(json data);