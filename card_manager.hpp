
#include <nlohmann/json.hpp>

using json = nlohmann::ordered_json;
using Flashcard = std::pair<std::wstring, std::wstring>;
using CardsContainer = std::vector<Flashcard>;

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

  const json ReadFromCardsFile();
  const void WriteToCardsFile(json& data);

  const int RandomNum(const int& max_n);
  const int EncodeName(std::wstring& deck_name);

  const void CreateDeck(std::wstring& deck_name);
  const int GetDeckId(std::wstring& deck_name);
  std::vector<std::wstring> GetAllDecks();

  CardsContainer GetDeck(const int& deck_id);

  const void AddToDeck(int card_id, int deck_id);
  const void RemoveFromDeck(int card_id, int deck_id);
  const void RenameDeck(std::wstring previous_name, std::wstring new_name);
};