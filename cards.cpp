
#include <nlohmann/json.hpp>

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <unordered_map>

using json = nlohmann::ordered_json;
using CardsContainer = std::unordered_map<std::string, std::string>;
using Flashcard = std::pair<std::string, std::string>;

namespace {
  CardsContainer GetCards(const std::string& deck_name) {
    std::ifstream file;
    file.exceptions(std::ifstream::badbit);

    CardsContainer current_deck{};

    try {
      file.open("cards.json");
      json data = json::parse(file);

      for (auto& el : data["cards"].items()) {
        for (auto& deck_el : el.value()["deck"].items()) {
          if (deck_el.value() == deck_name) {
            current_deck.insert(std::make_pair( el.value()["question"], el.value()["answer"] ));
          }
        }
      }
    }

    catch (std::ifstream::failure& e) {
      std::cerr << "Exception opening/reading/closing file\n";
    }

    file.close();
    return current_deck;
  }

  int RandomInd(int max_n) {
    std::srand(std::time(0));

    int ind = std::rand() % (max_n + 1);
    return ind;
  }
}

// управление карточками
class CardManager {
private:
  std::string path_to_file_ = "cards.json";

public:
  CardManager() = default;

  CardManager(const CardManager&) {};

  CardManager(std::string& path)
    : path_to_file_{ path }
  {};

  ~CardManager() = default;

  json ReadFromCardsFile(std::string& path);
  void WriteToCardsFile(std::string& path, json& data);

  void AddToDeck(int card_id, std::string deck_name);
  void RemoveFromDeck(int card_id, std::string deck_name);
  void RenameDeck(std::string previous_name, std::string new_name);
};

// изучение колоды карточек
class CardLearner {
private:
  std::string deck_name_{ "All" };
  CardsContainer study_deck_{ GetCards(deck_name_) };

  // bool show_result_{ 1 };
  // мб параметр показа результата надо задать не тут

public:
  CardLearner() = default;

  CardLearner(std::string& deck_name)
    : deck_name_{deck_name}
    , study_deck_{ GetCards(deck_name) }
  {};

  const int GetDeckSize() {
    return study_deck_.size();
  }

  Flashcard GetCard();

  bool CheckUserAnswer(std::string& user_ans, std::string& card_ans);
};

Flashcard CardLearner::GetCard() {
  int deck_size = CardLearner::GetDeckSize();
  Flashcard card;

  if (deck_size > 0) {
    auto card_it = std::next(study_deck_.begin(), RandomInd(deck_size - 1));
    card = { card_it->first, card_it->second };
    study_deck_.erase(card_it);
  }

  return card;
}

bool CardLearner::CheckUserAnswer(std::string& user_ans, std::string& card_ans) {
  if (user_ans == card_ans) {
    return true;
  }
  else {
    return false;
  }
}

// чтение из json
json CardManager::ReadFromCardsFile(std::string& path) {
  std::ifstream cards_file;
  cards_file.exceptions(std::ifstream::badbit);

  json data;

  try {
    cards_file.open(path);
    data = json::parse(cards_file);
  }

  catch (std::ifstream::failure& e) {
    std::cerr << "Exception opening/reading file\n";
  }

  cards_file.close();
  return data;
}

// запись в json
void CardManager::WriteToCardsFile(std::string& path, json& data) {
  std::ofstream cards_edit;
  cards_edit.exceptions(std::ofstream::badbit);

  try {
    cards_edit.open(path);
    cards_edit << std::setw(2) << data << std::endl;
  }

  catch (std::ofstream::failure const &e) {
    std::cerr << "Exception opening/writing to file\n";
  }

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

void CardManager::RenameDeck(std::string previous_name, std::string new_name) {
  json data = CardManager::ReadFromCardsFile(path_to_file_);

  for (auto& el : data["cards"].items()) {
    for (auto& deck_el : el.value()["deck"].items()) {
      if (deck_el.value() == previous_name) {
        // я не поняла прикола пока что.
      }
    }
  }
}

int main() {
  /*CardManager test;
  test.AddToDeck(1, "maths");
  test.RemoveFromDeck(1, "maths");*/

  
  CardLearner quiz;
  
  const int deck_size = quiz.GetDeckSize();

  for (int i = 0; i < deck_size; i += 1) {
    // хз как нормально организовать получение вопроса-ответа
    // в отдельные функции
    Flashcard current_card = quiz.GetCard();
    std::cout << "The question is: " << current_card.first << ", the answer is: " << current_card.second << '\n';
  }
  return 0;
}
