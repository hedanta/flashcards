
#include <nlohmann/json.hpp>

#include <iostream>
#include <fstream>

using json = nlohmann::ordered_json;

class Deck {
private:
  std::string path_to_file_ = "cards.json";

public:
  Deck() {
    path_to_file_ = "cards.json";
  }

  Deck(std::string& path)
    : path_to_file_{ path }
  {}

  ~Deck() = default;

  void AddToDeck(int card_id, std::string deck_name);
  void RemoveFromDeck(int card_id, std::string deck_name);
};

void Deck::AddToDeck(int card_id, std::string deck_name) {
  std::ifstream questions(path_to_file_);
  json data = json::parse(questions);

  data["cards"][card_id - 1]["deck"].push_back(deck_name);

  std::ofstream questions_edit("cards.json");
  questions_edit << std::setw(2) << data << std::endl;

  questions.close();
  questions_edit.close();
}

void::Deck::RemoveFromDeck(int card_id, std::string deck_name) {
  std::ifstream questions(path_to_file_);
  json data = json::parse(questions);

  int deck_count = data["cards"][card_id - 1]["deck"].size();
  for (int deck_idx = 0; deck_idx <= deck_count; deck_idx += 1) {
    if (data["cards"][card_id - 1]["deck"][deck_idx] == deck_name) {
      data["cards"][card_id - 1]["deck"].erase(deck_idx);
      break;
    }
  }

  std::ofstream questions_edit("cards.json");
  questions_edit << std::setw(2) << data << std::endl;

  questions.close();
  questions_edit.close();
}

int main() {
  Deck test;
  test.AddToDeck(1, "maths");
  test.RemoveFromDeck(2, "hehe");
  return 0;
}
