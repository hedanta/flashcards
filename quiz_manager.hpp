#include "deck_manager.hpp"

#include <nlohmann/json.hpp>

#include <codecvt>
#include <random>

using json = nlohmann::ordered_json;
using Flashcard = std::pair<std::wstring, std::wstring>;
using CardsContainer = std::vector<Flashcard>;

namespace {
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> Converter;
}


/*!
* @brief Класс изучения карточек
* 
* Позволяет проводить сам квиз - 
* устанавливать текущую колоду, получать случайную карточку,
* проверять пользовательский ответ и т.д.
*/
class QuizManager {
private:
  DeckManager cards;
  std::string deck_id_{ "0" };
  CardsContainer study_deck_{ cards.GetDeck(deck_id_) };
  Flashcard current_card_;

public:

  /*!
  * Конструктор по умолчанию
  */
  QuizManager(); 

  /*!
  * @brief Конструктор по идентифицатору колоды
  * 
  * Создаёт экземпляр класса, в котором данная
  * колода является текущей
  * 
  * @param deck_id Идентификатор колоды
  */
  QuizManager(std::string& deck_id);

  /*!
  * Деструктор по умолчанию
  */
  ~QuizManager();
  
  /*!
  * @brief Устанавливает текущую колоду
  * 
  * Устанавливает в качестве текущей колоду,
  * соответствующую данному идентификатору
  * @param deck_id Идентификатор колоды
  */
  void SetCurrentDeck(std::string& deck_id);

  /*!
  * @brief Получает размер колоды
  * 
  * @return Возвращает размер текущей колоды
  */
  const int GetCurrentDeckSize();

  /*!
  * @brief Получает идентификатор колоды
  * 
  * @return Возвращает идентификатор текущей колоды
  */
  const std::string GetCurrentDeckId();

  /*!
  * @brief Получает название колоды
  * 
  * @param deck_id Идентификатор колоды
  * 
  * @return Возвращает название колоды,
  * соответствующей данному идентификатору
  */
  const std::wstring GetDeckNameFromId(std::string& deck_id);

  /*!
  * Получает название колоды
  * 
  * @return Возвращает название текущей колоды
  */
  const std::wstring GetCurrentDeckName();

  /*!
  * @brief Получает карточку
  * 
  * @return Возвращает пару "вопрос - ответ"
  */
  const Flashcard GetCard();

  /*!
  * @brief Получает вопрос
  * 
  * @return Возвращает вопрос из карточки
  */
  const std::wstring GetQuestion();

  /*!
  * @brief Получает ответ
  * 
  * @return Возвращает ответ из карточки
  */
  const std::wstring GetAnswer();
  
  /*!
  * @brief Проверяет ответ
  * 
  * Проверяет данный пользователем ответ
  * 
  * @param user_ans Ответ пользователя
  * @param card_ans Ожидаемый ответ из карточки
  * 
  * @return Возвращает True, если ответ пользователя верный, 
  * в противном случае False
  */
  const bool CheckUserAnswer(std::wstring& user_ans, std::wstring& card_ans);

  /// @private
  void EraseCurrentCard();
};