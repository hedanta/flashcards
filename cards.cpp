
#include <nlohmann/json.hpp>

#include <iostream>
#include <fstream>

using json = nlohmann::ordered_json;

class CardManager {
public:
  std::string path_to_file_ = "cards.json";

public:
  CardManager() {
    path_to_file_ = "cards.json";
  }

  CardManager(const CardManager&) {};

  CardManager(std::string& path)
    : path_to_file_{ path }
  {}

  ~CardManager() = default;

  json ReadFromCardsFile(std::string& path);
  void WriteToCardsFile(std::string& path, json& data);

  void AddToDeck(int card_id, std::string deck_name);
  void RemoveFromDeck(int card_id, std::string deck_name);
};

// чтение из json
json CardManager::ReadFromCardsFile(std::string& path) {
  std::ifstream cards_file(path);
  json data = json::parse(cards_file);
  cards_file.close();
  return data;
}

// запись в json
void CardManager::WriteToCardsFile(std::string& path, json& data) {
  std::ofstream cards_edit(path);
  cards_edit << std::setw(2) << data << std::endl;
  cards_edit.close();
}

// добавление карточки в колоду
void CardManager::AddToDeck(int card_id, std::string deck_name) {
  json data = CardManager::ReadFromCardsFile(path_to_file_);

  data["cards"][card_id]["deck"].push_back(deck_name);

  CardManager::WriteToCardsFile(path_to_file_, data);
}

// удаление карточки из колоды
void CardManager::RemoveFromDeck(int card_id, std::string deck_name) {
  json data = CardManager::ReadFromCardsFile(path_to_file_);

  // количество колод, в которых есть карточка
  int deck_count = data["cards"][card_id]["deck"].size();

  // ищем индекс колоды, чтобы стереть её
  bool deleted = 0;
  for (int deck_idx = 0; deck_idx < deck_count; deck_idx += 1) {
    if (data["cards"][card_id]["deck"][deck_idx] == deck_name) {
      data["cards"][card_id]["deck"].erase(deck_idx);
      deleted = 1;
      break;
    }
  }

  CardManager::WriteToCardsFile(path_to_file_, data);
}

int main() {
  CardManager test;
  test.AddToDeck(1, "maths");
  test.RemoveFromDeck(1, "hehe");
  return 0;
}
