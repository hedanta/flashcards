
#include <nlohmann/json.hpp>

using json = nlohmann::ordered_json;
using CardsContainer = std::vector<std::pair<std::wstring, std::wstring>>;

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

  int RandomNum(int max_n);
  std::string EncodeName(std::wstring& deck_name);

  const void CreateDeck(std::wstring& deck_name);
  std::wstring GetNameFromId(std::string& deck_id);

  std::vector<std::pair<std::string, std::wstring>> GetAllDecks();

  CardsContainer GetDeck(std::string deck_id);

  const void AddToDeck(int card_id, std::string deck_id);
  const void RemoveFromDeck(int card_id, std::string deck_id);
  const void RenameDeck(std::string deck_id, std::wstring new_name);
};